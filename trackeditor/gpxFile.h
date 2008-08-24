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

#include "trackFile.h"

class TrackCollection;
class TrackPoint;

class gpxFile :public trackFile{
public:
	gpxFile();
	virtual ~gpxFile();

	TrackCollection* read(QString filename);
	void write(TrackCollection* tc,  QString filename);

private:
	QXmlStreamWriter* m_xml_writer;
	TrackCollection* m_track_collection;
    QFile* m_file;

	void write_metadata();
	void write_logpoints();
	void write_routes();
	void write_tracks();
	void write_extensions();

	void write_waypoint_details(TrackPoint* tp);

};

#endif /* GPXFILE_H_ */
