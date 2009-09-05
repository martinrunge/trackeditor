/*
 * TrackView.h
 *
 *  Created on: 03.08.2008
 *      Author: martin.runge@web.de
 */

#ifndef TRACKVIEW_H_
#define TRACKVIEW_H_

#include <QWidget>
#include <QList>
#include "CMarker.h"

class TrackCollection;
class QFrame;
class QScrollArea;
class QPixmap;

class TrackView : public QWidget {
	Q_OBJECT

public slots:
	void zoomValueChanged(int value);
	void setMarkers(QList<CMarker> markers);


public:
	TrackView(QWidget* parent = 0);
	virtual ~TrackView();

	TrackCollection* getTrackCollection();
	void setTrackColletcion(TrackCollection* tc);

	QSize sizeHint();
	QSize minimumSizeHint();

protected:
	void paintEvent( QPaintEvent * event );
	void paintEventold( QPaintEvent * event );
	void resizeEvent ( QResizeEvent * event );
	void moveEvent ( QMoveEvent * event );


private:
	TrackCollection* m_track_collection;
	QScrollArea* m_scroll_area;
	QFrame *m_frame;

	void recalculateOffset();
	QPointF toScreenCoord(QPointF point);
	QPointF fromScreenCoord(QPointF point);

	void refreshPixmap();
	void drawMarkers(QPainter *painter);

	QPixmap *m_pixmap;

	QRect m_rect;
	int m_zoom_value;


	double m_x_offset;
	double m_y_offset;
	double m_scale;

	QList<CMarker> m_markers;
};

#endif /* TRACKVIEW_H_ */
