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
	bool isValid() { return m_valid; };

public slots:
	void chooseDeviceFile();
	void textChanged(QString);

signals:
	void setValid(bool);

private:
	CSerialPortSettings m_settings;
	CDeviceFileValidator* m_validator;

	bool m_valid;
};

#endif /* CGENERICSERIALDEVICE_H_ */
