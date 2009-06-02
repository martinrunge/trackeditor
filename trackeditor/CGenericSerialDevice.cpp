/*
 * CGenericSerialDevice.cpp
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#include "CGenericSerialDevice.h"

CGenericSerialDevice::CGenericSerialDevice() {

	Ui::genericserialwidget widget;
	widget.setupUi(this);
}

CGenericSerialDevice::~CGenericSerialDevice() {
	// TODO Auto-generated destructor stub
}


CSerialPortSettings CGenericSerialDevice::getSerialPortSettings() const
{
	CSerialPortSettings settings;
	return settings;
}
