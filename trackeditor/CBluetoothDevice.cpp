/*
 * CBluetoothDevice.cpp
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */
#include <QDebug>
#include <QtDBus/QDBusPendingCall>
#include <QtDBus/QDBusPendingCallWatcher>

#include "CBluetoothDevice.h"
#include "DeviceListWidgetItem.h"

CBluetoothDevice::CBluetoothDevice()
	:m_conn(QDBusConnection::systemBus())
	,m_discovery_active(false)
	,m_valid(false)
{

	m_ui = new Ui::bluetoothwidget();
	m_ui->setupUi(this);

	connect(m_ui->startDiscoveryButton, SIGNAL(clicked()), this, SLOT(startDiscovery()));
	connect(m_ui->stopDiscoveryButton, SIGNAL(clicked()), this, SLOT(stopDiscovery()));
	connect(m_ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(deviceSelected(QListWidgetItem*, QListWidgetItem*)));

	m_manager = new QDBusInterface("org.bluez", "/", "org.bluez.Manager", m_conn );

	QDBusReply<QDBusObjectPath> reply = m_manager->call("DefaultAdapter");
	QDBusObjectPath path;
	if ( reply.isValid() )
	{
		path = reply.value();

		qDebug() << QString("Found default adapter at: %1").arg(path.path());
		m_adapter = new QDBusInterface("org.bluez", path.path(), "org.bluez.Adapter", m_conn );
		m_adapter->connection().connect("org.bluez", path.path(), "org.bluez.Adapter", "DeviceFound", this, SLOT(deviceFound(QString, QMap<QString,QVariant>)));
		//m_adapter->connection().connect(m_adapter, SIGNAL(DeviceFound(const QString&, const QMap<QString,QVariant>)&), this, SLOT(deviceFound(QString, QMap<QString,QVariant>)));
	}
	else
	{
		qDebug() << QString("DefaultAdatper not found!");
	}
		//	connect(m_if, SIGNAL(DeviceRemoved(QString)), this, SLOT(deviceRemoved(QString)));

	//getDeviceList();

}

CBluetoothDevice::~CBluetoothDevice() {
	if(m_discovery_active)
		stopDiscovery();
	delete m_adapter;
	delete m_manager;
	delete m_ui;
}


QString CBluetoothDevice::getDeviceFileName() {
	return m_device_file_name;
}

void CBluetoothDevice::startDiscovery()
{
	m_ui->listWidget->clear();
	m_adapter->call("StartDiscovery");
	m_discovery_active = true;
}

void CBluetoothDevice::stopDiscovery()
{
	m_adapter->call("StopDiscovery");
	m_discovery_active = false;
}


void CBluetoothDevice::deviceFound(const QString& address, const QMap<QString,QVariant>& properties) {
	qDebug() << QString("DeviceFound: %1").arg(address);

	bool included = false;
	for(int i = 0; i < m_ui->listWidget->count(); i++)
	{
		DeviceListWidgetItem* item = reinterpret_cast<DeviceListWidgetItem*>(m_ui->listWidget->item(i));
		QString addr = item->data(Qt::UserRole + 1).toString();
		if(addr.compare(address) == 0)
		{
			included = true;
			break;
		}
	}
	if(included == false )
	{
		DeviceListWidgetItem* item = new DeviceListWidgetItem;
		item->setText(address);
		item->setData(Qt::UserRole + 1, QVariant(address));
		m_ui->listWidget->addItem(item);
	}
}

void CBluetoothDevice::deviceSelected(QListWidgetItem *current, QListWidgetItem *previous)
{
	DeviceListWidgetItem* item = reinterpret_cast<DeviceListWidgetItem*>(current);
	QString address = item->data(Qt::UserRole + 1).toString();
	m_ui->macAddressValue->setText(address);

	m_adapter->call("CreateDevice", address);

	QDBusReply<QDBusObjectPath> reply = m_adapter->call("FindDevice", address);
	QDBusObjectPath path;
	if ( reply.isValid() )
	{
		path = reply.value();
		qDebug() << QString("DevicePath: %1").arg(path.path());
	}

	QDBusInterface serial("org.bluez", path.path(), "org.bluez.Serial", m_conn);
	QDBusReply<QString> reply2 = serial.call("Connect", "spp");

	if ( reply2.isValid() )
	{
		m_device_file_name = reply2.value();
		m_ui->deviceFileLabel->setText(m_device_file_name);
		qDebug() << QString("Device File: %1").arg(m_device_file_name);

		m_valid = true;
		emit setValid(m_valid);
	}
	else
	{
		m_valid = false;
	}

//		serial = dbus.Interface(session_bus.get_object('org.bluez',path),
//	                                "org.bluez.Serial")

//	    node = serial.Connect(service)
//	    print "Connected %s to %s" % (node, address)

}

