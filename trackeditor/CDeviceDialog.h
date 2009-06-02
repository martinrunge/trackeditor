/*
 * CDeviceDialog.h
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#ifndef CDEVICEDIALOG_H_
#define CDEVICEDIALOG_H_

#include <QtGui/QDialog>
#include "ui_DeviceDialog.h"
#include "CSerialPortSettings.h"

class LogReader;

class CDeviceDialog : public QDialog
{
    Q_OBJECT
public:
	CDeviceDialog(LogReader *parent = 0);
	virtual ~CDeviceDialog();

	void setPortSettings(CSerialPortSettings settings);
	CSerialPortSettings getPortSettings();

public slots:
	void modelChanged(int index);
	void interfaceChanged(int index);

	void accept();
	void reject();


private:
	Ui::DeviceDialog* m_dlg;

	CSerialPortSettings m_port_settings;
};

#endif /* CDEVICEDIALOG_H_ */
