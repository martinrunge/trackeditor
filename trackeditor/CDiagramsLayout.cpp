/*
 * CDiagramsLayout.cpp
 *
 *  Created on: 26.01.2009
 *      Author: martin
 */

#include "CDiagramsLayout.h"
#include "plotWidget.h"
#include "Track.h"


CDiagramsLayout::CDiagramsLayout(QWidget * parent) : QGridLayout(parent) {
	// TODO Auto-generated constructor stub
	// m_plotWidget = new plotWidget();
	// addWidget(m_plotWidget);

}

CDiagramsLayout::~CDiagramsLayout() {
	// TODO Auto-generated destructor stub
	clear();
	// delete m_plotWidget;
}

// void CDiagramsLayout::setTrack(Track* track) {
// 	m_plotWidget->setTrack(track);
//}

void CDiagramsLayout::setTracks(QList<Track*> tracks) {

	QList<plotWidget*>::iterator it;
	for(it = m_distPlots.begin(); it != m_distPlots.end(); it++) {
		if(*it) {
			(*it)->setTracks(tracks);
		}
	}

	for(it = m_timePlots.begin(); it != m_timePlots.end(); it++) {
		if(*it) {
			(*it)->setTracks(tracks);
		}
	}

	for(it = m_trackPointPlots.begin(); it != m_trackPointPlots.end(); it++) {
		if(*it) {
			(*it)->setTracks(tracks);
		}
	}
}

void CDiagramsLayout::clear() {

	QList<plotWidget*>::iterator it;

	for(it = m_distPlots.begin(); it != m_distPlots.end(); it++) {
		if(*it) {
			removeWidget(*it);
			delete *it;
		}
	}
	m_distPlots.clear();

	for(it = m_timePlots.begin(); it != m_timePlots.end(); it++) {
		if(*it) {
			removeWidget(*it);
			delete *it;
		}
	}
	m_timePlots.clear();

	for(it = m_trackPointPlots.begin(); it != m_trackPointPlots.end(); it++) {
		if(*it) {
			removeWidget(*it);
			delete *it;
		}
	}
	m_trackPointPlots.clear();

}

void CDiagramsLayout::setQuantities(QStringList distVals, QStringList timeVals, QStringList trackPointVals) {

	clear();

	plotWidget* widget;
	for(int i=0; i < distVals.size(); i++) {
		widget = new plotWidget(TYPE_X_DIST, TYPE_Y_ALT);
		addWidget(widget, i, 0);
		m_distPlots.append(widget);
	}

	for(int i=0; i < timeVals.size(); i++) {
		widget = new plotWidget(TYPE_X_TIME, TYPE_Y_SPEED);
		addWidget(widget, i, 1);
		m_timePlots.append(widget);
	}

	for(int i=0; i < trackPointVals.size(); i++) {
		widget = new plotWidget(TYPE_X_POINTS, TYPE_Y_SPEED);
		addWidget(widget, i, 3);
		m_trackPointPlots.append(widget);
	}

}

void CDiagramsLayout::setQuantities(QList<enum plotTypeY> distVals, QList<enum plotTypeY> timeVals, QList<enum plotTypeY> trackPointVals) {

	clear();

	plotWidget* widget;
	for(int i=0; i < distVals.size(); i++) {
		widget = new plotWidget(TYPE_X_DIST, distVals[i]);
		addWidget(widget, i, 0);
		m_distPlots.append(widget);
	}

	for(int i=0; i < timeVals.size(); i++) {
		widget = new plotWidget(TYPE_X_TIME, timeVals[i]);
		addWidget(widget, i, 1);
		m_timePlots.append(widget);
	}

	for(int i=0; i < trackPointVals.size(); i++) {
		widget = new plotWidget(TYPE_X_POINTS, trackPointVals[i]);
		addWidget(widget, i, 3);
		m_trackPointPlots.append(widget);
	}

}
