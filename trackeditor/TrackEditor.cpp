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

	// set m_track_collection to 0 to prevent setTrackCollection() from trying to delete it.
	m_track_collection = 0;

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

	m_track_view = new TrackView(ui.scrollArea);
	ui.scrollArea->setWidget(m_track_view);

	connect(ui.zoomSlider, SIGNAL(valueChanged(int)), m_track_view, SLOT(zoomValueChanged(int)));

	ui.treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_selection_model = ui.treeView->selectionModel();
    connect(m_selection_model, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection,QItemSelection)));

	setTrackCollection(new TrackCollection);

    m_device_io = 0;
	m_dev_data = 0;
	m_expect_binary_data = 0;

	m_command_mode_step = 0;
	m_command_response_step = 0;

	m_track_filename.clear();

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


void LogReader::setTrackCollection(TrackCollection* track_collection) {
//	m_track_collection.clear();

	TrackCollection* tmp_tc = m_track_collection;
	m_track_collection = track_collection;

	m_track_view->setTrackColletcion(m_track_collection);
    ui.treeView->setModel(m_track_collection);

	ui.treeView->resizeColumnToContents(0);
	ui.treeView->resizeColumnToContents(1);
	ui.treeView->resizeColumnToContents(2);
	ui.treeView->resizeColumnToContents(3);

	if(tmp_tc != 0) {
		delete tmp_tc;
	}

    disconnect(m_selection_model, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection,QItemSelection)));
    m_selection_model = ui.treeView->selectionModel();
    connect(m_selection_model, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection,QItemSelection)));

	m_track_view->update();

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
					track->setIndex(trackindex);
					qDebug() << QString("End of Track (%1 - %2 , %3 - %4)").arg(track->getMinLong()).arg(track->getMaxLong()).arg(track->getMinLat()).arg(track->getMaxLat());
				}
				track = new Track();
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
		TrackCollection* tc = gpx_file.read(filename);
		setTrackCollection(tc);
		return;
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
