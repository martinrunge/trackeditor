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

class CScrolledTrackView;

class TrackCollection;
class QFrame;
class QPixmap;
class QLabel;

class TrackView : public QWidget {
	Q_OBJECT

public slots:
	void zoomValueChanged(int value);

	void increaseZoomValue(int delta);
	inline void zoomIn() { increaseZoomValue(1); };
	inline void zoomOut() { increaseZoomValue(-1); };


	void setMarkers(QList<CMarker> markers);

	QWidget* statusBarWidget();

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

//	void mousePressEvent(QMouseEvent *event);
//	void mouseMoveEvent(QMouseEvent *event);

	void wheelEvent(QWheelEvent *event);

protected slots:
	void closeEvent(QCloseEvent *event);


private:
	TrackCollection* m_track_collection;
	CScrolledTrackView* m_scroll_area;
	QFrame *m_frame;

	void recalculateOffset();
	QPointF widgetToViweport(QPointF point);
	QPoint  widgetToViweport(QPoint point);

	QPointF viewportToWidget(QPointF point);
	QPoint viewportToWidget(QPoint point);

	QPoint m_start_move;

	int m_start_horizontal_slider;
	int m_start_vertical_slider;

	void refreshPixmap();
	void drawMarkers(QPainter *painter);

	QPixmap *m_pixmap;

	QRect m_rect;
	int m_zoom_value;


	double m_x_offset;
	double m_y_offset;
	double m_scale;

	QList<CMarker> m_markers;

	QLabel *m_status_bar_widget;
	QString m_zoom_text;

	void setStatusBarText();
	void restoreLayout();
};

#endif /* TRACKVIEW_H_ */
