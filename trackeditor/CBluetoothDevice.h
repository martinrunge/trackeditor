/*
 * CBluetoothDevice.h
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#ifndef CBLUETOOTHDEVICE_H_
#define CBLUETOOTHDEVICE_H_

#include <QTabWidget>
#include "ui_bluetoothwidget.h"


class CBluetoothDevice : public QTabWidget  {
public:
	CBluetoothDevice();
	virtual ~CBluetoothDevice();
	QString getDeviceFileName();
private:
	QString m_device_file_name;
};

#endif /* CBLUETOOTHDEVICE_H_ */
