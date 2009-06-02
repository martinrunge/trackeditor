/*
 * IDeviceIO.cpp
 *
 *  Created on: 26.08.2008
 *      Author: martin
 */

#include "IDeviceIO.h"
#include <QString>
#include <QStringList>

IDeviceIO::IDeviceIO(QString name) {
	m_device_name = name;
	QMap<enum interfaces_t, QString> m_interface_names;
}

IDeviceIO::~IDeviceIO() {
	m_device_name.clear();
}


QStringList IDeviceIO::interfaceNames()
{
	QStringList stringlist;
	stringlist.append(tr("USB"));
	stringlist.append(tr("bluetooth"));
	stringlist.append(tr("generic serial device"));
	return stringlist;
}

QString IDeviceIO::interfaceName(enum interfaces_t index)
{
	return QString();
}

//QStringList IDeviceIO::getInterfaceList() {
//	return QStringList();
//}

bool IDeviceIO::readLog() {
	return false;
}

void IDeviceIO::cancelReadLog() {
	return;
}
