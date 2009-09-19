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

#ifndef QTTEST2_H
#define QTTEST2_H

#include <termios.h>

#include <QtGui/QMainWindow>
#include <QSettings>

#include "ui_TrackEditor.h"
#include "ui_ProgressDialog.h"

#include "TrackPoint.h"
#include "Track.h"
#include "TrackCollection.h"
#include "PlotData.h"

#include "CAnimation.h"

class QGridLayout;
class QSocketNotifier;
class DeviceData;
class TrackView;
class QStandardItemModel;
class QStandardItem;
class QItemSelectionModel;
class QFile;
class IDeviceIO;
class plotWidget;
class CDiagramsLayout;
class CSettings;
class QextSerialPort;

class LogReader : public QMainWindow
{
    Q_OBJECT

public:
    LogReader(QWidget *parent = 0);
    ~LogReader();

signals:
    void setText(QString);
    void emitData(QByteArray);

public slots:
    void actionTriggered();
    void readDevice();
    void readDevice(int dev_fd);

    void connectDevice();
    void disconnectDevice();

    void readLog();
    void progress(int percent);
    void cancelReadLog();
    void readLogFinished();

    void setTrackCollection(TrackCollection* track_collection);
    void newTrack(Track* track);
    void newWayPoint(TrackPoint* tp);
    void newLogPoint(TrackPoint* tp);

    void startRecording();
    void stopRecording();

    void loadTrack();
    void appendTrack();
    void saveTrack();
    void saveTrackAs();

    void showSettingsDlg();
    //void setDiagramQuantities(QStringList distVals, QStringList timeVals, QStringList trackPointVals);
    void setDiagramQuantities(QList<enum plotTypeY> distVals, QList<enum plotTypeY> timeVals, QList<enum plotTypeY> trackPointVals);

    void treeViewClicked(QModelIndex index);
    void selectionChanged(QItemSelection,QItemSelection);

    void markerChanged(double lat, double lng);
    void markerChangedDist(double dist);
    void markerChangedTime(double time);
    void markerChangedTrackPoint(double tp_index);



//    void addData(QByteArray data);
    void sendData(QByteArray data);

private:
    Ui::TrackEditor2Class ui;
    TrackView *m_track_view;
    plotWidget *m_plotWidget;
    QGridLayout *m_plotLayout;
    CDiagramsLayout *m_diagrams_layout;

    QStringList m_distVals;
    QStringList m_timeVals;
    QStringList m_trackPointVals;

    QDialog *m_progress_dlg;
    Ui::ProgressDialog prg_dlg;

    CSettings *m_settings;

    CAnimation m_animation;


    void openTTY(const char* name, int speed);
    void closeTTY();
    //void enterCommandMode(int step = 0);
    //void readLogMode();
    //void leaveCommandMode();

    //QString readLine();
    //void parseLine(QString line);
    void parseNEMA(QString line);
    //void parseAL(QString line);

    //void readLogData();

    // void createTrackpoints();

    void save();
    void load(QString filename);

    QextSerialPort* m_serial_port;
    IDeviceIO *m_device_io;

    DeviceData* m_dev_data;

    int m_command_mode_step;

    // command_response_step:
    // 0: NEMA mode
    // 1: command mode, not yet logged in
    // 2: logged in (LoginOK received)
    // 3: command mode complete. Read out data...
    int m_command_response_step;

    int m_device_fd;
    QFile* m_device_file;

    struct termios m_oldtio;
    QSocketNotifier* m_socket_notifier;

    QString m_nema_string;
    QString m_line;


    QByteArray m_log_buf;
    QByteArray m_tmp_buf;

    int m_read_start;
    int m_retry_count;
    int m_expect_binary_data;
    int m_binary_data_already_read;
    bool m_lastsection;
    int m_blocksize;

    TrackCollection *m_track_collection;
    QItemSelectionModel* m_selection_model;

    QString m_track_filename;
};

#endif // QTTEST2_H
