/*
 * CScrolledTrackView.cpp
 *
 *  Created on: 15 Sep 2009
 *      Author: martin
 */

#include "CScrolledTrackView.h"
#include "TrackView.h"

#include <QMouseEvent>
#include <QWheelEvent>

#include <QScrollBar>

#include <QDebug>

CScrolledTrackView::CScrolledTrackView(QWidget *parent) : QScrollArea(parent)
{

}

CScrolledTrackView::~CScrolledTrackView()
{

}


void CScrolledTrackView::scrollTo(QPoint widgetPos, QPoint globalPos)
{
	TrackView* tv = reinterpret_cast<TrackView*>(widget());

	int x_scroll_range = tv->width() - viewport()->width();
	int y_scroll_range = tv->height() - viewport()->height();

	if(x_scroll_range < 0) x_scroll_range = 0;
	if(y_scroll_range < 0) y_scroll_range = 0;

	QPoint viewportPos = viewport()->mapFromGlobal(globalPos);

	QPoint diff = widgetPos - viewportPos;

	//qDebug() << QString("scrollTo: widgetPos (%1, %2)  viewportPos: (%3, %4))").arg(widgetPos.x()).arg(widgetPos.y()).arg(viewportPos.x()).arg(viewportPos.y());
	qDebug() << QString("scrollTo: diff (%1, %2)").arg(diff.x()).arg(diff.y());

	horizontalScrollBar()->setValue(diff.x());
	verticalScrollBar()->setValue(diff.y());

}



void CScrolledTrackView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
    {
		m_start_move = mapFromGlobal(event->globalPos());

		m_start_horizontal_slider = horizontalScrollBar()->value();
		m_start_vertical_slider = verticalScrollBar()->value();
    }
}

void CScrolledTrackView::mouseMoveEvent(QMouseEvent *event)
{
	QPoint pos = mapFromGlobal(event->globalPos()) - m_start_move;

	qDebug() << QString("mouseMoveEvent pos(%1,%2)").arg(event->pos().x()).arg(event->pos().y());

	horizontalScrollBar()->setValue(m_start_horizontal_slider - pos.x());
	verticalScrollBar()->setValue( m_start_vertical_slider - pos.y());

}

void CScrolledTrackView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
		case Qt::Key_Left:
			scrollRelativeHorizontal(-5);
			break;
		case Qt::Key_Right:
			scrollRelativeHorizontal(5);
			break;
		case Qt::Key_Down:
			scrollRelativeVertical(5);
			break;
		case Qt::Key_Up:
			scrollRelativeVertical(-5);
			break;
		default:
			QScrollArea::keyPressEvent(event);
    }
}

void CScrolledTrackView::scrollRelativeHorizontal(int percent)
{
	int pos = horizontalScrollBar()->value();
	int range = horizontalScrollBar()->maximum() - horizontalScrollBar()->minimum();
	int diff = range * percent;
	diff /= 100;

	horizontalScrollBar()->setValue(pos + diff);
}

void CScrolledTrackView::scrollRelativeVertical(int percent)
{
	int pos = verticalScrollBar()->value();
	int range = verticalScrollBar()->maximum() - verticalScrollBar()->minimum();
	int diff = range * percent;
	diff /= 100;

	verticalScrollBar()->setValue(pos + diff);
}


