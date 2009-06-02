/*
 * DeviceListWidgetItem.h
 *
 *  Created on: 02.06.2009
 *      Author: martin
 */

#ifndef DEVICELISTWIDGETITEM_H_
#define DEVICELISTWIDGETITEM_H_

#include <QListWidgetItem>

class DeviceListWidgetItem : public QListWidgetItem {
public:
	DeviceListWidgetItem ( QListWidget * parent = 0, int type = Type );
	DeviceListWidgetItem ( const QString & text, QListWidget * parent = 0, int type = Type );
	DeviceListWidgetItem ( const QIcon & icon, const QString & text, QListWidget * parent = 0, int type = Type );
	DeviceListWidgetItem ( const QListWidgetItem & other );

	virtual ~DeviceListWidgetItem();

	void setData ( int role, const QVariant & value );
	QVariant data ( int role ) const;

private:
	QString m_device_file_name;
};

#endif /* DEVICELISTWIDGETITEM_H_ */
