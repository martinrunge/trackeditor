/*
 * CScrolledTrackView.h
 *
 *  Created on: 15 Sep 2009
 *      Author: martin
 */

#ifndef CSCROLLEDTRACKVIEW_H_
#define CSCROLLEDTRACKVIEW_H_

#include <QScrollArea>

class QMouseEvent;
class QWheelEvent;

class CScrolledTrackView : public QScrollArea
{
	Q_OBJECT;

public:
	CScrolledTrackView(QWidget *parent = 0);
	virtual ~CScrolledTrackView();

	void scrollTo(QPoint widgetPos, QPoint screenPos );


protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	QPoint m_start_move;

	int m_start_horizontal_slider;
	int m_start_vertical_slider;

};

#endif /* CSCROLLEDTRACKVIEW_H_ */
