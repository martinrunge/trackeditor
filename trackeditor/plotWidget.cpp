/*
 * plotWidget.cpp
 *
 *  Created on: 16.11.2008
 *      Author: martin
 */


#include "PlotData.h"
#include "plotWidget.h"

#include <qwt-qt4/qwt_plot_marker.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>


plotWidget::plotWidget(QWidget * parent) : QwtPlot(parent) , m_alt_data(0), m_speed_data(0){
    //m_qwtPlot = new QwtPlot(parent);
    //m_qwtPlot->setObjectName(QString::fromUtf8("m_qwtPlot"));
    //m_qwtPlot->setGeometry(QRect(20, 40, 511, 200));

    m_grid = new QwtPlotGrid;
    m_grid->enableXMin(true);
    m_grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
    m_grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    m_grid->attach(this);

    // curves
    m_alt_crv = new QwtPlotCurve("Altitude");
    //m_alt_crv->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_alt_crv->setPen(QPen(Qt::blue));
    m_alt_crv->setYAxis(QwtPlot::yLeft);
    m_alt_crv->attach(this);

    m_speed_crv = new QwtPlotCurve("Speed");
    //m_speed_crv->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_speed_crv->setPen(QPen(Qt::red));
    m_speed_crv->setYAxis(QwtPlot::yRight);
    m_speed_crv->attach(this);

}

plotWidget::~plotWidget() {
	delete m_grid;

	delete m_alt_crv;
	delete m_speed_crv;

	if( m_alt_data != 0) delete m_alt_data;
	if( m_speed_data != 0) delete m_speed_data;

}

void plotWidget::setTrack(Track* track)
{
	m_alt_data = new PlotData(track, TYPE_ALT, 1000);
	//m_speed_data = new PlotData(track, TYPE_ALT, 1000);

	m_alt_crv->setData(*m_alt_data);
	// m_alt_crv->setData(*m_speed_data);

	setAutoReplot(true);
}
