/*
 * gpxFile.cpp
 *
 *  Created on: 15.08.2008
 *      Author: martin
 */

#include <QDebug>

#include "gpxFile.h"
#include "TrackCollection.h"

gpxFile::gpxFile() {
	m_track_collection = 0;
	m_xml_writer = new QXmlStreamWriter();
	m_xml_writer->setAutoFormatting(true);

}

gpxFile::~gpxFile() {
	qDebug() << QString("gpxFile D-tor");
	delete m_xml_writer;
	m_track_collection = 0;
}

TrackCollection* gpxFile::read(QString filename) {
	qDebug() << QString("gpxFile::read( %1 )").arg(filename);
	TrackCollection* tc = 0;
	m_file = new QFile(filename);



	delete m_file;
	return tc;
}

void gpxFile::write(TrackCollection* tc,  QString filename) {
	qDebug() << QString("gpxFile::write( %1 )").arg(filename);
	m_track_collection = tc;
	m_file = new QFile(filename);
	m_file->open(QIODevice::ReadWrite|QIODevice::Truncate);
	m_xml_writer->setDevice(m_file);


	m_xml_writer->writeStartDocument();
	// m_xml_writer->writeDTD("<!DOCTYPE xbel>");
	m_xml_writer->writeStartElement("gpx");
	m_xml_writer->writeAttribute("version", "1.1");
	m_xml_writer->writeAttribute("creator" , "TrackEditor");
	m_xml_writer->writeAttribute("xmlns" , "http://www.topografix.com/GPX/1/1");
	m_xml_writer->writeAttribute("xmlns:xsi", "http://www.topografix.com/GPX/1/1/gpx.xsd");

	// following attribute makes GPX file fail to validate. It was seen in some GPX files produced by
	// python "wintec-tools" ( http://www.steffensiebert.de/soft/python/wintec_tools.html ) but fail
	// validation via "xmllint --noout --schema http://www.topografix.com/GPX/1/1/gpx.xsd testfile.gpx"
	//m_xml_writer->writeAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd http://www.topografix.com/GPX/gpx_overlay/0/3 http://www.topografix.com/GPX/gpx_overlay/0/3/gpx_overlay.xsd http://www.topografix.com/GPX/gpx_modified/0/1 http://www.topografix.com/GPX/gpx_modified/0/1/gpx_modified.xsd");

	write_metadata();

	write_logpoints();
	write_routes();
	write_tracks();
	write_extensions();

    m_xml_writer->writeEndDocument();

    m_file->close();
	delete m_file;
}


void gpxFile::write_metadata() {
	m_xml_writer->writeStartElement("metadata");

	// name
	if(m_track_collection->validName()) {
		m_xml_writer->writeStartElement( "name" );
		m_xml_writer->writeCharacters("GPS-Track");
		m_xml_writer->writeEndElement();
	}

	// description
	if(m_track_collection->validDescription()) {
		m_xml_writer->writeStartElement( "desc" );
		m_xml_writer->writeCharacters("GPS Track created by Track Editor");
		m_xml_writer->writeEndElement();
	}

	// author
	if(m_track_collection->validAuthor()) {
		m_xml_writer->writeStartElement( "author" );
		if(m_track_collection->validAuthorName()) {
			m_xml_writer->writeStartElement( "name" );
			m_xml_writer->writeCharacters(m_track_collection->getAuthorName());
			m_xml_writer->writeEndElement();
		}
		if(m_track_collection->validAuthorEmail()) {
			m_xml_writer->writeStartElement( "email" );
			m_xml_writer->writeStartElement( "id" );
			m_xml_writer->writeCharacters(m_track_collection->getAuthorEMail().section('@',0));
			m_xml_writer->writeEndElement();

			m_xml_writer->writeStartElement( "domain" );
			m_xml_writer->writeCharacters(m_track_collection->getAuthorEMail().section('@',-1));
			m_xml_writer->writeEndElement();
			m_xml_writer->writeEndElement();
		}
	}

	if(m_track_collection->validCopyrightAuthor()) {
		m_xml_writer->writeStartElement( "copyright" );
		m_xml_writer->writeAttribute("author", m_track_collection->getCopyrightAuthor());

		if(m_track_collection->validCopyrightYear()) {
			m_xml_writer->writeStartElement( "year" );
			m_xml_writer->writeCharacters(QString::number(m_track_collection->getCopyrightYear(), 10));
			m_xml_writer->writeEndElement();
		}

		if(m_track_collection->validCopyrightLicenseUrl()) {
			m_xml_writer->writeStartElement( "license" );
			m_xml_writer->writeCharacters(m_track_collection->getCopyrightLicenseUrl());
			m_xml_writer->writeEndElement();
		}

		m_xml_writer->writeEndElement();
	}

	if(m_track_collection->validLinkUrl()) {
		m_xml_writer->writeStartElement( "link" );
		m_xml_writer->writeAttribute("href", m_track_collection->getLinkUrl());
		if(m_track_collection->validLinkText()) {
			m_xml_writer->writeStartElement( "text" );
			m_xml_writer->writeCharacters(m_track_collection->getLinkText());
			m_xml_writer->writeEndElement();
		}
		if(m_track_collection->validLinkMimeType()) {
			m_xml_writer->writeStartElement( "type" );
			m_xml_writer->writeCharacters(m_track_collection->getLinkMimeType());
			m_xml_writer->writeEndElement();
		}
		m_xml_writer->writeEndElement();
	}

	if(m_track_collection->validDateTime()) {
		m_xml_writer->writeStartElement( "time" );
		m_xml_writer->writeCharacters(m_track_collection->getDateTime().toUTC().toString("yyyy-MM-ddThh:mm:ssZ"));
		m_xml_writer->writeEndElement();
	}

	if(m_track_collection->validKeywords()) {
		m_xml_writer->writeStartElement( "keywords" );
		m_xml_writer->writeCharacters(m_track_collection->getKeywords());
		m_xml_writer->writeEndElement();
	}

	if(m_track_collection->validBounds()) {

		QRectF dim = m_track_collection->getDimension(m_track_collection->getIndexList());
		double minlat = dim.bottom();
		double minlon = dim.left();
		double maxlat = dim.top();
		double maxlon = dim.right();

		m_xml_writer->writeStartElement( "bounds" );
		m_xml_writer->writeAttribute("minlat", QString::number(minlat, 10, 8));
		m_xml_writer->writeAttribute("minlon", QString::number(minlon, 10, 8));
		m_xml_writer->writeAttribute("maxlat", QString::number(maxlat, 10, 8));
		m_xml_writer->writeAttribute("maxlon", QString::number(maxlon, 10, 8));
		m_xml_writer->writeEndElement();
	}

	// if(m_track_collection->validExtension()) {
	//
	// }


	m_xml_writer->writeEndElement();
}

void gpxFile::write_logpoints() {
	QRectF bounds = m_track_collection->getDimension();
	for(int i=0; i < m_track_collection->getNumWaypoints(); i++) {
		TrackPoint* tp = m_track_collection->getWaypoints()->at(i);
		if( bounds.contains(QPointF(tp->getLong(), tp->getLat()))) {
			m_xml_writer->writeStartElement("wpt");
			write_waypoint_details(m_track_collection->getWaypoints()->at(i));
			m_xml_writer->writeEndElement();
		}
	}
}

void gpxFile::write_routes() {
	// no routes supported yet.
}

void gpxFile::write_tracks() {

    QModelIndexList mi = m_track_collection->getIndexList();
    for(int mi_idx = 0; mi_idx < mi.size(); mi_idx++ ) {
    	int tr_idx = mi.at(mi_idx).row();

//  for complete GPX file
//	for(int i=0; i < m_track_collection->size(); i++) {
		qDebug() << QString("write_tracks %1").arg(mi_idx);
		m_xml_writer->writeStartElement("trk");
		Track* trk = m_track_collection->at(tr_idx);

		if(trk->validName()) {
			m_xml_writer->writeStartElement("name");
			m_xml_writer->writeCharacters(trk->getName());
			m_xml_writer->writeEndElement();
		}

		if(trk->validComment()) {
			m_xml_writer->writeStartElement("cmt");
			m_xml_writer->writeCharacters(trk->getComment());
			m_xml_writer->writeEndElement();
		}

		if(trk->validDescription()) {
			m_xml_writer->writeStartElement("desc");
			m_xml_writer->writeCharacters(trk->getDescription());
			m_xml_writer->writeEndElement();
		}

		if(trk->validDataSource()) {
			m_xml_writer->writeStartElement("src");
			m_xml_writer->writeCharacters("source");
			m_xml_writer->writeEndElement();
		}


		if(trk->validLinkUrl()) {
			m_xml_writer->writeStartElement( "link" );
			m_xml_writer->writeAttribute("href", trk->getLinkUrl());
			if(trk->validLinkText()) {
				m_xml_writer->writeStartElement( "text" );
				m_xml_writer->writeCharacters(trk->getLinkText());
				m_xml_writer->writeEndElement();
			}
			if(m_track_collection->validLinkMimeType()) {
				m_xml_writer->writeStartElement( "type" );
				m_xml_writer->writeCharacters(trk->getLinkMimeType());
				m_xml_writer->writeEndElement();
			}
			m_xml_writer->writeEndElement();
		}

		if(trk->validIndex()) {
			m_xml_writer->writeStartElement("number");
			// write index from track description in gpx file
			//m_xml_writer->writeCharacters(QString::number(trk->getIndex(), 10));

			// write logical index for new file
			m_xml_writer->writeCharacters(QString::number(mi_idx, 10));
			m_xml_writer->writeEndElement();
		}

		if(trk->validType()) {
			m_xml_writer->writeStartElement("type");
			m_xml_writer->writeCharacters(trk->getType());
			m_xml_writer->writeEndElement();
		}

		//<extensions> extensionsType </extensions> [0..1] ?
		write_extensions();

		//<trkseg> trksegType </trkseg> [0..*] ?
		m_xml_writer->writeStartElement("trkseg");

		for(int j = 0; j < m_track_collection->at(tr_idx)->size(); j++) {
			m_xml_writer->writeStartElement("trkpt");
			write_waypoint_details(m_track_collection->at(tr_idx)->at(j));
			m_xml_writer->writeEndElement();
		}

		m_xml_writer->writeEndElement();

		m_xml_writer->writeEndElement();

	}
	// <trk> trkType </trk> [0..*] ?
}

void gpxFile::write_extensions() {
	return;
}



void gpxFile::write_waypoint_details(TrackPoint* tp) {
	m_xml_writer->writeAttribute("lat", QString().setNum(tp->getLat(), 10, 8));
	m_xml_writer->writeAttribute("lon", QString().setNum(tp->getLong(), 10, 8));

	if(tp->validAlt()) {
		m_xml_writer->writeStartElement("ele");
		m_xml_writer->writeCharacters(QString().setNum(tp->getAlt(), 10, 8));
		m_xml_writer->writeEndElement();
	}

	if(tp->validTime()) {
		m_xml_writer->writeStartElement("time");
		m_xml_writer->writeCharacters(tp->getTime().toUTC().toString("yyyy-MM-ddThh:mm:ssZ"));
		m_xml_writer->writeEndElement();
	}

	if(tp->validMagneticVariation()) {
		m_xml_writer->writeStartElement("magvar");
		m_xml_writer->writeCharacters(QString::number(tp->getMagneticVariation(),10, 2));
		m_xml_writer->writeEndElement();
	}

	if(tp->validGeoidHeight()) {
		m_xml_writer->writeStartElement("geoidheight");
		m_xml_writer->writeCharacters(QString::number(tp->getGeoidHeight(), 10));
		m_xml_writer->writeEndElement();
	}

	if(tp->validName()) {
		m_xml_writer->writeStartElement("name");
		m_xml_writer->writeCharacters(tp->getName());
		m_xml_writer->writeEndElement();
	}

	if(tp->validComment()) {
		m_xml_writer->writeStartElement("cmt");
		m_xml_writer->writeCharacters(tp->getComment());
		m_xml_writer->writeEndElement();
	}

	if(tp->validDescription()) {
		m_xml_writer->writeStartElement("desc");
		m_xml_writer->writeCharacters(tp->getDescription());
		m_xml_writer->writeEndElement();
	}

	if(tp->validDataSource()) {
		m_xml_writer->writeStartElement("src");
		m_xml_writer->writeCharacters(tp->getDataSource());
		m_xml_writer->writeEndElement();
	}

	if(tp->validFixType()) {
		m_xml_writer->writeStartElement("fix");
		m_xml_writer->writeCharacters(tp->getFixType());
		m_xml_writer->writeEndElement();
	}

	if(tp->validNumSats()) {
		m_xml_writer->writeStartElement("sat");
		m_xml_writer->writeCharacters(QString::number(tp->getNumSats(), 10));
		m_xml_writer->writeEndElement();
	}

	if(tp->validHdop()) {
		m_xml_writer->writeStartElement("hdop");
		m_xml_writer->writeCharacters(QString::number(tp->getHdop(), 10));
		m_xml_writer->writeEndElement();
	}

	if(tp->validVdop()) {
		m_xml_writer->writeStartElement("vdop");
		m_xml_writer->writeCharacters(QString::number(tp->getVdop(),10));
		m_xml_writer->writeEndElement();
	}

	if(tp->validPdop()) {
		m_xml_writer->writeStartElement("pdop");
		m_xml_writer->writeCharacters(QString::number(tp->getPdop(), 10));
		m_xml_writer->writeEndElement();
	}

	if(tp->validDgpsAge()) {
		m_xml_writer->writeStartElement("ageofdgpsdata");
		m_xml_writer->writeCharacters(QString::number(tp->getDgpsAge(),10));
		m_xml_writer->writeEndElement();
	}

	if(tp->validDgpsStationId()) {
		m_xml_writer->writeStartElement("dgpsid");
		m_xml_writer->writeCharacters(QString::number(tp->getDgpsStationId(),10));
		m_xml_writer->writeEndElement();
	}

	//m_xml_writer->writeStartElement("extensions");
	//m_xml_writer->writeCharacters("extensions here .......");
	//m_xml_writer->writeEndElement();

}

