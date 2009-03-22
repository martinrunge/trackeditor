/*
 * Track.cpp
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */

#include "Track.h"
#include <QDebug>

Track::Track() : m_pj(0), m_color(Qt::black){
	initMetaData();

	m_index_item = 0;
	m_start_time_item = 0;
	m_end_time_item = 0;
	m_name_item = 0;
	m_num_points_item = 0;

	m_color_item = new QStandardItem();
	// new QPushButton("change");

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

	m_color_item->setEditable(false);
	setColor(m_color);
	m_itemlist.append(m_color_item);

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

	QString length;
	if(!isEmpty()) {
		double dist = last()->getDist();
		if(dist < 10000) {
			length = QString("%1 m").arg(dist);
		}
		else {
			length = QString("%1 km").arg(dist / 1000);
		}
	}
	m_length_item = new QStandardItem(length);
	m_length_item->setEditable(false);
	m_itemlist.append(m_length_item);

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

void Track::setColor(QColor col) {
	m_color = col;

	QBrush bg = m_color_item->background();
	bg.setColor(m_color);
	bg.setStyle(Qt::SolidPattern);
	m_color_item->setBackground(bg);
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
    double dlat = (tp1->getLat() - tp2->getLat()) * DEG_TO_RAD * r;
    double dlon = (tp1->getLong() - tp2->getLong()) * DEG_TO_RAD * r * cos((tp1->getLat() + tp2->getLat()) / 2.0 * DEG_TO_RAD);
    double dist = sqrt(dlat * dlat + dlon * dlon);

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

PlotData* Track::getDistData(enum plotTypeY key) {
	if(m_dist_data.contains(key)) {
		return m_dist_data.value(key);
	}
	else
	{
		return 0;
	}
}

PlotData* Track::getTimeData(enum plotTypeY key) {
	if(m_time_data.contains(key)) {
		return m_time_data.value(key);
	}
	else
	{
		return 0;
	}
}

PlotData* Track::getTrackpointsData(enum plotTypeY key) {
	if(m_trackpoints_data.contains(key)) {
		return m_trackpoints_data.value(key);
	}
	else
	{
		return 0;
	}
}

void Track::setDiagramQuantities(QList<enum plotTypeY> distVals, QList<enum plotTypeY> timeVals, QList<enum plotTypeY> trackPointVals) {

	//  first remove all values from m_dist_data that are not in distVals
	QList<enum plotTypeY> keys = m_dist_data.keys();

	for(int i = 0; i < keys.size(); i++) {
		bool found = false;
		for(int j=0; j < distVals.size(); j++) {
			if(keys[i] == distVals[j] ) {
				found = true;
				break;
			}
		}
		PlotData* pd = m_dist_data.take(keys[i]);
		delete pd;
	}

	// now add additional values from distVals
	keys = m_dist_data.keys();

	for(int j=0; j < distVals.size(); j++) {
		for(int i = 0; i < keys.size(); i++) {
			if(keys[i] != distVals[j] ) {
				PlotData* pd = new PlotData(this, TYPE_X_DIST, distVals[j], 1000);
				m_dist_data.insert(distVals[j], pd);
				break;
			}
		}
	}

	// noch die anderen

}
