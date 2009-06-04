/*
 * DeviceListWidgetItem.cpp
 *
 *  Created on: 02.06.2009
 *      Author: martin
 */

#include "DeviceListWidgetItem.h"

DeviceListWidgetItem::DeviceListWidgetItem(QListWidget * parent, int type)
	: QListWidgetItem(parent, type)
{

}

DeviceListWidgetItem::DeviceListWidgetItem( const QString & text, QListWidget * parent, int type)
	: QListWidgetItem(text, parent, type)
{

}

DeviceListWidgetItem::DeviceListWidgetItem( const QIcon & icon, const QString & text, QListWidget * parent, int type)
	: QListWidgetItem(icon, text, parent, type )
{

}

DeviceListWidgetItem::DeviceListWidgetItem( const QListWidgetItem & other )
	: QListWidgetItem(other)
{

}

DeviceListWidgetItem::~DeviceListWidgetItem()
{
	// TODO Auto-generated destructor stub
}

void DeviceListWidgetItem::setData ( int role, const QVariant & value )
{
	switch(role)
	{
	case Qt::UserRole:
		m_device_file_name = value.toString();
		break;
	case Qt::UserRole + 1:
		m_address = value.toString();
		break;
	default:
		QListWidgetItem::setData(role, value);
	}
}

QVariant DeviceListWidgetItem::data ( int role ) const
{
	switch(role)
	{
	case Qt::UserRole:
		return QVariant(m_device_file_name);
		break;
	case Qt::UserRole + 1:
		return QVariant(m_address);
		break;
	default:
		return QListWidgetItem::data(role);
	}

}

