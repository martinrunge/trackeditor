/*
 * TrackPoint.h
 *
 *  Created on: 31.07.2008
 *      Author: martin
 */

#ifndef TRACKPOINT_H_
#define TRACKPOINT_H_

#include <QByteArray>
#include <QDateTime>
#include <QPointF>

#include <projects.h>

#include "CommonAttributes.h"
#include "CommonTrackAttributes.h"

class TrackPoint : public CommonAttributes, public CommonTrackAttributes {
public:
	TrackPoint(QByteArray data);
	TrackPoint();
	virtual ~TrackPoint();

	bool isBeginOfTrack();
	void isBeginOfTrack(bool begin);
	bool isLogPoint();
	void isLogPoint(bool logpoint);
	bool isOverSpeed();
	void isOverSpeed(bool overspeed);

	void setPJ(PJ* pj);

	void setXY(double x, double y );
	QPointF getXY(void);

	double getX();
	double getY();

	void setLatLong(double lat, double lng);
	QPointF getLatLong(void);

	double getLat();
	void setLat(double lat);

	double getLong();
	void setLong(double lng);

	double getAlt();
	void setAlt(double alt);
	bool validAlt();

	QDateTime getTime();
	void setTime(QDateTime dt);
    bool validTime();

	void setMagneticVariation(double degrees);
	double getMagneticVariation();
	bool validMagneticVariation();

	void setGeoidHeight(int meters);
	int getGeoidHeight();
	bool validGeoidHeight();


	void setSymbol(QString sym);
	QString getSymbol();
	bool validSymbol();


	void setFixType(QString type);
	QString getFixType();
	bool validFixType();


	void setNumSats(int num_sats);
	int getNumSats();
	bool validNumSats();

	void setHdop(int hdop);
	int getHdop();
	bool validHdop();

	void setVdop(int vdop);
	int getVdop();
	bool validVdop();

	void setPdop(int pdop);
	int getPdop();
	bool validPdop();

	void setDgpsAge(int dgps_age_in_s);
	int getDgpsAge();
	bool validDgpsAge();

	void setDgpsStationId(int station_id);
	int getDgpsStationId();
	bool validDgpsStationId();

	double getDist();
	void setDist(double dist);

	double getSpeed();
	void setSpeed(double speed);

	static int size();


private:
	QByteArray m_data;
    static const int m_size;

    void initMetaData();

    double m_lat;
    double m_lng;

    PJ* m_pj;

    double m_trans_x;
    double m_trans_y;

    //    <ele> xsd:decimal </ele> [0..1]
    //    m_alt < -1000000 == not set
    double m_alt;

	//    <time> xsd:dateTime </time> [0..1]
    QDateTime m_time;

	//    <magvar> degreesType </magvar> [0..1]
    //    m_magmetic_variation > 1000.0 == not set
    double m_magmetic_variation;

    //    <geoidheight> xsd:decimal </geoidheight> [0..1]
    //    INT_MIN == not set
	int m_geoid_height;

	//    <sym> xsd:string </sym> [0..1]
	QString m_symbol;

	//    <fix> fixType </fix> [0..1]
	// {none|2d|3d|dgps|pps}
	QString m_fix_type;

	//    <sat> xsd:nonNegativeInteger </sat> [0..1]
	//   -1 == not set
	int m_num_sats;

	//    <hdop> xsd:decimal </hdop> [0..1]
	//   -1 == not set
	int m_hdop;

	//    <vdop> xsd:decimal </vdop> [0..1]
	//   -1 == not set
	int m_vdop;

	//    <pdop> xsd:decimal </pdop> [0..1]
	//   -1 == not set
	int m_pdop;

	//    <ageofdgpsdata> xsd:decimal </ageofdgpsdata> [0..1]
	//    in seconds; -1 == not set
	int m_age_of_dgps_data;

	//    <dgpsid> dgpsStationType </dgpsid> [0..1]
	//    0 <= value <= 1023   -1 == not set;
	int m_dgps_station_id;


	// distance between this TrackPoint and begin of Track in meters.
	// 0 for first TrackPoint of a Track, that is if m_is_begin_of_track == true
	double m_dist;

	// speed between this TrackPoint and the previous one in meters per second.
	// not defined for first TrackPoint of a Track, that is if m_is_begin_of_track == true
	double m_speed;

    bool m_is_log_point;
    bool m_is_begin_of_track;
    bool m_is_over_speed;

};

#endif /* TRACKPOINT_H_ */
