/*
 * CommonAttributes.cpp
 *
 *  Created on: 18.08.2008
 *      Author: martin
 */

#include "CommonAttributes.h"

CommonAttributes::CommonAttributes() {
	// TODO Auto-generated constructor stub
	initMetaData();
}

CommonAttributes::~CommonAttributes() {
	// TODO Auto-generated destructor stub
}


void CommonAttributes::initMetaData() {

	m_name.clear();

	m_description.clear();

	m_link_url.clear();
	m_link_mimetype.clear();
	m_link_text.clear();

}


void CommonAttributes::setName(QString name) {
	m_name = name;
}

QString CommonAttributes::getName() {
	return m_name;
}

bool CommonAttributes::validName() {
	return !(m_name.isEmpty());
}


void CommonAttributes::setDescription(QString desc) {
	m_description = desc;
}

QString CommonAttributes::getDescription() {
	return m_description;
}

bool CommonAttributes::validDescription() {
	return !(m_description.isEmpty());
}



void CommonAttributes::setLinkUrl(QString url) {
	m_link_url = url;
}

QString CommonAttributes::getLinkUrl() {
	return m_link_url;
}

bool CommonAttributes::validLinkUrl() {
	return !(m_link_url.isEmpty());
}

void CommonAttributes::setLinkMimeType(QString mime_type) {
	m_link_mimetype = mime_type;
}

QString CommonAttributes::getLinkMimeType() {
	return m_link_mimetype;
}

bool CommonAttributes::validLinkMimeType() {
	return !(m_link_mimetype.isEmpty());
}

void CommonAttributes::setLinkText(QString text) {
	m_link_text = text;
}

QString CommonAttributes::getLinkText() {
	return m_link_text;
}

bool CommonAttributes::validLinkText() {
	return !(m_link_text.isEmpty());
}
