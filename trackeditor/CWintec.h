/*
 * CWintec.h
 *
 *  Created on: 26.08.2008
 *      Author: martin
 */

#ifndef CWINTEC_H_
#define CWINTEC_H_


#include <QTimer>
#include <stdint.h>

#include "IDeviceIO.h"

class DeviceData;


class CWintec: public IDeviceIO {
	Q_OBJECT;

public:
	CWintec(QString name);
	virtual ~CWintec();

	QList<enum interfaces_t> getInterfaceList();
	CSerialPortSettings getSerialPortSettings(enum interfaces_t) const;

	bool readLog();
	void cancelReadLog();



public slots:
	void addData(QByteArray);

    void timeout();

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
    TrackPoint* dataToWayPoint(QByteArray data);
    void parseWayPoints(QByteArray data);

    bool checksumCorrect(QByteArray data, QString checksum);

    void save();
    void load(QString filename);

    Track* m_tmp_track;
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

    // Three variables to keep track of device commands and its responses
    // m_timer to have a timeout to each request
    QTimer* m_timer;
    // m_retry_count to count number of retris after timeout or unexpected responses
    int m_retry_count;
    const int m_num_retries;
    // m_step_complete will be set to true when the expcted response was received
    // and toggled to false again after next request was sent to device
    bool m_step_complete;

    QByteArray m_log_buf;
    QByteArray m_tmp_buf;

    int m_read_start;
    int m_expect_binary_data;
    int m_binary_data_already_read;
    bool m_lastsection;
    int m_blocksize;

    const int m_timeout_in_ms;

//    TrackCollection *m_track_collection;
//    QItemSelectionModel* m_selection_model;

    QString m_track_filename;


};

#endif /* CWINTEC_H_ */
