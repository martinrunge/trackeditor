/*
 * DeviceData.h
 *
 *  Created on: 30.07.2008
 *      Author: martin
 */

#ifndef DEVICEDATA_H_
#define DEVICEDATA_H_

#include <QString>

class DeviceData {
public:
	DeviceData();
	virtual ~DeviceData();

    inline QString getDeviceName() const
    {
        return deviceName;
    }

    inline void setDeviceName(QString deviceName)
    {
        this->deviceName = deviceName;
    }

    inline QString getDeviceInfo() const
    {
        return deviceInfo;
    }

    inline void setDeviceInfo(QString deviceInfo)
    {
        this->deviceInfo = deviceInfo;
    }

    inline QString getDeviceSerial() const
    {
        return deviceSerial;
    }

    inline void setDeviceSerial(QString deviceSerial)
    {
        this->deviceSerial = deviceSerial;
    }

    inline int getLogStart() const
    {
        return logStart;
    }

    inline void setLogStart(int logStart)
    {
        this->logStart = logStart;
        this->logStartSet = true;
    }

    inline int getLogEnd() const
    {
        return logEnd;
    }

    inline void setLogEnd(int logEnd)
    {
        this->logEnd = logEnd;
        this->logEndSet = true;
    }

    inline int getLogAreaStart() const
    {
        return logAreaStart;
    }

    inline void setLogAreaStart(int logAreaStart)
    {
        this->logAreaStart = logAreaStart;
        this->logAreaStartSet = true;
    }

    inline int getLogAreaEnd() const
    {
        return logAreaEnd;
    }

    inline void setLogAreaEnd(int logAreaEnd)
    {
        this->logAreaEnd = logAreaEnd;
        this->logAreaEndSet = true;
    }

    bool complete() {
    	if(logStartSet && logEndSet && logAreaStartSet && logAreaEndSet)
    		return true;
    	else
    		return false;
    }

private:
	QString deviceName;
	QString deviceInfo;
	QString deviceSerial;

	int logStart;
	int logEnd;
	int logAreaStart;
	int logAreaEnd;

	bool logStartSet;
	bool logEndSet;
	bool logAreaStartSet;
	bool logAreaEndSet;


};

#endif /* DEVICEDATA_H_ */
