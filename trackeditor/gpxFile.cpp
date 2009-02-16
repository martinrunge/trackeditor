/*
 * gpxFile.cpp
 *
 *  Created on: 15.08.2008
 *      Author: martin
 */

#include <QDebug>
#include <QMessageBox>
#include <QXmlStreamAttributes>

#include "gpxFile.h"
#include "TrackCollection.h"

gpxFile::gpxFile() {
	m_track_collection = 0;
	m_namespace_uri.clear();
	m_xml_writer = new QXmlStreamWriter();
	m_xml_writer->setAutoFormatting(true);

	m_xml_reader = new QXmlStreamReader();
}

gpxFile::~gpxFile() {
	// qDebug() << QString("gpxFile D-tor");

	delete m_xml_writer;
	delete m_xml_reader;

	m_track_collection = 0;
}

TrackCollection* gpxFile::read(QString filename) {
	qDebug() << QString("gpxFile::read( %1 )").arg(filename);

	m_file = new QFile(filename);
	m_file->open(QIODevice::ReadOnly);
	m_xml_reader->setDevice(m_file);

	m_track_collection = new TrackCollection();

	while (!m_xml_reader->atEnd()) {
		m_xml_reader->readNext();
		if(m_xml_reader->isStartDocument()) {
			qDebug() << QString("StartDocument .... ");
			readDocument();
			qDebug() << QString("EndDocument .... ");
		}
	}
	if (m_xml_reader->hasError()) {
	    QString errormsg = QString("Error parsing GPX file: '%1' at line %2  column %3")
						   .arg(m_xml_reader->errorString())
						   .arg(m_xml_reader->lineNumber())
						   .arg(m_xml_reader->columnNumber());
		qDebug() << errormsg;
	}

	delete m_file;
	return m_track_collection;
}


void gpxFile::readDocument() {
	enum QXmlStreamReader::TokenType type;

	do {

		type = m_xml_reader->readNext();

		switch(type) {
			case QXmlStreamReader::StartDocument:
				qDebug() << QString("StartDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::EndDocument:
				qDebug() << QString("readDocument() : EndDocument found. returning ... ");
				return;
				break;

			case QXmlStreamReader::StartElement:
			{
				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				QXmlStreamAttributes attr;
				if(m_xml_reader->name() == QString("gpx") ) {
					attr = m_xml_reader->attributes();
					QString version = attr.value(QString(), QString("version")).toString();
					QString creator = attr.value(QString(), QString("creator")).toString();
					m_namespace_uri = m_xml_reader->namespaceUri().toString();
					// qDebug() << QString("version: %1  Creator: %2 ns: %3").arg(version).arg(creator).arg(m_namespace_uri);
					readGpxType(version);
				}
				else
				{
					qDebug() << QString("Unknown StartElement '%1' unknown here. Expected 'gpx'").arg(m_xml_reader->name().toString());
				}

				break;
			}
			case QXmlStreamReader::EndElement:
				// qDebug() << QString("EndElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();

				break;

			case QXmlStreamReader::Characters:

				break;

			case QXmlStreamReader::Comment:
				break;

			case QXmlStreamReader::DTD:
				break;

			case QXmlStreamReader::EntityReference:
				break;

			case QXmlStreamReader::ProcessingInstruction:
				break;

			default:
				qDebug() << "unknown token type!";
		}
//		qDebug() << m_xml_reader->tokenString() << m_xml_reader->name().toString() << m_xml_reader->text().toString();
	} while (!m_xml_reader->atEnd());
}


/**
 * <gpx>
 *   we are here
 * </gpx>
 */
void gpxFile::readGpxType(QString version) {
	enum QXmlStreamReader::TokenType type;

	// assume version "1.1" for now ....

	do {

		type = m_xml_reader->readNext();

		switch(type) {
			case QXmlStreamReader::StartDocument:
				qDebug() << QString("StartDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::EndDocument:
				qDebug() << QString("EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				QXmlStreamAttributes attr;
				if(m_xml_reader->name() == QString("metadata")) {
					readMetadataType();
				}
				if(m_xml_reader->name() == QString("wpt")) {
					readWptType("wpt");
				}
				if(m_xml_reader->name() == QString("rte")) {
					Track* rte = readRteType();
					m_track_collection->appendTrack(rte);
				}
				if(m_xml_reader->name() == QString("trk")) {
					Track *tr = readTrkType();
					m_track_collection->appendTrack(tr);
				}

				break;
			}
			case QXmlStreamReader::EndElement:
				// expect </gpx> only !!!
				if(m_xml_reader->name() == QString("gpx")) {
					m_track_collection->commit();
					return;
				}
				else {
					qDebug() << QString("EndElement: expected 'gpx' but got: '%1'!").arg(m_xml_reader->name().toString());
				}

				break;

			case QXmlStreamReader::Characters:

				break;

			case QXmlStreamReader::Comment:
				break;

			case QXmlStreamReader::DTD:
				break;

			case QXmlStreamReader::EntityReference:
				break;

			case QXmlStreamReader::ProcessingInstruction:
				break;

			default:
				qDebug() << "unknown token type!";
		}
//		qDebug() << m_xml_reader->tokenString() << m_xml_reader->name().toString() << m_xml_reader->text().toString();
	} while (!m_xml_reader->atEnd());
}


void gpxFile::readMetadataType() {
	enum QXmlStreamReader::TokenType type;
	QString tmp_string, open_tag;
	do {
		type = m_xml_reader->readNext();
		switch(type) {
			case QXmlStreamReader::StartDocument:
				qDebug() << QString("StartDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::EndDocument:
				qDebug() << QString("EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				QXmlStreamAttributes attr;
				tmp_string.clear();
				open_tag.clear();

				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				if(m_xml_reader->name() == QString("name")) {
					open_tag = QString("name");
				}
				if(m_xml_reader->name() == QString("desc")) {
					open_tag = QString("desc");
				}
				if(m_xml_reader->name() == QString("author")) {
					personType pt = readPersonType();

					m_track_collection->setAuthorName(pt.name);
					m_track_collection->setAuthorEMail(QString("%1@%2").arg(pt.email.id).arg(pt.email.domain));
					m_track_collection->setAuthorLinkUrl(pt.link.uri);
					m_track_collection->setAuthorLinkText(pt.link.text);
					m_track_collection->setAuthorLinkMimeType(pt.link.type);
				}
				if(m_xml_reader->name() == QString("time")) {
					open_tag = QString("time");
				}
				if(m_xml_reader->name() == QString("keywords")) {
					open_tag = QString("keywords");
				}
				if(m_xml_reader->name() == QString("bounds")) {
					open_tag = QString("bounds");
				}
				if(m_xml_reader->name() == QString("link")) {
					linkType lt = readLinkType();
					if(lt.isValid()) {
						m_track_collection->setLinkUrl(lt.uri);
						m_track_collection->setLinkMimeType(lt.type);
						m_track_collection->setLinkText(lt.text);
					}
					else {
						m_track_collection->setLinkUrl(QString());
					}
				}

				break;
			}
			case QXmlStreamReader::EndElement:
				// return tag for this state: </metadata>
				if(m_xml_reader->name() == open_tag) {
					if(open_tag == QString("name")) {
						m_track_collection->setName(tmp_string);
					}
					if(open_tag == QString("desc")) {
						m_track_collection->setDescription(tmp_string);
					}
					if(open_tag == QString("time")) {
						m_track_collection->setDateTime(readXsdDateTime(tmp_string));
					}
					if(open_tag == QString("keywords")) {
						m_track_collection->setKeywords(tmp_string);
					}
					open_tag.clear();
					tmp_string.clear();
				}
				else {
					if(m_xml_reader->name() == QString("metadata")) {
						return;
					}
					else {
						qDebug() << QString("EndElement: expected 'metadata' but got: '%1'!").arg(m_xml_reader->name().toString());
					}
				}

				break;

			case QXmlStreamReader::Characters:
				tmp_string.append(m_xml_reader->text());
				break;

			case QXmlStreamReader::Comment:
				break;

			default:
				qDebug() << "unknown token type!";
		}
//		qDebug() << m_xml_reader->tokenString() << m_xml_reader->name().toString() << m_xml_reader->text().toString();
	} while (!m_xml_reader->atEnd());
}

personType gpxFile::readPersonType() {
	personType pt;
	enum QXmlStreamReader::TokenType type;
	QString tmp_string, open_tag;
	do {
		type = m_xml_reader->readNext();
		switch(type) {
			case QXmlStreamReader::StartDocument:
				qDebug() << QString("StartDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::EndDocument:
				qDebug() << QString("EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				tmp_string.clear();
				open_tag.clear();

				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				if(m_xml_reader->name() == QString("name")) {
					open_tag = QString("name");
				}
				if(m_xml_reader->name() == QString("link")) {
					linkType lt = readLinkType();
					if(lt.isValid()) {
						pt.link = lt;
					}
				}
				if(m_xml_reader->name() == QString("email")) {
					emailType et = readEmailType();
					if(et.isValid()) {
						pt.email = et;
					}
				}
				break;
			}
			case QXmlStreamReader::EndElement:
				// return tag for this state: </copyright>
				if(m_xml_reader->name() == open_tag) {
					if(open_tag == QString("name")) {
						pt.name = tmp_string;
					}
				}
				else {
					if(m_xml_reader->name() == QString("author")) {
						return pt;
					}
					else {
						qDebug() << QString("EndElement: expected 'license' but got: '%1'!").arg(m_xml_reader->name().toString());
					}
				}
				break;

			case QXmlStreamReader::Characters:
				tmp_string.append(m_xml_reader->text());
				break;
			default:
				qDebug() << "unknown token type!";
		}
	} while (!m_xml_reader->atEnd());
	return pt;
}


void gpxFile::readCopyrightType() {
	enum QXmlStreamReader::TokenType type;
	QString tmp_string, open_tag;
	do {
		type = m_xml_reader->readNext();
		switch(type) {
			case QXmlStreamReader::StartDocument:
				qDebug() << QString("StartDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::EndDocument:
				qDebug() << QString("EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				tmp_string.clear();
				open_tag.clear();

				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				if(m_xml_reader->name() == QString("author")) {
					open_tag = QString("author");
				}
				if(m_xml_reader->name() == QString("year")) {
					open_tag = QString("year");
				}
				if(m_xml_reader->name() == QString("license")) {
					open_tag = QString("license");
				}
				break;
			}
			case QXmlStreamReader::EndElement:
				// return tag for this state: </copyright>
				if(m_xml_reader->name() == open_tag) {
					if(open_tag == QString("author")) {
						m_track_collection->setCopyrightAuthor(tmp_string);
					}
					if(open_tag == QString("year")) {
						bool ok;
						int year = tmp_string.toInt(&ok, 10);
						if(ok) {
							m_track_collection->setCopyrightYear(year);
						}
						else {
							m_track_collection->setCopyrightYear(0);
						}
					}
					if(open_tag == QString("license")) {
						m_track_collection->setCopyrightLicenseUrl(tmp_string);
					}
					open_tag.clear();
					tmp_string.clear();
				}
				else {
					if(m_xml_reader->name() == QString("license")) {
						return;
					}
					else {
						qDebug() << QString("EndElement: expected 'license' but got: '%1'!").arg(m_xml_reader->name().toString());
					}
				}
				break;

			case QXmlStreamReader::Characters:
				tmp_string.append(m_xml_reader->text());
				break;
			default:
				qDebug() << "unknown token type!";
		}
	} while (!m_xml_reader->atEnd());
}

linkType gpxFile::readLinkType() {
	QXmlStreamAttributes attr = m_xml_reader->attributes();
	QString href = attr.value(QString(), QString("href")).toString();
	// qDebug() << QString("link (raw): href=%1").arg(href);
	if(href.startsWith('"')) {
		href = href.right(href.size() - 1);
	}
	if(href.endsWith('"')) {
		href.chop(1);
	}

	enum QXmlStreamReader::TokenType type;
	linkType lt;
	lt.uri = href;
	QString tmp_string, open_tag;
	do {
		type = m_xml_reader->readNext();
		switch(type) {
			case QXmlStreamReader::StartDocument:
				qDebug() << QString("StartDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::EndDocument:
				qDebug() << QString("EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				tmp_string.clear();
				open_tag.clear();

				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				if(m_xml_reader->name() == QString("text")) {
					open_tag = QString("text");
				}
				if(m_xml_reader->name() == QString("type")) {
					open_tag = QString("type");
				}
				break;
			}
			case QXmlStreamReader::EndElement:
				// return tag for this state: </copyright>
				if(m_xml_reader->name() == open_tag) {
					if(open_tag == QString("text")) {
						lt.text = tmp_string;
					}
					if(open_tag == QString("type")) {
						lt.type = tmp_string;
					}
					open_tag.clear();
					tmp_string.clear();
				}
				else {
					if(m_xml_reader->name() == QString("link")) {
						return lt;
					}
					else {
						qDebug() << QString("EndElement: expected 'license' but got: '%1'!").arg(m_xml_reader->name().toString());
					}
				}
				break;

			case QXmlStreamReader::Characters:
				tmp_string.append(m_xml_reader->text());
				break;
			default:
				qDebug() << "unknown token type!";
		}
	} while (!m_xml_reader->atEnd());
	return lt;
}

emailType gpxFile::readEmailType() {
	QXmlStreamAttributes attr = m_xml_reader->attributes();
	emailType et;
	et.id = attr.value(QString(), QString("id")).toString();
	et.domain = attr.value(QString(), QString("domain")).toString();
	// qDebug() << QString("email:%1@%2").arg(et.id).arg(et.domain);

	// read the </email> end tag
	do {
		m_xml_reader->readNext();
	} while( m_xml_reader->isEndElement() && m_xml_reader->name() == QString("email") );
	return et;
}


TrackPoint* gpxFile::readWptType(QString tagname) {
	TrackPoint* tp = new TrackPoint();
	QXmlStreamAttributes attr = m_xml_reader->attributes();
	bool ok;
	double lat = attr.value(QString(), QString("lat")).toString().toDouble(&ok);
	if(!ok) {
		delete tp;
		tp = 0;
		return tp;
	}
	double lon = attr.value(QString(), QString("lon")).toString().toDouble(&ok);
	if(!ok) {
		delete tp;
		tp = 0;
		return 0;
	}

	tp->setLat(lat);
	tp->setLong(lon);

	QString tmp_string, open_tag;
	enum QXmlStreamReader::TokenType type;
	do {
		type = m_xml_reader->readNext();
		switch(type) {
			case QXmlStreamReader::StartDocument:
			case QXmlStreamReader::EndDocument:
				qDebug() << QString("Start- or EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				tmp_string.clear();
				open_tag.clear();
				if(m_xml_reader->name() == QString("ele")) {
					open_tag = QString("ele");
				}
				if(m_xml_reader->name() == QString("time")) {
					open_tag = QString("time");
				}
				if(m_xml_reader->name() == QString("magvar")) {
					open_tag = QString("magvar");
				}
				if(m_xml_reader->name() == QString("geoidheight")) {
					open_tag = QString("geoidheight");
				}
				if(m_xml_reader->name() == QString("name")) {
					open_tag = QString("name");
				}
				if(m_xml_reader->name() == QString("cmt")) {
					open_tag = QString("desc");
				}
				if(m_xml_reader->name() == QString("src")) {
					open_tag = QString("src");
				}
				if(m_xml_reader->name() == QString("link")) {
					linkType lt = readLinkType();
					tp->setLinkUrl(lt.uri);
					tp->setLinkText(lt.text);
					tp->setLinkMimeType(lt.type);
				}
				if(m_xml_reader->name() == QString("sym")) {
					open_tag = QString("sym");
				}
				if(m_xml_reader->name() == QString("type")) {
					open_tag = QString("type");
				}
				if(m_xml_reader->name() == QString("fix")) {
					open_tag = QString("fix");
				}
				if(m_xml_reader->name() == QString("sat")) {
					open_tag = QString("sat");
				}
				if(m_xml_reader->name() == QString("hdop")) {
					open_tag = QString("hdop");
				}
				if(m_xml_reader->name() == QString("vdop")) {
					open_tag = QString("vdop");
				}
				if(m_xml_reader->name() == QString("pdop")) {
					open_tag = QString("pdop");
				}
				if(m_xml_reader->name() == QString("ageofdgpsdata")) {
					open_tag = QString("ageofdgpsdata");
				}
				if(m_xml_reader->name() == QString("dgpsid")) {
					open_tag = QString("dgpsid");
				}
				if(m_xml_reader->name() == QString("extensions")) {
					open_tag = QString("extensions");
				}

				break;
			}
			case QXmlStreamReader::EndElement:
				if(m_xml_reader->name() == open_tag) {
					if(m_xml_reader->name() == QString("ele")) {
						double alt = tmp_string.toDouble(&ok);
						tp->setAlt(alt);
					}
					if(m_xml_reader->name() == QString("time")) {
						tp->setTime(readXsdDateTime(tmp_string));
					}
					if(m_xml_reader->name() == QString("magvar")) {
						double magvar = tmp_string.toDouble(&ok);
						tp->setMagneticVariation(magvar);
					}
					if(m_xml_reader->name() == QString("geoidheight")) {
						double geoidheight = tmp_string.toDouble(&ok);
						tp->setGeoidHeight(geoidheight);
					}
					if(m_xml_reader->name() == QString("name")) {
						tp->setName(tmp_string);
					}
					if(m_xml_reader->name() == QString("cmt")) {
						tp->setComment(tmp_string);
					}
					if(m_xml_reader->name() == QString("src")) {
						tp->setComment(tmp_string);
					}
					if(m_xml_reader->name() == QString("sym")) {
						tp->setSymbol(tmp_string);
					}
					if(m_xml_reader->name() == QString("type")) {
						tp->setType(tmp_string);
					}
					if(m_xml_reader->name() == QString("fix")) {
						tp->setFixType(tmp_string);
					}
					if(m_xml_reader->name() == QString("sat")) {
						unsigned num_sats = tmp_string.toUInt(&ok);
						tp->setNumSats(num_sats);
					}
					if(m_xml_reader->name() == QString("hdop")) {
						double hdop = tmp_string.toDouble(&ok);
						tp->setHdop(hdop);
					}
					if(m_xml_reader->name() == QString("vdop")) {
						double vdop = tmp_string.toDouble(&ok);
						tp->setVdop(vdop);
					}
					if(m_xml_reader->name() == QString("pdop")) {
						double pdop = tmp_string.toDouble(&ok);
						tp->setPdop(pdop);
					}
					if(m_xml_reader->name() == QString("ageofdgpsdata")) {
						double age = tmp_string.toDouble(&ok);
						tp->setDgpsAge(age);
					}
					if(m_xml_reader->name() == QString("dgpsid")) {
						unsigned dgpsid = tmp_string.toUInt(&ok);
						tp->setDgpsStationId(dgpsid);
					}
					if(m_xml_reader->name() == QString("extensions")) {
						qDebug() << QString("found extension: %1").arg(tmp_string);
					}
				}
				else {
					if(m_xml_reader->name() == tagname) {
						return tp;
					}
				}
				break;

			case QXmlStreamReader::Characters:
				tmp_string.append(m_xml_reader->text());
				break;

			case QXmlStreamReader::Comment:
			case QXmlStreamReader::DTD:
			case QXmlStreamReader::EntityReference:
			case QXmlStreamReader::ProcessingInstruction:
				break;

			default:
				qDebug() << "unknown token type!";
		}
//		qDebug() << m_xml_reader->tokenString() << m_xml_reader->name().toString() << m_xml_reader->text().toString();
	} while (!m_xml_reader->atEnd());
	return tp;
}

Track* gpxFile::readRteType() {
	QString tmp_string, open_tag;
	bool ok;

	Track* tr = new Track();

	enum QXmlStreamReader::TokenType type;
	do {
		type = m_xml_reader->readNext();
		switch(type) {
			case QXmlStreamReader::StartDocument:
				qDebug() << QString("StartDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::EndDocument:
				qDebug() << QString("EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				break;
			}
			case QXmlStreamReader::EndElement:
				// expect </rte> only !!!
				if(m_xml_reader->name() == QString("rte")) {
					return tr;
				}
				else {
					qDebug() << QString("EndElement: expected 'rte' but got: '%1'!").arg(m_xml_reader->name().toString());
				}

				break;

			case QXmlStreamReader::Characters:
				tmp_string.append(m_xml_reader->text());
				break;

			case QXmlStreamReader::Comment:
			case QXmlStreamReader::DTD:
			case QXmlStreamReader::EntityReference:
			case QXmlStreamReader::ProcessingInstruction:
				break;

			default:
				qDebug() << "unknown token type!";
		}
//		qDebug() << m_xml_reader->tokenString() << m_xml_reader->name().toString() << m_xml_reader->text().toString();
	} while (!m_xml_reader->atEnd());
	return tr;
}

Track* gpxFile::readTrkType() {
	QString tmp_string, open_tag;
	bool ok;
	int trkseg = 0;
	unsigned track_index;

	Track* tr = new Track();

	enum QXmlStreamReader::TokenType type;
	do {
		type = m_xml_reader->readNext();
		switch(type) {
			case QXmlStreamReader::StartDocument:
			case QXmlStreamReader::EndDocument:
				qDebug() << QString("Start- or EndDocument!! Should never happen here!!! ");
				break;

			case QXmlStreamReader::StartElement:
			{
				// qDebug() << QString("StartElement: ") << m_xml_reader->name().toString() << m_xml_reader->text().toString();
				tmp_string.clear();
				open_tag.clear();

				if(m_xml_reader->name() == QString("name")) {
					open_tag = QString("name");
				}
				if(m_xml_reader->name() == QString("cmt")) {
					open_tag = QString("cmt");
				}
				if(m_xml_reader->name() == QString("desc")) {
					open_tag = QString("desc");
				}
				if(m_xml_reader->name() == QString("src")) {
					open_tag = QString("src");
				}
				if(m_xml_reader->name() == QString("link")) {
					linkType lt = readLinkType();
					tr->setLinkUrl(lt.uri);
					tr->setLinkText(lt.text);
					tr->setLinkMimeType(lt.type);
				}
				if(m_xml_reader->name() == QString("number")) {
					open_tag = QString("number");
				}
				if(m_xml_reader->name() == QString("type")) {
					open_tag = QString("type");
				}
				if(m_xml_reader->name() == QString("extensions")) {
					open_tag = QString("extensions");
				}
				if(m_xml_reader->name() == QString("trkseg")) {
					trkseg++;
				}
				if(m_xml_reader->name() == QString("trkpt")) {
					TrackPoint * tp = readWptType("trkpt");
					if(trkseg == 1) {
						tr->append(tp);
					}
				}


				break;
			}
			case QXmlStreamReader::EndElement:
				// expect </trk> only !!!
				if(m_xml_reader->name() == open_tag) {
					if(m_xml_reader->name() == QString("name")) {
						tr->setName(tmp_string);
					}
					if(m_xml_reader->name() == QString("cmt")) {
						tr->setComment(tmp_string);
					}
					if(m_xml_reader->name() == QString("desc")) {
						tr->setDescription(tmp_string);
					}
					if(m_xml_reader->name() == QString("src")) {
						tr->setDataSource(tmp_string);
					}
					if(m_xml_reader->name() == QString("number")) {
						track_index = tmp_string.toUInt(&ok);
					}
					if(m_xml_reader->name() == QString("type")) {
						tr->setType(tmp_string);
					}
					if(m_xml_reader->name() == QString("extensions")) {
						qDebug() << QString("extensions: %1").arg(tmp_string);
					}
				}
				else {
					if(m_xml_reader->name() == QString("trkseg")) {
						trkseg--;
					}
					else {
						if(m_xml_reader->name() == QString("trk")) {
							tr->setIndex(track_index);
							if(trkseg != 0 ){
								qDebug() << QString("EndElement: got 'trk' end tag with %d trkseg open!!!").arg(trkseg);
							}

							return tr;
						}
						else {
							qDebug() << QString("EndElement: expected 'trk' but got: '%1'!").arg(m_xml_reader->name().toString());
						}
					}
				}
				break;

			case QXmlStreamReader::Characters:
				tmp_string.append(m_xml_reader->text());
				break;

			case QXmlStreamReader::Comment:
			case QXmlStreamReader::DTD:
			case QXmlStreamReader::EntityReference:
			case QXmlStreamReader::ProcessingInstruction:
				break;

			default:
				qDebug() << "unknown token type!";
		}
//		qDebug() << m_xml_reader->tokenString() << m_xml_reader->name().toString() << m_xml_reader->text().toString();
	} while (!m_xml_reader->atEnd());
	return tr;
}



/**
 * TODO: add millisecond support here !!!
 */

QDateTime gpxFile::readXsdDateTime(QString timestring) {
	QDateTime dt;
	bool error = false;
	if(timestring.endsWith('Z')) {
		// time string is in UTC
		dt = QDateTime::fromString(timestring, "yyyy-MM-ddThh:mm:ss'Z'");
		dt.setTimeSpec(Qt::UTC);
		// qDebug() << QString("converting %1 to %2").arg(timestring).arg(dt.toString());
	}
	else {
		QStringList strlist = timestring.split(":");
		if(strlist.size() == 3) {
			// timestring is in format "yyyy-MM-ddThh:mm:ss"
			dt = QDateTime::fromString(timestring, "yyyy-MM-ddThh:mm:ss");
			dt.setTimeSpec(Qt::LocalTime);
		}
		else {
			if(strlist.size() == 4) {
				// timestring is in format "yyyy-MM-ddThh:mm:ss.zzz+01:00"
				bool ok;
				int mins = strlist[3].toInt(&ok, 10);
				if(!ok) error=true;

				int hours = strlist[2].right(3).toInt(&ok, 10);
				if(!ok) error=true;

				// tmpstring = timstring without the "+01:00" at the end
				QString tmpstring = timestring.left(timestring.size() - 6);
				dt = QDateTime::fromString(tmpstring, "yyyy-MM-ddThh:mm:ss");
				dt.setTimeSpec(Qt::UTC);
				dt.addSecs(mins * 60 + hours * 60 * 60);
			}
			else {
				qDebug() << QString("unknown date format: %1   (number of ':' unknown)").arg(timestring);
			}
		}
	}

	if(error) {
		// return an invalid QDateTime
		dt = QDateTime(QDate(0,0,0));
	}

	return dt;
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

		QRectF dim = m_track_collection->getDimension(m_track_collection->getModelIndexList());
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

    std::vector<int> mi = m_track_collection->getIndexList();
    for(unsigned mi_idx = 0; mi_idx < mi.size(); mi_idx++ ) {
    	int tr_idx = mi[mi_idx];

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

