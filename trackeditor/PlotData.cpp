/*
 * PlotData.cpp
 *
 *  Created on: 17.11.2008
 *      Author: martin
 */

#include "PlotData.h"
#include <QDebug>
#include <QString>

#include "Track.h"


QMap<enum plotTypeX, QString> PlotData::XTypeName;
QMap<enum plotTypeY, QString> PlotData::YTypeName;
QMap<QString, enum plotTypeY> PlotData::YTypeNamesForSettings;

void PlotData::initializeMaps() {

	PlotData::XTypeName[ TYPE_X_DIST ] = QString(QObject::tr("Distance"));
	PlotData::XTypeName[ TYPE_X_TIME ] = QString(QObject::tr("Time"));
	PlotData::XTypeName[ TYPE_X_POINTS ] = QString(QObject::tr("Trackpoints"));

	PlotData::YTypeName[ TYPE_Y_ALT ] = QString(QObject::tr("Elevation"));
	PlotData::YTypeName[ TYPE_Y_SPEED ] = QString(QObject::tr("Speed"));
	PlotData::YTypeName[ TYPE_Y_DGPS_DIFF ] = QString(QObject::tr("DGPS diff"));
	PlotData::YTypeName[ TYPE_Y_HDOP ] = QString(QObject::tr("HDOP"));
	PlotData::YTypeName[ TYPE_Y_VDOP ] = QString(QObject::tr("VDOP"));
	PlotData::YTypeName[ TYPE_Y_PDOP ] = QString(QObject::tr("PDOP"));

	PlotData::YTypeNamesForSettings["elevation"] = TYPE_Y_ALT;
	PlotData::YTypeNamesForSettings["speed"] = TYPE_Y_SPEED;
	PlotData::YTypeNamesForSettings["dgps_diff"] = TYPE_Y_DGPS_DIFF;
	PlotData::YTypeNamesForSettings["hdop"] = TYPE_Y_HDOP;
	PlotData::YTypeNamesForSettings["vdop"] = TYPE_Y_VDOP;
	PlotData::YTypeNamesForSettings["pdop"] = TYPE_Y_PDOP;


}

PlotData::PlotData(Track* track, enum plotTypeX xtype, enum plotTypeY ytype, int numPoints) : QwtData(),
                                                                                              m_plot_type_x(xtype),
                                                                                              m_plot_type_y(ytype),
                                                                                              m_copied(false)
{
	m_num_points = numPoints;
	if( numPoints > 0 ) {
		m_size = numPoints;
	}
	else {
		m_size = m_track->size();
	}

	m_x_values = new double[ m_size ];
	m_y_values = new double[ m_size ];
	unsigned arrayindex = 0;

	Track::iterator it;

	// as TrackPoint->getDist() returns the accumulated distance of the track,
	// length of complete Track is stored in last TrackPoint.
	it = track->end();
	--it;
	//double total_dist = (*it)->getDist();
	double total_dist = getXVal(*it);
	double distraster = total_dist / m_size;

	it = track->begin();

	// double lastalt = (*it)->getAlt();
	double lastalt = getYVal(*it);
	//double interpol_x = (*it)->getDist();  // should be 0 for begin of track
	double interpol_x = getXVal(*it);        // should be 0 for begin of track
	double interpol_y = lastalt;
	double ddist;
	double part = 0;

	//qDebug() << QString("distraster: %1 total_dist %2 ").arg(distraster).arg(total_dist);
	//qDebug() << QString("interpol_x %1").arg(interpol_x);
	// it++;
	for(double d = distraster; d < total_dist && arrayindex < m_size; d += distraster) {
		// (tmp_x, tmp_y) : linear interpolation between last TP left of range
		// [d .. (d + ddist)] next TP at position x == d.
		part = 0;

		//qDebug() << QString("in for loop: d: %1, dist: %2 interpol_x: %3 part %4").arg(d).arg((*it)->getDist()).arg(interpol_x).arg(part);
		//while( (*it)->getDist() < d) {
		while( getXVal(*it) < d) {
			//ddist = (*it)->getDist() - interpol_x;
			ddist = getXVal(*it) - interpol_x;
			//part += (((*it)->getAlt() + interpol_y) / 2) * ( ddist /  distraster);
			part += ((getYVal(*it) + interpol_y) / 2) * ( ddist /  distraster);

			// qDebug() << QString("in while loop: dist: %1, interpol_x: %2 ddist: %3 part %4").arg((*it)->getDist()).arg(interpol_x).arg(ddist).arg(part);


			//interpol_x = (*it)->getDist();
			interpol_x = getXVal(*it);
			//lastalt = (*it)->getAlt();
			lastalt = getYVal(*it);
			interpol_y = lastalt;
			it++;
			m_tp_index++;
		}
		// (*it) is right of d + ddist -> interpolate linearly between last TP and (*it) at pos d
		// interpol_x = d;
		//interpol_y = lastalt + ((*it)->getAlt() - lastalt) * (d - interpol_x) / ((*it)->getDist() - interpol_x);
		interpol_y = lastalt + (getYVal(*it) - lastalt) * (d - interpol_x) / (getXVal(*it) - interpol_x);
		part += ((lastalt + interpol_y) / 2 ) * ((d - interpol_x) / distraster);
		interpol_x = d;

		// part now contains the arithmethic average of the alt values in the range [ d .. (d + ddist) ]
		// qDebug() << QString("*** part %1  (interpol_y %2    lastdist: %3)").arg(part).arg(interpol_y).arg(interpol_x);

		//lastdist = interpol_x;

		m_x_values[arrayindex] = d + 0.5 * distraster;
		m_y_values[arrayindex] = part;
		arrayindex++;


	}

	// qDebug() << QString("size: %1 arrayindex %2").arg(m_size).arg(arrayindex);
	while (arrayindex - 1 < m_size ) {
		m_x_values[arrayindex -1 ] = m_x_values[arrayindex - 2];
		m_y_values[arrayindex -1 ] = m_y_values[arrayindex - 2];
		arrayindex++;
	}

}

PlotData::PlotData(double *x_vals, double *y_vals, int size): m_tp_index(0), m_copied(true) {
	m_x_values = x_vals;
	m_y_values = y_vals;

	m_size = size;
}


PlotData::~PlotData() {
	if(!m_copied) {
		delete [] m_x_values;
		delete [] m_y_values;
	}
}

double PlotData::getXVal(TrackPoint* tp) {
	double val;
	switch(m_plot_type_x) {
	case TYPE_X_DIST:
		val = tp->getDist();
		break;

	case TYPE_X_TIME:
	{
//		QDateTime dt = tp->getTime();
//		int diffdays = m_start_time.daysTo(dt);
//	    int msecs = m_start_time.time().msecsTo(dt.time());
//	    int ddays_in_ms = diffdays * 24 * 60 * 60 * 1000;
//
//	    val = ddays_in_ms + msecs / 1000;
	    val = tp->getTimeDiff();
		break;
	}
	case TYPE_X_POINTS:
		val = m_tp_index;
		break;

	case TYPE_X_NONE:
	default:
		val = 0.0;
		break;
	}

	return val;
}

double PlotData::getYVal(TrackPoint* tp) {
	double val;
	switch(m_plot_type_y) {
	case TYPE_Y_ALT:
		val = tp->getAlt();
		break;

	case TYPE_Y_SPEED:
		val = tp->getSpeed();
		break;

	case TYPE_Y_HDOP:
		val = tp->getHdop();
		break;

	case TYPE_Y_VDOP:
		val = tp->getVdop();
		break;

	case TYPE_Y_PDOP:
		val = tp->getPdop();
		break;

	case TYPE_Y_DGPS_DIFF:
		val = 0.0;
		break;
	case TYPE_Y_NONE:
	default:
		val = 0.0;
		break;
	}

	return val;

}


QwtData *PlotData::copy() const
{
    // return new PlotData( m_track, m_plot_type , m_num_points);
    return new PlotData( m_x_values, m_y_values , m_size);
}

size_t PlotData::size() const
{
    return m_size;
}

double PlotData::x(size_t i) const
{
    return m_x_values[i];
}

double PlotData::y(size_t i) const
{
    return m_y_values[i];
}

