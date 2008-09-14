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

//	void setName(QString name);
//	QString getName();

	void setMagneticVariation(double degrees);
	double getMagneticVariation();
	bool validMagneticVariation();

	void setGeoidHeight(int meters);
	int getGeoidHeight();
	bool validGeoidHeight();

//	void setComment(QString comment);
//	QString getComment();

//	void setDescription(QString desc);
//	QString getDescription();

//	void setDataSource(QString src);
//	QString getDataSource();

//	void setLinkUrl(QString url);
//	QString getLinkUrl();

//	void setLinkMimeType(QString mime_type);
//	QString getLinkMimeType();
//
//	void setLinkText(QString text);
//	QString getLinkText();

	void setSymbol(QString sym);
	QString getSymbol();
	bool validSymbol();

//	void setType(QString type);
//	QString getType();

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


	static const int size();

private:
	QByteArray m_data;
    static const int m_size;

    void initMetaData();

    double m_lat;
    double m_lng;

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

    //    <name> xsd:string </name> [0..1]
//	QString m_name;

	//    <cmt> xsd:string </cmt> [0..1]
//	QString m_comment;

	//    <desc> xsd:string </desc> [0..1]
//	QString m_description;

	//    <src> xsd:string </src> [0..1]
//	QString m_data_source;

	//    <link> linkType </link> [0..*]
//	QString m_link_url;
//	QString m_link_mime_type;
//	QString m_link_text;

	//    <sym> xsd:string </sym> [0..1]
	QString m_symbol;

	//    <type> xsd:string </type> [0..1]
//	QString m_type;

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



    bool m_is_log_point;
    bool m_is_begin_of_track;
    bool m_is_over_speed;

};

#endif /* TRACKPOINT_H_ */
