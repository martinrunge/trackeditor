/*
 * CWintec.h
 *
 *  Created on: 26.08.2008
 *      Author: martin
 */

#ifndef CWINTEC_H_
#define CWINTEC_H_

#include "IDeviceIO.h"

class DeviceData;


class CWintec: public IDeviceIO {
public:
	CWintec(QString name);
	virtual ~CWintec();

	QStringList getInterfaceList();
	bool readLog();


public slots:
	void addData(QByteArray);

private:
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
//    struct termios m_oldtio;
//    QSocketNotifier* m_socket_notifier;

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

//    TrackCollection *m_track_collection;
//    QItemSelectionModel* m_selection_model;

    QString m_track_filename;


};

#endif /* CWINTEC_H_ */
