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
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>

#include <QDebug>



plotWidget::plotWidget(enum plotTypeX x_type, enum plotTypeY y_type, QWidget * parent) : QwtPlot(parent) {
    //m_qwtPlot = new QwtPlot(parent);
    //m_qwtPlot->setObjectName(QString::fromUtf8("m_qwtPlot"));
    //m_qwtPlot->setGeometry(QRect(20, 40, 511, 200));

	m_x_type = x_type;
	m_y_type = y_type;

    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
    m_grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    m_grid->attach(this);

    // curves
    // m_alt_crv = new QwtPlotCurve("Altitude");
    //m_alt_crv->setRenderHint(QwtPlotItem::RenderAntialiased);
    // m_alt_crv->setPen(QPen(Qt::blue));
    // m_alt_crv->setYAxis(QwtPlot::yLeft);
    // m_alt_crv->attach(this);

    // m_speed_crv = new QwtPlotCurve("Speed");
    // m_speed_crv->setRenderHint(QwtPlotItem::RenderAntialiased);
    // m_speed_crv->setPen(QPen(Qt::red));
    // m_speed_crv->setYAxis(QwtPlot::yRight);
    // m_speed_crv->attach(this);

    // enableAxis(QwtPlot::yRight);

	// m_curve_list = new QList<QwtPlotCurve*>;

    m_curve_list.clear();

    QString x_label = PlotData::XTypeName[m_x_type];
    // x_label.append(PlotData::XUnitName[m_x_unit]);

    QString y_label = PlotData::YTypeName[m_y_type];
    // x_label.append(PlotData::XUnitName[m_y_unit]);

    setAxisTitle(QwtPlot::xBottom, x_label);
    setAxisTitle(QwtPlot::yLeft, y_label);
    // setAxisTitle(QwtPlot::yRight, "Speed [m/s]");

}

plotWidget::~plotWidget() {
	delete m_grid;

	// delete m_alt_crv;
	// delete m_speed_crv;

	// delete m_curve_list;

	// if( m_alt_data != 0) delete m_alt_data;
	// if( m_speed_data != 0) delete m_speed_data;

}

//void plotWidget::setTrack(Track* track)
//{
//	m_alt_data = new PlotData(track, TYPE_X_DIST, TYPE_Y_ALT, 1000);
//	m_speed_data = new PlotData(track, TYPE_X_DIST, TYPE_Y_SPEED, 1000);
//
//	m_alt_crv->setPen(QPen(track->getColor()));
//	m_alt_crv->setData(*m_alt_data);
//	// m_alt_crv->setData(*m_speed_data);
//	m_speed_crv->setPen(QPen(track->getColor()));
//	m_speed_crv->setData(*m_speed_data);
//
//	setAutoReplot(true);
//}

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
				break;
			case TYPE_X_TIME:
				data = tracks[i]->getTimeData(m_y_type);
				break;
			case TYPE_X_POINTS:
				data = tracks[i]->getTrackpointsData(m_y_type);
				break;
			default:
				break;
    	}
		m_curve_list[i]->setData(*data);
    }

	m_track_list = tracks;
	setAutoReplot(true);

	//m_curve_list;
}
