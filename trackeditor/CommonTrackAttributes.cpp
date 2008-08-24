/*
 * CommonTrackAttributes.cpp
 *
 *  Created on: 18.08.2008
 *      Author: martin
 */

#include "CommonTrackAttributes.h"

CommonTrackAttributes::CommonTrackAttributes() {
	// TODO Auto-generated constructor stub
	initMetaData();
}

CommonTrackAttributes::~CommonTrackAttributes() {
	// TODO Auto-generated destructor stub
}


void CommonTrackAttributes::initMetaData() {

	m_comment.clear();
	m_data_src.clear();
	m_type.clear();

}


void CommonTrackAttributes::setComment(QString comment) {
	m_comment = comment;
}

QString CommonTrackAttributes::getComment(void) {
	return m_comment;
}

bool CommonTrackAttributes::validComment(void) {
	return !(m_comment.isEmpty());
}

void CommonTrackAttributes::setDataSource(QString source) {
	m_data_src = source;
}

QString CommonTrackAttributes::getDataSource(void) {
	return m_data_src;
}

bool CommonTrackAttributes::validDataSource(void) {
	return !(m_data_src.isEmpty());
}


void CommonTrackAttributes::setType(QString type) {
	m_type = type;
}

QString CommonTrackAttributes::getType(void) {
	return m_type;
}

bool CommonTrackAttributes::validType(void) {
	return !(m_type.isEmpty());
}

