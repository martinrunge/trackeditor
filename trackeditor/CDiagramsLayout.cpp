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
	delete m_plotWidget;
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

	for(it = m_timePlots.begin(); it != m_timePlots.end(); it++) {
		if(*it) {
			removeWidget(*it);
			delete *it;
		}
	}

	for(it = m_trackPointPlots.begin(); it != m_trackPointPlots.end(); it++) {
		if(*it) {
			removeWidget(*it);
			delete *it;
		}
	}

}

void CDiagramsLayout::setQuantities(QStringList distVals, QStringList timeVals, QStringList trackPointVals) {

	clear();

	plotWidget* widget;
	for(int i=0; i < distVals.size(); i++) {
		widget = new plotWidget();
		addWidget(widget, i, 0);
		m_distPlots.append(widget);
	}

	for(int i=0; i < timeVals.size(); i++) {
		widget = new plotWidget();
		addWidget(widget, i, 1);
		m_distPlots.append(widget);
	}

	for(int i=0; i < trackPointVals.size(); i++) {
		widget = new plotWidget();
		addWidget(widget, i, 3);
		m_distPlots.append(widget);
	}

}
