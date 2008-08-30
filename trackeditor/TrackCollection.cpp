/*
 * TrackCollection.cpp
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */


#include <assert.h>

#include <QDebug>
#include "TrackCollection.h"

TrackCollection::TrackCollection() {
	m_waypoints = new Track();
	m_parentItem = invisibleRootItem();
	setHorizontalHeaderLabels(QStringList() << "Nr " << "Start Time" << "End Time" << "Name" << "Nr Points");
	initMetaData();
    connect(this, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
    		this, SLOT(editFinished(const QModelIndex&, const QModelIndex&)));


}

TrackCollection::~TrackCollection() {
	delete m_waypoints;
}


void TrackCollection::editFinished(const QModelIndex & topLeft, const QModelIndex & bottomRight) {
	qDebug() << QString("editFinished: (%1,%2) - (%3,%4)").arg(topLeft.column()).arg(topLeft.row()).arg(bottomRight.column()).arg(bottomRight.row());
	assert(topLeft == bottomRight);

	at(topLeft.row())->dataChanged(topLeft.column());
}


int TrackCollection::getNumWaypoints() {
	return m_waypoints->size();
}

Track* TrackCollection::getWaypoints() {
	return m_waypoints;
}

QRectF TrackCollection::getCompleteDimension() {
	// iterate over QList and find min and max lat and long
	double min_lat = 360;
	double max_lat = 0;
	double min_lng = 360;
	double max_lng = 0;

	for(int i = 0; i < size(); i++) {
		if(min_lat > at(i)->getMinLat() ) min_lat = at(i)->getMinLat();
		if(max_lat < at(i)->getMaxLat() ) max_lat = at(i)->getMaxLat();
		if(min_lng > at(i)->getMinLong()) min_lng = at(i)->getMinLong();
		if(max_lng < at(i)->getMaxLong()) max_lng = at(i)->getMaxLong();
	}

	return QRectF(QPointF(min_lng, max_lat), QPointF(max_lng, min_lat));
}

QRectF TrackCollection::getDimension() {
	return getDimension(m_model_index_list);
}

QRectF TrackCollection::getDimension(QModelIndexList indices) {
	// iterate over QVector and find min and max lat and long
	double min_lat = 360;
	double max_lat = 0;
	double min_lng = 360;
	double max_lng = 0;

	for(int i = 0; i < indices.size(); i++) {
		int tmp_i = indices.at(i).row();
		if(min_lat > at(tmp_i)->getMinLat() ) min_lat = at(tmp_i)->getMinLat();
		if(max_lat < at(tmp_i)->getMaxLat() ) max_lat = at(tmp_i)->getMaxLat();
		if(min_lng > at(tmp_i)->getMinLong()) min_lng = at(tmp_i)->getMinLong();
		if(max_lng < at(tmp_i)->getMaxLong()) max_lng = at(tmp_i)->getMaxLong();
	}

	return QRectF(QPointF(min_lng, max_lat), QPointF(max_lng, min_lat));

}

bool TrackCollection::validBounds() {
	return true;
}


void TrackCollection::setModelIndexList(QModelIndexList index_list) {
	m_model_index_list = index_list;
}

QModelIndexList TrackCollection::getModelIndexList(void) {
	return m_model_index_list;
}

// void TrackCollection::setIndexList(QModelIndexList index_list) {
//	m_index_list = index_list;
// }

std::vector<int> TrackCollection::getIndexList(void) {
	m_index_list.clear();

    for(int mi_idx = 0; mi_idx < m_model_index_list.size(); mi_idx++ ) {
    	int tr_idx = m_model_index_list.at(mi_idx).row();
    	std::vector<int>::iterator it;
    	for(it = m_index_list.begin() ; it != m_index_list.end(); it++ ) {
    	   	if(*it == tr_idx) {
    	   		break;
    	   	}
    	}
    	if(it == m_index_list.end()) {
    		m_index_list.push_back(tr_idx);
    	}
    }
	return m_index_list;
}


void TrackCollection::commit() {
	for (int i = 0; i < size(); i++) {
		QList<QStandardItem*> itemlist = at(i)->getItemList();
		appendRow(itemlist);
	}
}

void TrackCollection::clear() {
	// remove all logpoints
	for(int i= 0; i < getNumWaypoints(); i++) {
		delete m_waypoints->at(i);
	}
	m_waypoints->clear();
	m_waypoints->commit();

	for(int i= 0; i < size(); i++) {
		takeRow(0);
		delete at(i);
	}
	QList<Track*>::clear();
	initMetaData();
	commit();

}

void TrackCollection::initMetaData() {
	m_creator_description = "TrackEditor http://some.future.URL";

	// <author> personType </author> [0..1] ?
	m_author_name.clear();
	m_author_email.clear();

	m_author_link_url.clear();
	m_author_link_mimetype.clear();
	m_author_link_text.clear();

	// <copyright> copyrightType </copyright> [0..1] ?
	m_copyright_year = 0;
	m_copyright_license_url.clear();

	// <time> xsd:dateTime </time> [0..1] ?
	m_date_time = QDateTime();

	// <keywords> xsd:string </keywords> [0..1] ?
	m_keywords.clear();

	CommonAttributes::initMetaData();
}

QString TrackCollection::getCreator() {
	return m_creator_description;
}


void TrackCollection::setAuthorName(QString author) {
	m_author_name = author;
}

QString TrackCollection::getAuthorName() {
	return m_author_name;
}

bool TrackCollection::validAuthorName() {
	return !(m_author_name.isEmpty());
}

bool TrackCollection::validAuthor() {
	return validAuthorName() || validAuthorEmail() || validAuthorLinkUrl();
}


void TrackCollection::setAuthorEMail(QString email) {
	m_author_email = email;
}

QString TrackCollection::getAuthorEMail() {
	return m_author_email;
}

bool TrackCollection::validAuthorEmail() {
	return !(m_author_email.isEmpty());
}

void TrackCollection::setAuthorLinkUrl(QString url) {
	m_author_link_url = url;
}

QString TrackCollection::getAuthorLinkUrl() {
	return m_author_link_url;
}

bool TrackCollection::validAuthorLinkUrl() {
	return !(m_author_link_url.isEmpty());
}

void TrackCollection::setAuthorLinkMimeType(QString mime_type) {
	m_author_link_mimetype = mime_type;
}

QString TrackCollection::getAuthorLinkMimeType() {
	return m_author_link_mimetype;
}


void TrackCollection::setAuthorLinkText(QString text) {
	m_author_link_text = text;
}

QString TrackCollection::getAuthorLinkText() {
	return m_author_link_text;
}

void TrackCollection::setCopyrightAuthor(QString author) {
	m_copyright_author = author;
}

QString TrackCollection::getCopyrightAuthor() {
	return m_copyright_author;
}

bool TrackCollection::validCopyrightAuthor() {
	return !(m_copyright_author.isEmpty());
}

void TrackCollection::setCopyrightYear(unsigned year) {
	m_copyright_year = year;
}

unsigned TrackCollection::getCopyrightYear() {
	return m_copyright_year;
}

bool TrackCollection::validCopyrightYear() {
	if(m_copyright_year != 0) {
		return true;
	}
	else {
		return false;
	}
}


void TrackCollection::setCopyrightLicenseUrl(QString license_url) {
	m_copyright_license_url = license_url;
}

QString TrackCollection::getCopyrightLicenseUrl() {
	return m_copyright_license_url;
}

bool TrackCollection::validCopyrightLicenseUrl() {
	return !(m_copyright_license_url.isEmpty());
}


void TrackCollection::setDateTime(QDateTime date_time) {
	m_date_time = date_time;
}

QDateTime TrackCollection::getDateTime() {
	return m_date_time;
}

bool TrackCollection::validDateTime() {
	return m_date_time.isValid();
}


void TrackCollection::setKeywords(QString keywords) {
	m_keywords = keywords;
}

QString TrackCollection::getKeywords() {
	return m_keywords;
}

bool TrackCollection::validKeywords() {
	return !(m_keywords.isEmpty());
}

