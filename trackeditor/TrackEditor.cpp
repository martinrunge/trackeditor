/****************************************************************************
 **
 ** Trolltech hereby grants a license to use the Qt/Eclipse Integration
 ** plug-in (the software contained herein), in binary form, solely for the
 ** purpose of creating code to be used with Trolltech's Qt software.
 **
 ** Qt Designer is licensed under the terms of the GNU General Public
 ** License versions 2.0 and 3.0 ("GPL License"). Trolltech offers users the
 ** right to use certain no GPL licensed software under the terms of its GPL
 ** Exception version 1.2 (http://trolltech.com/products/qt/gplexception).
 **
 ** THIS SOFTWARE IS PROVIDED BY TROLLTECH AND ITS CONTRIBUTORS (IF ANY) "AS
 ** IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 ** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 ** PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 ** OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 ** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 ** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 ** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 ** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 ** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 ** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** Since we now have the GPL exception I think that the "special exception
 ** is no longer needed. The license text proposed above (other than the
 ** special exception portion of it) is the BSD license and we have added
 ** the BSD license as a permissible license under the exception.
 **
 ****************************************************************************/

#include <sys/stat.h>
#include <fcntl.h>

#include <qapplication.h>
#include <QSocketNotifier>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QFileDialog>
#include <QMessageBox>

#include "TrackEditor.h"
#include "DeviceData.h"
#include "TrackView.h"
#include "tk1File.h"
#include "gpxFile.h"
#include "CWintec.h"

#include "ui_DeviceDialog.h"

LogReader::LogReader(QWidget *parent) :
	QMainWindow(parent) {
	ui.setupUi(this);
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	connect(ui.action_Connect, SIGNAL(triggered()), this, SLOT(connectDevice()));
	connect(ui.action_Disconnect, SIGNAL(triggered()), this, SLOT(disconnectDevice()));

	connect(ui.action_Load_Track, SIGNAL(triggered()), this, SLOT(loadTrack()));
	connect(ui.action_Save_Track, SIGNAL(triggered()), this, SLOT(saveTrack()));
	connect(ui.action_Save_Track_As, SIGNAL(triggered()), this, SLOT(saveTrackAs()));

	connect(ui.action_Read_Log, SIGNAL(triggered()), this, SLOT(readLog()));
	ui.action_Read_Log->setDisabled(true);
	connect(ui.action_Start_Recording, SIGNAL(triggered()), this, SLOT(startRecording()));
	connect(ui.action_Stop_Recording, SIGNAL(triggered()), this, SLOT(stopRecording()));


	connect(this, SIGNAL(setText(QString)), ui.nemaText, SLOT(appendPlainText(QString)));

	m_track_collection = new TrackCollection();

	m_track_view = new TrackView(ui.scrollArea);
	ui.scrollArea->setWidget(m_track_view);
	m_track_view->setTrackColletcion(m_track_collection);



    m_device_io = 0;
	m_dev_data = 0;
	m_expect_binary_data = 0;

	m_command_mode_step = 0;
	m_command_response_step = 0;

	m_track_filename.clear();

	ui.treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui.treeView->setModel(m_track_collection);

    m_selection_model = ui.treeView->selectionModel();
    connect(m_selection_model, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection,QItemSelection)));

    connect(ui.treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(treeViewClicked(QModelIndex)));

    ui.treeView->setEditTriggers( QAbstractItemView::DoubleClicked
								| QAbstractItemView::SelectedClicked
								| QAbstractItemView::EditKeyPressed );


    m_progress_dlg = new QDialog(this);
    prg_dlg.setupUi(m_progress_dlg);
    m_progress_dlg->setModal(false);
    connect(prg_dlg.cancelButton, SIGNAL(clicked()), this, SLOT(readLogFinished()));

}

LogReader::~LogReader() {

	if(m_device_io != 0)
	{
		delete m_device_io;
	}

	if(m_dev_data != 0)
	{
		leaveCommandMode();
	}

	ui.scrollArea->setWidget(0);
	delete m_track_view;

	delete m_track_collection;

	closeTTY();

	delete m_progress_dlg;
}

void LogReader::connectDevice() {
	QDialog *devdlg = new QDialog(this);
	Ui::DeviceDialog dlg;
	dlg.setupUi(devdlg);
	devdlg->setModal(true);
	int retval = devdlg->exec();

	if(retval == QDialog::Accepted) {
		qDebug("OK pressed.");
		openTTY("/dev/rfcomm0", 115200);
		m_device_io = new CWintec("WBT201");
		connect(this, SIGNAL(emitData(QByteArray)), m_device_io, SLOT(addData(QByteArray)));
		connect(m_device_io, SIGNAL(sendData(QByteArray)), this, SLOT(sendData(QByteArray)));
		connect(m_device_io, SIGNAL(nemaString(QString)), ui.nemaText, SLOT(appendPlainText(QString)));

		connect(m_device_io, SIGNAL(progress(int)), this, SLOT(progress(int)));

		connect(m_device_io, SIGNAL(readLogFinished()), this, SLOT(readLogFinished()));
		connect(m_device_io, SIGNAL(cancelReadLog()), this, SLOT(cancelReadLog()));

		connect(m_device_io, SIGNAL(newTrack(Track*)), this, SLOT(newTrack(Track*)));
		connect(m_device_io, SIGNAL(newWayPoint(TrackPoint*)), this, SLOT(newWayPoint(TrackPoint*)));
		connect(m_device_io, SIGNAL(newLogPoint(TrackPoint*)), this, SLOT(newLogPoint(TrackPoint*)));

		ui.action_Read_Log->setDisabled(false);
	}
}

void LogReader::openTTY(const char* name, int speed) {

	m_device_fd = open(name, O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
    m_device_file = new QFile();

	bool openres = m_device_file->open(m_device_fd, QIODevice::ReadWrite);
	if (m_device_fd == -1 || openres == false) {
		qDebug("failed to open device %s with speed %d.", name, speed);
	} else {

		// int fd,c, res;
		struct termios newtio;

		tcgetattr(m_device_fd, &m_oldtio); /* save current port settings */

		bzero(&newtio, sizeof(newtio));
		newtio.c_cflag = CRTSCTS | CS8 | CLOCAL | CREAD;
		newtio.c_iflag = IGNPAR;
		newtio.c_oflag = 0;

		/* set input mode (non-canonical, no echo,...) */
		newtio.c_lflag = 0;

		newtio.c_cc[VTIME] = 0; /* inter-character timer unused */
		newtio.c_cc[VMIN] = 5; /* blocking read until 5 chars received */

		tcflush(m_device_fd, TCIFLUSH);
		tcsetattr(m_device_fd, TCSANOW, &newtio);

		m_socket_notifier
				= new QSocketNotifier(m_device_fd, QSocketNotifier::Read);
		connect(m_socket_notifier, SIGNAL(activated(int)), this, SLOT(readDevice(int)));
		readDevice(m_device_fd);
	}
}

void LogReader::closeTTY() {

	if(m_device_file != 0) {
		m_device_file->close();
		delete m_device_file;
		m_device_file = 0;
	}

	disconnect(this, SLOT(readDevice(int)) );
	delete m_socket_notifier;
	m_socket_notifier = 0;

	if(m_device_fd != -1) {
		tcsetattr(m_device_fd, TCSANOW, &m_oldtio);
		::close(m_device_fd);
		m_device_fd = -1;
	}

}

void LogReader::readDevice(int dev_fd) {
	static char buffer[4096 + 1];
	int bytes_read;
	if (dev_fd == m_device_fd) {
		bytes_read = read(m_device_fd, buffer, 4096);
		QByteArray data(buffer, bytes_read);
		emit emitData(data);
	}
}


void LogReader::sendData(QByteArray data) {
	if(m_device_fd != -1) {
		write(m_device_fd, data.data(), data.size());
	}
}


void LogReader::disconnectDevice() {
	if(m_device_io != 0) {
		disconnect(m_device_io, SLOT(addData(QByteArray)));
		disconnect(m_device_io, SIGNAL(sendData(QByteArray)), this, SLOT(sendData(QByteArray)));
		disconnect(m_device_io, SIGNAL(nemaString(QString)), ui.nemaText, SLOT(appendPlainText(QString)));

		disconnect(m_device_io, SIGNAL(progress(int)), this, SLOT(progress(int)));

		disconnect(m_device_io, SIGNAL(readLogFinished()), this, SLOT(readLogFinished()));
		disconnect(m_device_io, SIGNAL(cancelReadLog()), this, SLOT(cancelReadLog()));

		disconnect(m_device_io, SIGNAL(newTrack(Track*)), this, SLOT(newTrack(Track*)));
		disconnect(m_device_io, SIGNAL(newWayPoint(TrackPoint*)), this, SLOT(newWayPoint(TrackPoint*)));
		disconnect(m_device_io, SIGNAL(newLogPoint(TrackPoint*)), this, SLOT(newLogPoint(TrackPoint*)));

		ui.action_Read_Log->setDisabled(true);

		delete m_device_io;

		m_device_io = 0;

		closeTTY();

	}
}

void LogReader::readLog() {

	if(m_device_io == 0) {
		connectDevice();
	}
	if(m_device_io == 0) {
		return;
	}

	progress(0);
	m_progress_dlg->show();

    m_device_io->readLog();

	//if (m_command_mode_step != 0) {
	//	qDebug("already in command mode.");
	//	return;
	//}
	//m_command_mode_step++;

	//m_dev_data = new DeviceData();

	//enterCommandMode(m_command_mode_step);
}

void LogReader::progress(int percent) {
	prg_dlg.progressBar->setValue(percent);
}

void LogReader::cancelReadLog() {
	m_device_io->cancelReadLog();
	readLogFinished();
}

void LogReader::readLogFinished() {
	m_progress_dlg->close();
}

void LogReader::newTrack(Track* track) {
	track->setIndex(m_track_collection->size());
	m_track_collection->appendTrack(track);

	ui.treeView->resizeColumnToContents(0);
	ui.treeView->resizeColumnToContents(1);
	ui.treeView->resizeColumnToContents(2);
	ui.treeView->resizeColumnToContents(3);

	prg_dlg.m_num_tracks->setText(QString().number(m_track_collection->size()));

	m_track_view->update();
}

void LogReader::newWayPoint(TrackPoint* tp) {

}

void LogReader::newLogPoint(TrackPoint* tp) {

	prg_dlg.m_num_logpoints->setText(QString().number(m_track_collection->getNumWaypoints()));

}

void LogReader::startRecording() {

}

void LogReader::stopRecording() {

}



void LogReader::actionTriggered() {
	openTTY("/dev/rfcomm0", 115200);
	emit setText(QString("Hallo"));
	qDebug("action triggered");
}

void LogReader::treeViewClicked(QModelIndex index) {
	//qDebug() << QString("treeViewClicked (%1,%2)").arg(index.row()).arg(index.column());
}

void LogReader::selectionChanged(QItemSelection selected,QItemSelection deselected) {
	qDebug() << QString("selction changed");
	QModelIndexList selected_indices = m_selection_model->selectedIndexes();
    m_track_collection->setModelIndexList(selected_indices);
    m_track_view->update();
}




void LogReader::addData(QByteArray data) {
		if(m_expect_binary_data == 0) {
			m_nema_string.append(data);
			do {
				m_line = readLine();
				if (m_line.size() != 0) {
					// qDebug() << QString("setLine: %1 !end!").arg(m_line);
					emit setText(m_line);
					parseLine(m_line);

					enterCommandMode(m_command_mode_step);
				}
			} while(m_line.size() != 0);
		}
		else {  // m_expect_binary_data > 0 -> read m_expect_binary_data bytes of binary data
			m_expect_binary_data -= data.size();
			// store data in m_tmp_buffer which is used to calc checksum and
			// will be appended to m_log_buf if checksum was correct.
			m_tmp_buf.append(data);
		}
		// qDebug("%s",buffer);
}

QString LogReader::readLine() {
	int pos;

	QString tmp_string;

	pos = m_nema_string.indexOf("\n");

	if (pos == -1) {
		// no end of line found in string. Line not complete yet.
		// return empty String and wait for next invocation.
		tmp_string.clear();
		return tmp_string;
	}

	tmp_string = m_nema_string.left(pos);
	m_nema_string = m_nema_string.right(m_nema_string.length() - pos - 1);

	int last_pos = tmp_string.lastIndexOf("\r");
	if(last_pos != -1)
	{
		tmp_string.chop(tmp_string.size() - last_pos );
	}
	return tmp_string;
}


void LogReader::enterCommandMode(int step) {
	switch (step) {
	case 1:
		qDebug("enterCommandMode step %d.", step);
		qDebug("send @AL,02,01\n");
		write(m_device_fd, "@AL,02,01\n", strlen("@AL,02,01\n"));
		sleep(1);
		m_command_mode_step++;
		// wait for readLine to finish ...
		break;

	case 2:
        qDebug("enterCommandMode step %d.", step);
        qDebug("send @AL\n");
        //qDebug("@AL,2,3\n");
        //qDebug("@AL,2,3\n");

		write(m_device_fd, "@AL\n", strlen("@AL\n"));
        //write(m_device_fd, "@AL\n", strlen("@AL\n"));
		//write(m_device_fd, "@AL,2,3\n", strlen("@AL,2,3\n"));
		//write(m_device_fd, "@AL,2,3\n", strlen("@AL,2,3\n"));

        m_command_mode_step++;
		break;

	case 3:
		if(m_command_response_step < 2)
		{
			// LoginOK not yet received
			//break;
		}
        qDebug("enterCommandMode step %d.", step);
        write(m_device_fd, "@AL,07,01\n", strlen("@AL,07,01\n"));
        m_command_mode_step++;
		break;

    case 4:
    	qDebug("enterCommandMode step %d.", step);
    	write(m_device_fd, "@AL,07,02\n", strlen("@AL,07,02\n"));
    	m_command_mode_step++;
    	break;

    case 5:
        qDebug("enterCommandMode step %d.", step);
        write(m_device_fd, "@AL,07,03\n", strlen("@AL,07,03\n"));
        m_command_mode_step++;
        break;

    case 6:
        qDebug("enterCommandMode step %d. => @AL,05,01", step);
        write(m_device_fd, "@AL,05,01\n", strlen("@AL,05,01\n"));
        write(m_device_fd, "@AL,05,01\n", strlen("@AL,05,01\n"));
        // m_command_mode_step++;
        break;

    case 7:
        qDebug("enterCommandMode step %d. => @AL,05,02", step);
        write(m_device_fd, "@AL,05,02\n", strlen("@AL,05,02\n"));
        // m_command_mode_step++;
        break;

    case 8:
        qDebug("enterCommandMode step %d. => @AL,05,09", step);
        write(m_device_fd, "@AL,05,09\n", strlen("@AL,05,09\n"));
        // m_command_mode_step++;
        break;

    case 9:
        qDebug("enterCommandMode step %d. => @AL,05,10", step);
        write(m_device_fd, "@AL,05,10\n", strlen("@AL,05,10\n"));
        // m_command_mode_step++;
        break;

    default:
    	break;
	}
}


void LogReader::leaveCommandMode()
{
	m_expect_binary_data = 0;
	m_command_mode_step = 0;
	m_command_response_step = 0;
	// Exit command mode

    write(m_device_fd, "@AL,02,01\n", strlen("@AL,02,01\n"));
}

void LogReader::parseLine(QString line) {
	qDebug() << QString("parseLine: ") << line;

	if (m_command_mode_step == 0) {
		parseNEMA(line);
	} else {
		parseAL(line);
	}
}

void LogReader::parseAL(QString line) {

    // expect the responses from the set to command mode state machine.
	// wait for LoginOK. If received, switchng to command mode was successful
	// and we can continue reading out data. In thins state m_command_response_step in 2.
    QString expectstr("@AL,LoginOK");
    //qDebug() << QString("expecting line %1: %2").arg(m_command_response_step).arg(expectstr);
    if (expectstr.compare(line) == 0) {
            qDebug("got LoginOK, proceeding... ");
            m_command_response_step = 2;
            return;
    }


    // get device name (usually WBT201)
    expectstr = QString("@AL,07,01,");
    if (line.startsWith(expectstr)) {
    	QString model = line.section(',', 3, 3);
        qDebug() << QString("model = %1").arg(model);
        m_dev_data->setDeviceName(model);
        return;
    }

    // get device info
    expectstr = QString("@AL,07,02,");
    if (line.startsWith(expectstr)) {
        QString info = line.section(',', 3, 3);
        qDebug() << QString("device info = %1.").arg(info);
        m_dev_data->setDeviceInfo(info);
        return;
    }

    // get device serial No
    expectstr = QString("@AL,07,03,");
    if (line.startsWith(expectstr)) {
        QString serial = line.section(',', 3, 3);
        qDebug() << QString("device serial No = %1.").arg(serial);
        m_dev_data->setDeviceSerial(serial);
        return;
    }

    // get log start address
    expectstr = QString("@AL,05,01,");
    if (line.startsWith(expectstr)) {
        QString log_start_str = line.section(',', 3, 3);
        long logstart = log_start_str.toLong();
        qDebug() << QString("Log start = %1. As int %2").arg(log_start_str).arg(logstart);
        m_dev_data->setLogStart(logstart);
        m_command_mode_step++;
        if(m_dev_data->complete()) {
        	readLogMode();
        }
        return;
    }

    // get log end address
    expectstr = QString("@AL,05,02,");
    if (line.startsWith(expectstr)) {
        QString log_end_str = line.section(',', 3, 3);
        long logend = log_end_str.toLong();
        qDebug() << QString("Log end = %1. As int %2").arg(log_end_str).arg(logend);
        m_dev_data->setLogEnd(logend);
        m_command_mode_step++;
        if(m_dev_data->complete()) {
        	readLogMode();
        }
        return;
    }

    // get log area start address
    expectstr = QString("@AL,05,09,");
    if (line.startsWith(expectstr)) {
        QString log_area_start_str = line.section(',', 3, 3);
        long logareastart = log_area_start_str.toLong();
        qDebug() << QString("Log area start = %1. As int %2").arg(log_area_start_str).arg(logareastart);
        m_dev_data->setLogAreaStart(logareastart);
        m_command_mode_step++;
        if(m_dev_data->complete()) {
        	readLogMode();
        }
        return;
    }

    // get log area end address
    expectstr = QString("@AL,05,10,");
    //qDebug() << QString("expecting line %1: %2").arg(m_command_response_step).arg(expectstr);
    if (line.startsWith(expectstr)) {
        QString log_area_end_str = line.section(',', 3, 3);
        long logareaend = log_area_end_str.toLong();
        qDebug() << QString("Log area end = %1. As int %2").arg(log_area_end_str).arg(logareaend);
        m_dev_data->setLogAreaEnd(logareaend);
        m_command_mode_step++;
        if(m_dev_data->complete()) {
        	readLogMode();
        }
        return;
    }

    // get checksum over received binary data
    expectstr = QString("@AL,CS,");
    //qDebug() << QString("expecting line %1: %2").arg(m_command_response_step).arg(expectstr);
    if (line.startsWith(expectstr)) {
        QString checksum_str = line.section(',', 2, 2);
        qDebug() << QString("checksum string = %1.").arg(checksum_str);
        // if(checksumCorrect) {
        m_log_buf.append(m_tmp_buf);
        m_retry_count = 5;

        if(m_lastsection == 1 || m_tmp_buf.size() == 0) {
        	createTrackpoints();
        	leaveCommandMode();
            return;
        }
        m_read_start += m_tmp_buf.size();

        readLogData();
        return;
    }

}

void LogReader::readLogMode() {
    m_read_start = m_dev_data->getLogStart();
    m_retry_count = 5;
    m_lastsection = false;
    m_blocksize = 4096;

    m_command_response_step = 3;

    m_log_buf.clear();
    m_log_buf.reserve((m_dev_data->getLogAreaEnd() - m_dev_data->getLogAreaStart()));

    readLogData();
}

void LogReader::readLogData() {

	int logstart = m_dev_data->getLogStart();
	int logend = m_dev_data->getLogEnd();

	int logareastart = m_dev_data->getLogAreaStart();
	int logareaend = m_dev_data->getLogAreaEnd();

    qDebug() << QString("Logarea: %1 - %2").arg(logareastart).arg(logareaend);
    qDebug() << QString("Log: %1 - %2").arg(logstart).arg(logend);

    int trackpointlen = 16;
    int log_capacy = (m_dev_data->getLogAreaEnd() - m_dev_data->getLogAreaStart())
				     / trackpointlen;

    if (log_capacy < m_blocksize) {
    	m_expect_binary_data = log_capacy;
        m_lastsection = true;
    }
    else if(logstart + m_blocksize >= logend) {
    	m_expect_binary_data = logend - logstart;
        m_lastsection = true;
    }
    else if(m_read_start + m_blocksize >= logend) {
        m_expect_binary_data = logend - m_read_start;
        m_lastsection = true;
        qDebug() << QString("re3adin last rest at %1 length %2.").arg(m_read_start).arg(logend - m_read_start);
    }
    else {
    	m_expect_binary_data = m_blocksize;
    }
//    if(m_read_start >= m_dev_data->getLogAreaEnd()) {
//        m_read_start = m_dev_data->getLogAreaStart();
//    }
//    if (m_read_start < m_dev_data->getLogEnd() &&
//            m_read_start + m_blocksize >= m_dev_data->getLogEnd()) {
//        m_read_count = m_dev_data->getLogEnd() - m_read_start;
//        m_lastsection = 1
//    }


    char cmd_buf[32];
    snprintf(cmd_buf, 32, "@AL,05,03,%d\n", m_read_start);
    m_binary_data_already_read = 0;
    m_tmp_buf.clear();

    write(m_device_fd, cmd_buf, strlen(cmd_buf));

}

void LogReader::createTrackpoints() {
	FILE* fd;
	Track* track = 0;
	fd = fopen("outfile2.tkraw", "wb");
    qDebug() << QString("createTrackpoints()");
    int trackindex = 0;

    m_track_collection->clear();

	for(int pos = 0; pos < m_log_buf.size(); pos += TrackPoint::size()) {
		fwrite(m_log_buf.mid(pos, TrackPoint::size()).data(), m_log_buf.mid(pos, TrackPoint::size()).size(), 1, fd);
		TrackPoint* tp = new TrackPoint(m_log_buf.mid(pos, TrackPoint::size()));


		if(tp->isLogPoint()) {
			m_track_collection->getWaypoints()->append(tp);

		}
		else {
			if(tp->isBeginOfTrack()) {
				if(track != 0) {
					track->commit();
					qDebug() << QString("End of Track (%1 - %2 , %3 - %4)").arg(track->getMinLong()).arg(track->getMaxLong()).arg(track->getMinLat()).arg(track->getMaxLat());
				}
				track = new Track();
				track->setIndex(trackindex);
				trackindex++;
				m_track_collection->append(track);
			}
			track->append(tp);
		}

	}
	track->commit();
	m_track_view->setTrackColletcion(m_track_collection);
	m_track_collection->commit();

	ui.treeView->resizeColumnToContents(0);
	ui.treeView->resizeColumnToContents(1);
	ui.treeView->resizeColumnToContents(2);
	ui.treeView->resizeColumnToContents(3);
	fclose(fd);

	m_track_view->update();
}

void LogReader::parseNEMA(QString line) {
	qDebug() << line;
}

void LogReader::loadTrack() {
	FILE* fd;
	char buffer[32];
    int bytes_read = 0;

    QString filename( QFileDialog::getOpenFileName( this,  tr("Open Track"),QString::null,  tr("GPX Tracks (*.gpx);;Google Earth Tracks (*.kml *.kmz);;Wintec TK1 Tracks (*.tk1);;Raw Wintec Tracklogs (*.tkraw)")) );
    if ( filename.isEmpty() )
        return;


	if(filename.endsWith(".gpx", Qt::CaseInsensitive)) {
		// load from GPX file
		gpxFile gpx_file;
		m_track_collection = gpx_file.read(filename);
	}
	else if(m_track_filename.endsWith(".kml", Qt::CaseInsensitive)) {
		//kmlFile kml_file;
		//kml_file.read(m_track_collection, filename);
		// load from kml file

	}
	else if(m_track_filename.endsWith(".kmz", Qt::CaseInsensitive)) {
		// load from kmz file

	}
	else if(m_track_filename.endsWith(".tk1", Qt::CaseInsensitive)) {
		tk1File tk1_file;
		m_track_collection = tk1_file.read(filename);
		// load from as tk1 file

	}
	else {
		 // QMessageBox::warning(this, tr("Track Editor"),
		 //                          tr("Unknown file type. TrackEditor is only\n"
		 //                            "able to load raw tk1 files."),
		 //                           QMessageBox::Discard);
	}

	m_log_buf.clear();
	fd = fopen(filename.toLatin1(), "rb");
	do {
		bytes_read = fread(buffer, TrackPoint::size(), 1, fd);
		m_log_buf.append(QByteArray(buffer,TrackPoint::size()));
	} while( bytes_read != 0);
	fclose(fd);

	createTrackpoints();
}


void LogReader::saveTrack() {
	if(m_track_filename.isEmpty()) {
		saveTrackAs();
	}
	else {
		save();
	}
}

void LogReader::saveTrackAs() {
    m_track_filename = QFileDialog::getSaveFileName( this,  tr("Save Track As"),QString::null,  tr("GPX Tracks (*.gpx);;Google Earth Tracks (*.kml *.kmz);;Wintec TK1 Tracks (*.tk1)"));
    if ( m_track_filename.isEmpty() )
        return;

    save();
}

void LogReader::save() {
	if(m_track_filename.endsWith(".gpx", Qt::CaseInsensitive)) {
		// save as GPX file
		gpxFile gpx_file;
		gpx_file.write(m_track_collection, m_track_filename);
	}
	else if(m_track_filename.endsWith(".kml", Qt::CaseInsensitive)) {
		//kmlFile kml_file;
		//kml_file.write(m_track_collection, m_track_filename);
		// save as kml file

	}
	else if(m_track_filename.endsWith(".kmz", Qt::CaseInsensitive)) {
		// save as kmz file

	}
	else if(m_track_filename.endsWith(".tk1", Qt::CaseInsensitive)) {
		tk1File tk1_file;
		tk1_file.write(m_track_collection, m_track_filename);
		// save as tk1 file

	}
	else {
		 QMessageBox::warning(this, tr("Track Editor"),
		                           tr("Unknown file type. TrackEditor is only\n"
		                              "able to save GPX, KML, KMZ and TK1 files."),
		                            QMessageBox::Discard);
	}


}


void LogReader::load(QString filename) {


}
