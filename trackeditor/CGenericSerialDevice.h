/*
 * CGenericSerialDevice.h
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#ifndef CGENERICSERIALDEVICE_H_
#define CGENERICSERIALDEVICE_H_

#include <QTabWidget>
#include "ui_serialwidget.h"
#include "CSerialPortSettings.h"

class CGenericSerialDevice : public QTabWidget {
public:
	CGenericSerialDevice();
	virtual ~CGenericSerialDevice();

	QString getDeviceFileName();
	CSerialPortSettings getSerialPortSettings() const;
};

#endif /* CGENERICSERIALDEVICE_H_ */
