/*
 * TrackPoint.cpp
 *
 *  Created on: 31.07.2008
 *      Author: martin
 */

#include "TrackPoint.h"

#include <QDebug>
#include <arpa/inet.h>

const int TrackPoint::m_size = 16;

TrackPoint::TrackPoint(QByteArray data) {
	m_data = data;
	uint32_t* tmp;
	uint16_t *stmp;

	stmp = reinterpret_cast<uint16_t*>(m_data.mid(0, 2).data());
    m_is_begin_of_track = *stmp & 0x01;
	m_is_log_point = *stmp & 0x02;
    m_is_over_speed = *stmp & 0x04;

    tmp = reinterpret_cast<uint32_t*>(m_data.mid(2, 4).data());

    int sec    = ((*tmp >>  0) & 0x3F);
    int min    = ((*tmp >>  6) & 0x3F);
    int hour   = ((*tmp >> 12) & 0x1F);
    int mday   = ((*tmp >> 17) & 0x1F);
    int mon    = ((*tmp >> 22) & 0x0F);
    int year   = ((*tmp >> 26) & 0x3F);

    m_time.setDate(QDate(year+2000, mon, mday));
    m_time.setTime(QTime(hour, min, sec));
    m_time.setTimeSpec(Qt::UTC);

    tmp = reinterpret_cast<uint32_t*>(m_data.mid(6, 4).data());
    m_lat = (double) (*tmp) / 10000000;
    tmp = reinterpret_cast<uint32_t*>(m_data.mid(10, 4).data());
    m_lng = (double) (*tmp) / 10000000;
    stmp = reinterpret_cast<uint16_t*>(m_data.mid(14, 2).data());
    m_alt = (double) (*stmp);

    initMetaData();
    // qDebug() << QString("Waypoint: %1: long:%2 lat:%3 alt:%4").arg(m_time.toString()).arg(m_lng,8, 'f', 8).arg(m_lat,8, 'f', 8).arg(m_alt);
}

TrackPoint::TrackPoint() {
    initMetaData();
}

TrackPoint::~TrackPoint() {
	// TODO Auto-generated destructor stub
}

const int TrackPoint::size() {
	return m_size;
}

bool TrackPoint::isBeginOfTrack() {
	return m_is_begin_of_track;
}

void TrackPoint::isBeginOfTrack(bool begin) {
	m_is_begin_of_track = begin;
}

bool TrackPoint::isLogPoint() {
	return m_is_log_point;
}

void TrackPoint::isLogPoint(bool logpoint) {
	m_is_log_point = logpoint;
}

bool TrackPoint::isOverSpeed() {
	return m_is_over_speed;
}

void TrackPoint::isOverSpeed(bool overspeed) {
	m_is_over_speed = overspeed;
}

void TrackPoint::initMetaData() {
	//    <magvar> degreesType </magvar> [0..1]
    m_magmetic_variation = 1111.1;

    //    <geoidheight> xsd:decimal </geoidheight> [0..1]
    //    INT_MIN == not set
	m_geoid_height = INT_MIN;

    //    <name> xsd:string </name> [0..1]
//	m_name.clear();

	//    <cmt> xsd:string </cmt> [0..1]
//	m_comment.clear();

	//    <desc> xsd:string </desc> [0..1]
//	m_description.clear();

	//    <src> xsd:string </src> [0..1]
//	m_data_source.clear();

	//    <link> linkType </link> [0..*]
//	m_link_url.clear();
//	m_link_mime_type.clear();
//	m_link_text.clear();

	//    <sym> xsd:string </sym> [0..1]
	m_symbol.clear();

	//    <type> xsd:string </type> [0..1]
//	m_type.clear();

	//    <fix> fixType </fix> [0..1]
	// {none|2d|3d|dgps|pps}
	m_fix_type.clear();

	//    <sat> xsd:nonNegativeInteger </sat> [0..1]
	//   -1 == not set
	m_num_sats = -1;

	//    <hdop> xsd:decimal </hdop> [0..1]
	//   -1 == not set
	m_hdop = -1;

	//    <vdop> xsd:decimal </vdop> [0..1]
	//   -1 == not set
	m_vdop = -1;

	//    <pdop> xsd:decimal </pdop> [0..1]
	//   -1 == not set
	m_pdop = -1;

	//    <ageofdgpsdata> xsd:decimal </ageofdgpsdata> [0..1]
	//    in seconds; -1 == not set
	m_age_of_dgps_data = -1;

	//    <dgpsid> dgpsStationType </dgpsid> [0..1]
	//    0 <= value <= 1023   -1 == not set;
	m_dgps_station_id = -1;

}


double TrackPoint::getLat() {
	return m_lat;
}

void TrackPoint::setLat(double lat) {
	m_lat = lat;
}

double TrackPoint::getLong() {
	return m_lng;
}

void TrackPoint::setLong(double lng) {
	m_lng = lng;
}

double TrackPoint::getAlt() {
	return m_alt;
}

void TrackPoint::setAlt(double alt) {
	m_alt = alt;
}

bool TrackPoint::validAlt() {
	if( m_alt > -1000000) {
		return true;;
	}
	else {
		return false;
	}
}


QDateTime TrackPoint::getTime() {
	return m_time;
}

void TrackPoint::setTime(QDateTime dt) {
	m_time = dt;
}

bool TrackPoint::validTime() {
	return m_time.isValid();
}


//void TrackPoint::setName(QString name) {
//	m_name = name;
//}
//
//QString TrackPoint::getName() {
//	return m_name;
//}


void TrackPoint::setMagneticVariation(double degrees) {
	m_magmetic_variation = degrees;
}

double TrackPoint::getMagneticVariation() {
	return m_magmetic_variation;
}

bool TrackPoint::validMagneticVariation() {
	if( m_magmetic_variation > 1000.0) {
		return false;
	}
	else {
		return true;
	}
}

void TrackPoint::setGeoidHeight(int meters) {
	// INT_MIN == not set
	m_geoid_height = meters;
}

int TrackPoint::getGeoidHeight() {
	return m_geoid_height;
}

bool TrackPoint::validGeoidHeight() {
	if(m_geoid_height == INT_MIN) {
		return false;
	}
	else {
		return true;;
	}
}


//void TrackPoint::setComment(QString comment) {
//	m_comment = comment;
//}
//
//QString TrackPoint::getComment() {
//	return m_comment;
//}
//
//
//void TrackPoint::setDescription(QString desc) {
//	m_description = desc;
//}
//
//QString TrackPoint::getDescription() {
//	return m_description;
//}
//
//
//void TrackPoint::setDataSource(QString src) {
//	m_data_source = src;
//}
//
//QString TrackPoint::getDataSource() {
//	return m_data_source;
//}
//
//
//void TrackPoint::setLinkUrl(QString url) {
//	m_link_url = url;
//}
//
//QString TrackPoint::getLinkUrl() {
//	return m_link_url;
//}
//
//void TrackPoint::setLinkMimeType(QString mime_type) {
//	m_link_mime_type = mime_type;
//}
//
//QString TrackPoint::getLinkMimeType() {
//	return m_link_mime_type;
//}
//
//void TrackPoint::setLinkText(QString text) {
//	m_link_text = text;
//}
//
//QString TrackPoint::getLinkText() {
//	return m_link_text;
//}


void TrackPoint::setSymbol(QString sym) {
	m_symbol = sym;
}

QString TrackPoint::getSymbol() {
	return m_symbol;
}

bool TrackPoint::validSymbol() {
	return !(m_symbol.isEmpty());
}

//
//void TrackPoint::setType(QString type) {
//	m_type = type;
//}
//
//QString TrackPoint::getType() {
//	return m_type;
//}


void TrackPoint::setFixType(QString type) {
	m_fix_type = type;
}

QString TrackPoint::getFixType() {
	return m_fix_type;
}

bool TrackPoint::validFixType() {
	return !(m_fix_type.isEmpty());
}



void TrackPoint::setNumSats(int num_sats) {
	m_num_sats = num_sats;
}

int TrackPoint::getNumSats() {
	return m_num_sats;
}

bool TrackPoint::validNumSats() {
	if(m_num_sats < 0) {
		return false;
	}
	else {
		return true;
	}
}

void TrackPoint::setHdop(int hdop) {
	m_hdop = hdop;
}

int TrackPoint::getHdop() {
	return m_hdop;
}

bool TrackPoint::validHdop() {
	if(m_hdop < 0) {
		return false;
	}
	else {
		return true;
	}
}


void TrackPoint::setVdop(int vdop) {
	m_vdop = vdop;
}

int TrackPoint::getVdop() {
	return m_vdop;
}

bool TrackPoint::validVdop() {
	if(m_vdop < 0) {
		return false;
	}
	else {
		return true;
	}
}

void TrackPoint::setPdop(int pdop) {
	m_pdop = pdop;
}

int TrackPoint::getPdop() {
	return m_pdop;
}

bool TrackPoint::validPdop() {
	if(m_pdop < 0) {
		return false;
	}
	else {
		return true;
	}
}


void TrackPoint::setDgpsAge(int dgps_age_in_s) {
	m_age_of_dgps_data = dgps_age_in_s;
}

int TrackPoint::getDgpsAge() {
	return m_age_of_dgps_data;
}

bool TrackPoint::validDgpsAge() {
	if(m_age_of_dgps_data < 0) {
		return false;
	}
	else {
		return true;
	}
}



void TrackPoint::setDgpsStationId(int station_id) {
	m_dgps_station_id = station_id;
}

int TrackPoint::getDgpsStationId() {
	return m_dgps_station_id;
}

bool TrackPoint::validDgpsStationId() {
	if(m_dgps_station_id < 0) {
		return false;
	}
	else {
		return true;
	}
}






























