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
	Q_OBJECT;
public:
	CGenericSerialDevice();
	virtual ~CGenericSerialDevice();

	QString getDeviceFileName();
	const CSerialPortSettings getSerialPortSettings();

	Ui::genericserialwidget *m_ui;

public slots:
	void chooseDeviceFile();

private:
	CSerialPortSettings m_settings;
};

#endif /* CGENERICSERIALDEVICE_H_ */
