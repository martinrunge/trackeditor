/*
 * CSettings.cpp
 *
 *  Created on: 14.02.2009
 *      Author: martin
 */

#include "CSettings.h"

#include <QString>
#include <QDebug>
#include <QList>
#include <QStringList>

CSettings::CSettings() {
	// TODO Auto-generated constructor stub

}

CSettings::~CSettings() {
	// TODO Auto-generated destructor stub
	save();
}

void CSettings::load() {
	QStringList distList;
	distList = m_settings.value("diagrams/distance").toStringList();
	for(int i=0; i < distList.size(); i++) {
		if(PlotData::YTypeNamesForSettings.contains( distList[i] )) {
			m_dist_quantities.append(PlotData::YTypeNamesForSettings[ distList[i] ]);
		}
	}

	QStringList timeList;
	timeList = m_settings.value("diagrams/time").toStringList();
	for(int i=0; i < timeList.size(); i++) {
		if(PlotData::YTypeNamesForSettings.contains( timeList[i] )) {
			m_time_quantities.append(PlotData::YTypeNamesForSettings[ timeList[i] ]);
		}
	}

	QStringList trackPointsList;
	trackPointsList = m_settings.value("diagrams/trackpoints").toStringList();
	for(int i=0; i < trackPointsList.size(); i++) {
		if(PlotData::YTypeNamesForSettings.contains( trackPointsList[i] )) {
			m_trackpoints_quantities.append(PlotData::YTypeNamesForSettings[ trackPointsList[i] ]);
		}
	}
}

void CSettings::save() {
	QStringList distList;
	qDebug() << QString("CSettings::save()");
	QStringList keys = PlotData::YTypeNamesForSettings.keys();
	for(int i=0; i < m_dist_quantities.size(); i++) {
		for(int j=0; j < keys.size(); j++) {
			if( m_dist_quantities[i] == PlotData::YTypeNamesForSettings[ keys[j] ]) {
				QString label = keys[j];
				distList.append( label );
				continue;
			}
		}
	}
	m_settings.setValue("diagrams/distance", distList);

	QStringList timeList;
	for(int i=0; i < m_time_quantities.size(); i++) {
		for(int j=0; j < keys.size(); j++) {
			if( m_time_quantities[i] == PlotData::YTypeNamesForSettings[ keys[j] ]) {
				QString label = keys[j];
				timeList.append( label );
				continue;
			}
		}
	}
	m_settings.setValue("diagrams/time", timeList);

	QStringList trackpointsList;
	for(int i=0; i < m_trackpoints_quantities.size(); i++) {
		for(int j=0; j < keys.size(); j++) {
			if( m_trackpoints_quantities[i] == PlotData::YTypeNamesForSettings[ keys[j] ]) {
				QString label = keys[j];
				trackpointsList.append( label );
				continue;
			}
		}
	}
	m_settings.setValue("diagrams/trackpoints", trackpointsList);

}



QList<enum plotTypeY> CSettings::getDistQuantities() {
	return m_dist_quantities;
}

void CSettings::setDistQuantities(QList<enum plotTypeY> values) {
	m_dist_quantities = values;
}

QList<enum plotTypeY> CSettings::getTimeQuantities() {
	return m_time_quantities;
}

void CSettings::setTimeQuantities(QList<enum plotTypeY> values) {
	m_time_quantities = values;
}

QList<enum plotTypeY> CSettings::getTrackpointsQuantities() {
	return m_trackpoints_quantities;
}

void CSettings::setTrackpointsQuantities(QList<enum plotTypeY> values) {
	m_trackpoints_quantities = values;
}


