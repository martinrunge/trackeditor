/*
 * plotWidget.cpp
 *
 *  Created on: 16.11.2008
 *      Author: martin
 */


#include "PlotData.h"
#include "plotWidget.h"
#include "Track.h"

#include <qwt-qt4/qwt_plot_marker.h>
#include <qwt-qt4/qwt_plot_picker.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>

#include <QDebug>



plotWidget::plotWidget(enum plotTypeX x_type, enum plotTypeY y_type, QWidget * parent) : QwtPlot(parent)
{

	m_x_type = x_type;
	m_y_type = y_type;

    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
    m_grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    m_grid->attach(this);

    m_picker = new QwtPlotPicker(QwtPlot::xBottom , QwtPlot::yLeft,
				                 QwtPicker::PointSelection,
				                 QwtPlotPicker::VLineRubberBand,
				                 QwtPicker::AlwaysOn,
				                 canvas());

    connect(m_picker, SIGNAL(moved(QwtDoublePoint)), this, SLOT(pickerMoved(QwtDoublePoint)));


    m_curve_list.clear();

    QString x_label = PlotData::XTypeName[m_x_type];
    // x_label.append(PlotData::XUnitName[m_x_unit]);

    QString y_label = PlotData::YTypeName[m_y_type];
    // x_label.append(PlotData::XUnitName[m_y_unit]);

    setAxisTitle(QwtPlot::xBottom, x_label);
    setAxisTitle(QwtPlot::yLeft, y_label);
    // setAxisTitle(QwtPlot::yRight, "Speed [m/s]");

	setAutoReplot(true);

}

plotWidget::~plotWidget() {
	delete m_picker;
	delete m_grid;

}


void plotWidget::setTracks(QList<Track*> tracks) {

	QList<Track*>::iterator it;
	QList<QwtPlotCurve*>::iterator cplit;

	int n_tracks = tracks.size();
	int n_curves = m_curve_list.size();


	int diff = n_tracks - n_curves;

	qDebug() << QString("setTracks: n_tracks=%1 n_curves=%2").arg(n_tracks).arg(n_curves);
	// if diff is > 0, there are more tracks than curves -> add curves
	if(diff > 0) {
		for(int i=0; i < abs(diff); i++ ) {
			QwtPlotCurve* cplot = new QwtPlotCurve();
			// cplot->attach(this);
			m_curve_list.append(cplot);
		}
	}
	else {
		// if diff is < 0, there are less tracks than curves -> remove curves
		for(int i=0; i < abs(diff); i++ ) {
			QwtPlotCurve* last = m_curve_list.takeLast();
			last->detach();
			delete last;
		}
	}

	// now, there is exactly one curve per track

    for(int i = 0; i < n_tracks; i++) {
    	m_curve_list[i]->attach(this);
    	m_curve_list[i]->setPen(QPen(tracks[i]->getColor()));

    	// PlotData* data = new PlotData(tracks[i], m_x_type, m_y_type, 1000);
    	PlotData* data;
    	switch(m_x_type) {
			case TYPE_X_DIST:
				data = tracks[i]->getDistData(m_y_type);
				tracks[i]->dumpDistData();
				break;
			case TYPE_X_TIME:
				data = tracks[i]->getTimeData(m_y_type);
				tracks[i]->dumpTimeData();
				break;
			case TYPE_X_POINTS:
				data = tracks[i]->getTrackpointsData(m_y_type);
				tracks[i]->dumpTrackPointData();
				break;
			default:
				break;
    	}
		m_curve_list[i]->setData(*data);
    }

	m_track_list = tracks;

	//m_curve_list;
}

void plotWidget::pickerMoved(const QwtDoublePoint &pos) {
	// QPoint pt = m_picker->transform(pos);
	qDebug() << QString("pickermoved: %1 %2 ").arg(pos.x()).arg(pos.y());

	QList<CMarker> markers;
	for(int i = 0; i < m_track_list.size(); i++)
	{
		// get transformed coordinates from each track
		// in e.g. time and elevation
		// out -> geo coordinates in selected projection
		int index = m_track_list.at(i)->getIndexFromXVal(pos.x(), m_x_type);
		TrackPoint* tp = m_track_list.at(i)->at(index);


		CMarker marker(tp->getX(),tp->getX(),m_track_list.at(i)->getColor());
		markers.append(marker);

	}
	emit drawMarkers(markers);

}

