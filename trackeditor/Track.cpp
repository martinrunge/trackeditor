/*
 * Track.cpp
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */

#include "Track.h"
#include <QDebug>

Track::Track() : m_pj(0){
	initMetaData();

	m_index_item = 0;
	m_start_time_item = 0;
	m_end_time_item = 0;
	m_name_item = 0;
	m_num_points_item = 0;

//	m_itemlist = new QList<QStandardItem*>;
}

Track::~Track() {
	for(int i = 0; i < m_itemlist.size(); i++) {
		delete m_itemlist.at(i);
	}
	//delete m_itemlist;
}

void Track::commit() {
	// iterate over QVector and find min and max lat and long
	m_min_lat = 360.0;
	m_max_lat = 0;
	m_min_lng = 360.0;
	m_max_lng = 0;

	m_min_x = 100000000.0;
	m_max_x = -100000000.0;
	m_min_y = 100000000.0;
	m_max_y = -100000000.0;

	if(size() == 0) return;

	m_min_time = at(0)->getTime();
	m_max_time = at(0)->getTime();
	int i;

	at(0)->setSpeed(0);
	at(0)->setDist(0);

	for(i = 0; i < size(); i++) {
		if(m_min_lat > at(i)->getLat() ) m_min_lat = at(i)->getLat();
		if(m_max_lat < at(i)->getLat() ) m_max_lat = at(i)->getLat();
		if(m_min_lng > at(i)->getLong() ) m_min_lng = at(i)->getLong();
		if(m_max_lng < at(i)->getLong() ) m_max_lng = at(i)->getLong();

		at(i)->setPJ(m_pj);

		if(m_min_x > at(i)->getX() ) m_min_x = at(i)->getX();
		if(m_max_x < at(i)->getX() ) m_max_x = at(i)->getX();
		if(m_min_y > at(i)->getY() ) m_min_y = at(i)->getY();
		if(m_max_y < at(i)->getY() ) m_max_y = at(i)->getY();

		if(m_min_time > at(i)->getTime()) m_min_time = at(i)->getTime();
		if(m_max_time < at(i)->getTime()) m_max_time = at(i)->getTime();

		if( i > 0) {
			double dist = distance(at(i-1), at(i));
			double spd = speed(at(i-1), at(i), dist );

			at(i)->setDist(dist + at(i-1)->getDist());
			at(i)->setSpeed(spd);
			// qDebug() << QString("dist: %1").arg(at(i)->getDist());
		}

	}

	QString tracknr;
	tracknr.setNum(m_track_index);
	m_index_item = new QStandardItem(tracknr);
	m_index_item->setEditable(false);
	m_itemlist.append(m_index_item);

	QString starttime = m_min_time.toString("yy-MM-dd  hh:mm:ss");
	m_start_time_item = new QStandardItem(starttime);
	m_start_time_item->setEditable(false);
	m_itemlist.append(m_start_time_item);

	QString endtime = m_max_time.toString("yy-MM-dd  hh:mm:ss");
	m_end_time_item = new QStandardItem(endtime);
	m_end_time_item->setEditable(false);
	m_itemlist.append(m_end_time_item);

	m_name_item = new QStandardItem(getName());
	m_itemlist.append(m_name_item);

	QString nrpoints;
	nrpoints.setNum(size());
	m_num_points_item = new QStandardItem(nrpoints);
	m_num_points_item->setEditable(false);
	m_itemlist.append(m_num_points_item);

}

void Track::dataChanged(int column) {
	if(column == 3) { // name changed
		setName(m_name_item->text());
	}
}


void Track::initMetaData() {
	m_min_lat = 0;
	m_max_lat = 0;
	m_min_lng = 0;
	m_max_lng = 0;

	m_min_x = 0;
	m_max_x = 0;
	m_min_y = 0;
	m_max_y = 0;

	m_track_index = 0;

}

double Track::getMinLat() {
	return m_min_lat;
}

double Track::getMaxLat() {
	return m_max_lat;
}

double Track::getMinLong() {
	return m_min_lng;
}

double Track::getMaxLong() {
	return m_max_lng;
}

double Track::getMinX() {
	return m_min_x;
}

double Track::getMaxX() {
	return m_max_x;
}

double Track::getMinY() {
	return m_min_y;
}

double Track::getMaxY() {
	return m_max_y;
}


QDateTime Track::getTrackBegin() {
	return m_min_time;
}

QDateTime Track::getTrackEnd() {
	return m_max_time;
}

void Track::setIndex(int index) {
	m_track_index = index;
}

int Track::getIndex(void) {
	return m_track_index;
}

bool Track::validIndex(void) {
	if(m_track_index >= 0) {
		return true;
	}
	else {
		return false;
	}
}

QList<QStandardItem*> Track::getItemList() {
	return m_itemlist;
}

double Track::distance(TrackPoint* tp1, TrackPoint* tp2) {
    double r = 6371000.8;
    double dlat = (tp1->getLat() - tp2->getLat()) * (r * 2 * M_PI / 360);
    double dlon = (tp1->getLong() - tp2->getLong())* (r *2 * M_PI / 360) * cos((tp1->getLat() - tp2->getLat()) / 2 * DEG_TO_RAD);
    double dist = sqrt(dlat * dlat +dlon *dlon);

    return dist;
}

double Track::speed(TrackPoint* tp1, TrackPoint* tp2) {
	double dist_in_m;
	dist_in_m = distance(tp1, tp2);

	double speed_in_m_per_s = speed(tp1, tp2, dist_in_m);
	return speed_in_m_per_s;
}

double Track::speed(TrackPoint* tp1, TrackPoint* tp2, double dist_in_m) {

	QDateTime dt1 = tp1->getTime();
	QDateTime dt2 = tp2->getTime();

	int diffdays = dt1.daysTo(dt2);
    int msecs = dt1.time().msecsTo(dt2.time());
    int ddays_in_ms = diffdays * 24 * 60 * 60 * 1000;

    double time_diff_in_s = ddays_in_ms + msecs / 1000;

	return dist_in_m / time_diff_in_s;
}
