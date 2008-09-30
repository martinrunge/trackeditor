/*
 * gpxFile.h
 *
 *  Created on: 15.08.2008
 *      Author: martin
 */

#ifndef GPXFILE_H_
#define GPXFILE_H_

#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDateTime>

#include "trackFile.h"

class TrackCollection;
class TrackPoint;
class Track;


class linkType {
public:
	QString uri;
	QString text;
	QString type;

	inline bool isValid() {
		return (! uri.isEmpty());
	}
};

class emailType {
public:
	QString id;
	QString domain;

	inline bool isValid() {
		return (!id.isEmpty() && !domain.isEmpty());
	}
};

class personType {
public:
	QString name;
	emailType email;
	linkType link;

	inline bool isValid() {
		return (!name.isEmpty());
	}

};


class gpxFile :public trackFile{
public:
	gpxFile();
	virtual ~gpxFile();

	TrackCollection* read(QString filename);
	void write(TrackCollection* tc,  QString filename);


private:
	QXmlStreamWriter* m_xml_writer;
	QXmlStreamReader* m_xml_reader;

	TrackCollection* m_track_collection;
	Track* m_track;
    QFile* m_file;

    void readDocument();
    void readGpxType(QString version);
    void readMetadataType();
    TrackPoint* readWptType(QString tagname);
    Track* readRteType();
    Track* readTrkType();
    void readExtensionType();
    void readTrksegType();
    void readCopyrightType();
    linkType readLinkType();
    emailType readEmailType();
    personType readPersonType();
    void readPtType();
    void readPtsegType();
    QDateTime readXsdDateTime(QString timestring);


	void write_metadata();
	void write_logpoints();
	void write_routes();
	void write_tracks();
	void write_extensions();

	void write_waypoint_details(TrackPoint* tp);

	QString m_namespace_uri;

};

#endif /* GPXFILE_H_ */
