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
#include "ui_TrackEditor.h"
#include "TrackPoint.h"
#include "Track.h"
#include "TrackCollection.h"


class QSocketNotifier;
class DeviceData;
class TrackView;
class QStandardItemModel;
class QStandardItem;
class QItemSelectionModel;

class LogReader : public QMainWindow
{
    Q_OBJECT

public:
    LogReader(QWidget *parent = 0);
    ~LogReader();

signals:
    void setText(QString);

public slots:
    void actionTriggered();
    void readDevice(int dev_fd);

    void readLog();
    void loadTrack();
    void saveTrack();
    void saveTrackAs();

    void treeViewClicked(QModelIndex index);
    void selectionChanged(QItemSelection,QItemSelection);

private:
    Ui::TrackEditor2Class ui;
    TrackView *m_track_view;


    void openTty(const char* name, int speed);
    void enterCommandMode(int step = 0);
    void readLogMode();
    void leaveCommandMode();

    QString readLine();
    void parseLine(QString line);
    void parseNEMA(QString line);
    void parseAL(QString line);

    void readLogData();

    void createTrackpoints();

    void save();
    void load(QString filename);

    DeviceData* m_dev_data;

    int m_command_mode_step;

    // command_response_step:
    // 0: NEMA mode
    // 1: command mode, not yet logged in
    // 2: logged in (LoginOK received)
    // 3: command mode complete. Read out data...
    int m_command_response_step;

    int m_device_fd;
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