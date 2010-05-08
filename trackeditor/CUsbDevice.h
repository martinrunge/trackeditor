/*
 * CUsbDevice.h
 *
 *  Created on: 23.05.2009
 *      Author: martin
 */

#ifndef CUSBDEVICE_H_
#define CUSBDEVICE_H_

#include <QtDBus/QtDBus>
#include <QString>
#include <QTabWidget>
#include "ui_usbwidget.h"

class QDBusPendingCallWatcher;

class CUsbDevice : public QTabWidget {
	Q_OBJECT;
public:
	CUsbDevice();
	virtual ~CUsbDevice();

	QString getDeviceFileName();
	bool isValid() { return m_valid; };


public slots:
	void deviceAdded(QString objpath);
	void deviceRemoved(QString objpath);

	void deviceListReceived(QDBusPendingCallWatcher* result);

	void currentItemChanged( QListWidgetItem * current, QListWidgetItem * previous );

signals:
	void setValid(bool);


private:
	void getDeviceList();

	Ui::usbwidget *m_ui;


	QDBusConnection m_conn;
	QDBusInterface *m_if;

	QString m_device_file_name;

	bool m_valid;

};

#endif /* CUSBDEVICE_H_ */
