/*
 * plotWidget.h
 *
 *  Created on: 16.11.2008
 *      Author: martin
 */

#ifndef PLOTWIDGET_H_
#define PLOTWIDGET_H_

#include <qwt-qt4/qwt_plot.h>

class QwtPlotGrid;
class QwtPlotCurve;
class PlotData;
class Track;

class plotWidget : public QwtPlot {
	Q_OBJECT
public:
	plotWidget(QWidget * parent);
	virtual ~plotWidget();

	void setTrack(Track* track);

private:
	QwtPlotGrid *m_grid;
	//QwtPlot * m_qwtPlot;

	QwtPlotCurve* m_alt_crv;
	QwtPlotCurve* m_speed_crv;

	PlotData* m_alt_data;
	PlotData* m_speed_data;
};

#endif /* PLOTWIDGET_H_ */
