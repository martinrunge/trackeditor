/*
 * CUsbDevice.cpp
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#include <QDebug>
#include <QtDBus/QDBusPendingCall>
#include <QtDBus/QDBusPendingCallWatcher>


#include "CUsbDevice.h"
#include "DeviceListWidgetItem.h"

CUsbDevice::CUsbDevice() : m_conn(QDBusConnection::systemBus()), m_valid(false){

	m_ui = new Ui::usbwidget();
	m_ui->setupUi(this);

	m_if = new QDBusInterface("org.freedesktop.Hal", "/org/freedesktop/Hal/Manager", "org.freedesktop.Hal.Manager", m_conn );

	connect(m_if, SIGNAL(DeviceAdded(QString)), this, SLOT(deviceAdded(QString)));
	connect(m_if, SIGNAL(DeviceRemoved(QString)), this, SLOT(deviceRemoved(QString)));

	getDeviceList();

	connect(m_ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
			this, SLOT(currentItemChanged(QListWidgetItem*, QListWidgetItem*)));

	currentItemChanged(0,0);
}

CUsbDevice::~CUsbDevice() {
	delete m_if;
	delete m_ui;
}

QString CUsbDevice::getDeviceFileName() {
	DeviceListWidgetItem* item = reinterpret_cast<DeviceListWidgetItem*>(m_ui->listWidget->currentItem());
	m_device_file_name = item->data(Qt::UserRole).toString();
	return m_device_file_name;
}

void CUsbDevice::currentItemChanged( QListWidgetItem * current, QListWidgetItem * previous)
{
	QListWidgetItem* item = m_ui->listWidget->currentItem();

	if(item != 0 && m_valid == false)
	{
		m_valid = true;
		emit setValid(m_valid);
	}
	else if( item == 0 && m_valid == true )
	{
		m_valid = false;
		emit setValid(m_valid);
	}
}


void CUsbDevice::getDeviceList() {
	// QDBusReply<QStringList> reply = m_if->call( "FindDeviceByCapability", "serial");
	QDBusPendingCall pcall = m_if->asyncCall( "FindDeviceByCapability", "serial");

	QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pcall, this);

	QObject::connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
	                      this, SLOT(deviceListReceived(QDBusPendingCallWatcher*)));
}


void CUsbDevice::deviceListReceived(QDBusPendingCallWatcher* result) {

	QDBusPendingReply<QStringList> reply = *result;
    if (reply.isError()) {
    	qDebug() << QString("Error in async reply.");
    } else {
    	m_ui->listWidget->clear();
    	QStringList  sl = reply.argumentAt<0>();
	    for(int i = 0; i < sl.size(); i++ ) {
	    	qDebug() << sl.at(i);
 			QDBusInterface devif("org.freedesktop.Hal", sl.at(i), "org.freedesktop.Hal.Device", m_conn );

 			QDBusReply<QString> reply = devif.call( "GetProperty", "serial.device");
 			QString interface;
 			if ( reply.isValid() )
 				interface = reply.value();

 			reply = devif.call( "GetProperty", "info.product");
 			QString name;
 			if ( reply.isValid() )
 				name = reply.value();

 			DeviceListWidgetItem* item = new DeviceListWidgetItem();
 			item->setText(QString("%1  (%2)").arg(interface).arg(name));
 			item->setData(Qt::UserRole, QVariant(interface));
 	 		m_ui->listWidget->addItem(item);
	    }
    }
}

void CUsbDevice::deviceAdded(QString objpath) {
	qDebug() << QString("deviceAdded: %1").arg(objpath);
	getDeviceList();
}

void CUsbDevice::deviceRemoved(QString objpath) {
	qDebug() << QString("DeviceRemoved: %1").arg(objpath);
	getDeviceList();
}

