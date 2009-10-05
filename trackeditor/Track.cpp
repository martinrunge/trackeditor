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
			double td = timeDiff(at(i-1), at(i));


			at(i)->setDist(dist + at(i-1)->getDist());
			at(i)->setSpeed(spd);
			at(i)->setTimeDiff(td + at(i-1)->getTimeDiff());
			// qDebug() << QString("dist: %1").arg(at(i)->getDist());
		}

	}

	m_itemlist.clear();

	m_index_item = new QStandardItem();
	m_index_item->setEditable(false);
	//m_itemlist.append(m_index_item);

	m_color_item = new QStandardItem();
	m_color_item->setEditable(false);
	//m_itemlist.append(m_color_item);

	m_start_time_item = new QStandardItem();
	m_start_time_item->setEditable(false);
	//m_itemlist.append(m_start_time_item);

	m_end_time_item = new QStandardItem();
	m_end_time_item->setEditable(false);
	//m_itemlist.append(m_end_time_item);

	m_name_item = new QStandardItem();
	//m_itemlist.append(m_name_item);

	m_length_item = new QStandardItem();
	m_length_item->setEditable(false);
	//m_itemlist.append(m_length_item);

	m_num_points_item = new QStandardItem();
	m_num_points_item->setEditable(false);
	//m_itemlist.append(m_num_points_item);


	QString tracknr;
	tracknr.setNum(m_track_index);
	//m_itemlist.at(0)->setText(tracknr);
	m_index_item->setText(tracknr);

	setColor(m_color);

	QString starttime = m_min_time.toString("yy-MM-dd  hh:mm:ss");
	m_start_time_item->setText(starttime);

	QString endtime = m_max_time.toString("yy-MM-dd  hh:mm:ss");
	m_end_time_item->setText(endtime);

	m_name_item->setText(getName());

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
	m_length_item->setText(length);

	QString nrpoints;
	nrpoints.setNum(size());
	m_num_points_item->setText(nrpoints);

	m_itemlist.append(m_index_item);
	m_itemlist.append(m_color_item);
	m_itemlist.append(m_start_time_item);
	m_itemlist.append(m_end_time_item);
	m_itemlist.append(m_name_item);
	m_itemlist.append(m_length_item);
	m_itemlist.append(m_num_points_item);

}

void Track::dataChanged(int column) {
	if(column == 3) { // name changed
		setName(m_name_item->text());
	}
}

void Track::setColor(QColor col) {
	m_color = col;

	if(m_color_item)
	{
		QBrush bg = m_color_item->background();
		bg.setColor(m_color);
		bg.setStyle(Qt::SolidPattern);
		m_color_item->setBackground(bg);
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


int Track::getIndexFromTime(double time)
{
	return getIndexFromXVal(time, TYPE_X_TIME);
}

int Track::getIndexFromDist(double dist)
{
	return getIndexFromXVal(dist, TYPE_X_DIST);
}

int Track::getIndexFromTrackPoint(int tp)
{
	return getIndexFromXVal(tp, TYPE_X_POINTS);

}

int Track::getIndexFromXVal(double val, enum plotTypeX x_type)
{
	int retval;
	QList<enum plotTypeY> keys;

	switch(x_type)
	{
		case TYPE_X_TIME:
			keys = m_time_data.keys();

			if(keys.isEmpty())
			{
				retval = -1;
			}
			else
			{
				retval = m_time_data[keys.at(0)]->findIndex(val);
			}
			break;

		case TYPE_X_DIST:
			keys = m_dist_data.keys();

			if(keys.isEmpty())
			{
				retval = -1;
			}
			else
			{
				retval = m_dist_data[keys.at(0)]->findIndex(val);
			}
			break;

		case TYPE_X_POINTS:
			retval = val;
			break;

		default:
			retval = -1;
	}
	return retval;

}

int Track::getIndexFromXVal(int val, enum plotTypeX x_type)
{
	int retval;

	if( x_type == TYPE_X_POINTS)
	{
		retval = val;
	}
	else
	{
		retval = getIndexFromXVal(double(val), x_type);
	}
	return retval;
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

double Track::timeDiff(TrackPoint* tp1, TrackPoint* tp2) {
	QDate d1 = tp1->getTime().date();
	QDate d2 = tp2->getTime().date();

	int diffdays = d1.daysTo(d2);

	QTime t1 = tp1->getTime().time();
	QTime t2 = tp2->getTime().time();

	int m_time_diff_in_ms = t1.msecsTo(t2);

	double secs = diffdays * 60 * 60 * 24;
	secs += 0.001 * m_time_diff_in_ms;

	return secs;

}


void Track::dumpDistData()
{
	int size = m_dist_data.size();
	QList<enum plotTypeY> keys = m_dist_data.keys();

	qDebug() << QString("Track::dumpDistData this=") << this << QString(" size: %1").arg(size);

	for(int i = 0; i < keys.size(); i++) {
		qDebug() << QString("Track::dumpDistData[%1]=(%2, ").arg(i).arg(keys[i]) << m_dist_data[keys[i]] << QString(" )");
	}

}

void Track::dumpTimeData()
{
	int size = m_time_data.size();
	QList<enum plotTypeY> keys = m_time_data.keys();

	qDebug() << QString("Track::dumpTimeData this=") << this << QString(" size: %1").arg(size);

	for(int i = 0; i < keys.size(); i++) {
		qDebug() << QString("Track::dumpTimeData[%1]=(%2, ").arg(i).arg(keys[i]) << m_time_data[keys[i]] << QString(") )");
	}

}

void Track::dumpTrackPointData()
{
	int size = m_trackpoints_data.size();
	QList<enum plotTypeY> keys = m_trackpoints_data.keys();

	qDebug() << QString("Track::dumpTrackPointsData this=") << this << QString(" size: %1").arg(size);

	for(int i = 0; i < keys.size(); i++) {
		qDebug() << QString("Track::dumpTrackPointsData[%1]=(%2,").arg(i).arg(keys[i])  << m_trackpoints_data[keys[i]] << QString(")");
	}

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
		if(!found) {
			PlotData* pd = m_dist_data.take(keys[i]);
			delete pd;
		}
	}

	// now add additional values from distVals
	keys = m_dist_data.keys();

	for(int j=0; j < distVals.size(); j++) {
		bool found = false;
		for(int i = 0; i < keys.size(); i++) {
			if(keys[i] == distVals[j] ) {
				found = true;
				break;
			}
		}
		if(!found) {
			PlotData* pd = new PlotData(this, TYPE_X_DIST, distVals[j], 1000);
			m_dist_data.insert(distVals[j], pd);
		}
	}

	// same for m_time_data
	keys = m_time_data.keys();

	for(int i = 0; i < keys.size(); i++) {
		bool found = false;
		for(int j=0; j < timeVals.size(); j++) {
			if(keys[i] == timeVals[j] ) {
				found = true;
				break;
			}
		}
		if(!found) {
			PlotData* pd = m_time_data.take(keys[i]);
			delete pd;
		}
	}

	// now add additional values from distVals
	keys = m_time_data.keys();

	for(int j=0; j < timeVals.size(); j++) {
		bool found = false;
		for(int i = 0; i < keys.size(); i++) {
			if(keys[i] == timeVals[j] ) {
				found = true;
				break;
			}
		}
		if(!found) {
			PlotData* pd = new PlotData(this, TYPE_X_TIME, timeVals[j], 1000);
			m_time_data.insert(timeVals[j], pd);
		}
	}

	keys = m_trackpoints_data.keys();

	for(int i = 0; i < keys.size(); i++) {
		bool found = false;
		for(int j=0; j < trackPointVals.size(); j++) {
			if(keys[i] == trackPointVals[j] ) {
				found = true;
				break;
			}
		}
		if(!found) {
			PlotData* pd = m_trackpoints_data.take(keys[i]);
			delete pd;
		}
	}

	// now add additional values from distVals
	keys = m_trackpoints_data.keys();

	for(int j=0; j < trackPointVals.size(); j++) {
		bool found = false;
		for(int i = 0; i < keys.size(); i++) {
			if(keys[i] == timeVals[j] ) {
				found = true;
				break;
			}
		}
		if(!found) {
			PlotData* pd = new PlotData(this, TYPE_X_POINTS, trackPointVals[j], 1000);
			m_trackpoints_data.insert(trackPointVals[j], pd);
		}
	}

	dumpDistData();
	dumpTimeData();
	dumpTrackPointData();

}

double Track::duration()
{
	double duration = at(size() - 1 )->getTimeDiff();
	return duration;

}
