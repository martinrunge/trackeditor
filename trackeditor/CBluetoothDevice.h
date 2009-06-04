/*
 * CBluetoothDevice.h
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#ifndef CBLUETOOTHDEVICE_H_
#define CBLUETOOTHDEVICE_H_

#include <QtDBus/QtDBus>
#include <QString>
#include <QTabWidget>
#include "ui_bluetoothwidget.h"


class CBluetoothDevice : public QTabWidget  {
	Q_OBJECT;
public:
	CBluetoothDevice();
	virtual ~CBluetoothDevice();
	QString getDeviceFileName();

public slots:
	void startDiscovery();
	void stopDiscovery();
	void deviceFound(const QString& address, const QMap<QString,QVariant>& properties);

	void deviceSelected(QListWidgetItem *current, QListWidgetItem *previous);

private:
	Ui::bluetoothwidget *m_ui;

	QDBusConnection m_conn;
	QDBusInterface *m_manager;
	QDBusInterface *m_adapter;

	QString m_device_file_name;
	bool m_discovery_active;
};

#endif /* CBLUETOOTHDEVICE_H_ */
