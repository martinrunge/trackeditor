/*
 * IDeviceIO.h
 *
 *  Created on: 26.08.2008
 *      Author: martin
 */

#ifndef IDEVICEIO_H_
#define IDEVICEIO_H_

#include <QObject>
#include <QString>
#include "TrackPoint.h"
#include "Track.h"

#include "CSerialPortSettings.h"

enum interfaces_t {E_USB, E_BLUETOOTH, E_GENERIC_SERIAL, E_LAST};

class IDeviceIO: public QObject {
	Q_OBJECT

public:
	IDeviceIO(QString name);
	virtual ~IDeviceIO();

	static QStringList interfaceNames();
	static QString interfaceName(enum interfaces_t index);

	virtual QList<enum interfaces_t> getInterfaceList() = 0;

	virtual bool readLog();
	virtual void cancelReadLog();

	virtual CSerialPortSettings getSerialPortSettings(enum interfaces_t interface) const = 0;
signals:
	void nemaString(QString);

	void progress(int percent);

	void newTrack(Track*);
	void newWayPoint(TrackPoint*);
	void newLogPoint(TrackPoint*);
	void sendData(QByteArray);
    void readLogFinished();
    void readLogFailed(QString);

public slots:
	virtual void addData(QByteArray) = 0;

private:
	QString m_device_name;
};

#endif /* IDEVICEIO_H_ */
