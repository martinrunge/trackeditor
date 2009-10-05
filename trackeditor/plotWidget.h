/*
 * plotWidget.h
 *
 *  Created on: 16.11.2008
 *      Author: martin
 */

#ifndef PLOTWIDGET_H_
#define PLOTWIDGET_H_

#include <qwt-qt4/qwt_plot.h>
#include "PlotData.h"
#include "CMarker.h"

class QwtPlotGrid;
class QwtPlotCurve;
class QwtPlotPicker;
class Track;

class plotWidget : public QwtPlot
{
	Q_OBJECT
public:
	plotWidget(enum plotTypeX x_type, enum plotTypeY y_type, QWidget * parent = 0);
	virtual ~plotWidget();

	// void setTrack(Track* track);
	void setTracks(QList<Track*> tracks);

public slots:
	void pickerMoved(const QwtDoublePoint &pos);

signals:
	void drawMarkers(QList<CMarker> markers);

private:
	QwtPlotGrid *m_grid;
	QwtPlotPicker *m_picker;

	QList<QwtPlotCurve*> m_curve_list;
	QList<Track*> m_track_list;

	enum plotTypeX m_x_type;
	enum plotTypeY m_y_type;


};

#endif /* PLOTWIDGET_H_ */
