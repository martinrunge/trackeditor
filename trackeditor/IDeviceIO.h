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

class IDeviceIO: public QObject {
	Q_OBJECT

public:
	IDeviceIO(QString name);
	virtual ~IDeviceIO();
	virtual QStringList getInterfaceList();

	virtual bool readLog();
	virtual void cancelReadLog();

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
