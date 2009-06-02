/*
 * CBluetoothDevice.cpp
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#include "CBluetoothDevice.h"

CBluetoothDevice::CBluetoothDevice() {

	Ui::bluetoothwidget widget;
	widget.setupUi(this);

}

CBluetoothDevice::~CBluetoothDevice() {
	// TODO Auto-generated destructor stub
}


QString CBluetoothDevice::getDeviceFileName() {
	return m_device_file_name;
}
