/*
 * IDeviceIO.cpp
 *
 *  Created on: 26.08.2008
 *      Author: martin
 */

#include "IDeviceIO.h"

IDeviceIO::IDeviceIO(QString name) {
	m_device_name = name;
}

IDeviceIO::~IDeviceIO() {
	m_device_name.clear();
}

QStringList IDeviceIO::getInterfaceList() {
	return QStringList();
}

bool IDeviceIO::readLog() {
	return false;
}
