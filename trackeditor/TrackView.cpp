/*
 * TrackView.cpp
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */

#include "TrackView.h"

#include <QPainter>
#include <QRegion>
#include <QPaintEvent>
#include <QTime>
#include <QDebug>
#include <QVector>
#include <QFrame>
#include <QLayout>
#include <QScrollArea>
#include <QPoint>

#include "TrackCollection.h"
#include "Track.h"
#include "TrackPoint.h"

TrackView::TrackView(QWidget* parent) : QWidget(parent), m_track_collection(0), m_pixmap(0) {

	m_scroll_area = reinterpret_cast<QScrollArea*>(parent);

	setAttribute(Qt::WA_PaintOnScreen);

	m_zoom_value = 1;
	refreshPixmap();

}

TrackView::~TrackView() {

}

void TrackView::zoomValueChanged(int value) {
	m_zoom_value = value;

    QRectF dimension = m_track_collection->getDimensionXY();

    double dh = dimension.height();
    double dw = dimension.width();

    QSize viewportSize = m_scroll_area->viewport()->size();

	double w = (double)viewportSize.width();
	double h = (double)viewportSize.height();


    double x_scale = (w / dw) * m_zoom_value;
    double y_scale = (h / dh) * m_zoom_value;

    double scale = (x_scale < y_scale) ? x_scale : y_scale;

	setMinimumSize(dw * scale, dh * scale);

	refreshPixmap();
	repaint();
}


QSize TrackView::sizeHint() {
	return QSize(1000,1000);
}

QSize TrackView::minimumSizeHint() {
	return QSize(500,700);
}

void TrackView::refreshPixmap() {

	if(m_track_collection == 0 || m_track_collection->size() == 0) {
    	return;
    }

	QSize viewportSize = m_scroll_area->viewport()->size();

	int width = viewportSize.width();
	int height = viewportSize.height();


	if(m_pixmap)
	{
		if( m_pixmap->width() != width || m_pixmap->height() != height )
		{
			delete m_pixmap;
			m_pixmap = new QPixmap(width, height);
		}
	}
	else
	{
		m_pixmap = new QPixmap(width, height);

	}
	m_pixmap->fill(Qt::transparent);
	//m_pixmap->fill(Qt::yellow);

	double w = (double)width * m_zoom_value;
    double h = (double)height * m_zoom_value;

    QRectF dimension = m_track_collection->getDimensionXY();

    double dh = dimension.height();
    double dw = dimension.width();

    double ratio = dw / dh;

    double x_off = dimension.left();
    double y_off = dimension.bottom();


    double x_scale = (w / dw);
    double y_scale = (h / dh);

    double scale = (x_scale < y_scale) ? x_scale : y_scale;


    QPainter painter(m_pixmap);

    // painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(1, -1);          // , 15 * 1.0 / width(), 50 * 1.0 / height());
    painter.translate(0, 0); //-height());  // -11.5, -48.05);

//    const QRegion region = event->region();
//    QSize fs=frameSize();
//    qDebug() << QString("FrameSize: %1 %2 ").arg(region.width()).arg(region.height());

    painter.setPen(QColor(0,0,0));

    Track* tr_ptr;
    std::vector<int> mi = m_track_collection->getIndexList();
    for(unsigned mi_idx = 0; mi_idx < mi.size(); mi_idx++ ) {
    	int tr_idx = mi.at(mi_idx);

    	if(m_track_collection->at(tr_idx)->size() == 0) {
        	return;
        }
        tr_ptr = m_track_collection->at(tr_idx);
    	painter.setPen(tr_ptr->getColor());

        for(int tp_idx = 0; tp_idx < m_track_collection->at(tr_idx)->size(); tp_idx++) {
//        	double x = (tr_ptr->at(tp_idx)->getLong() - x_off) * x_scale;
//        	double y = (tr_ptr->at(tp_idx)->getLat() - y_off) * y_scale;
           	double xval = (tr_ptr->at(tp_idx)->getX() - x_off) * scale - x();
         	double yval = (tr_ptr->at(tp_idx)->getY() - y_off) * scale - y();

        	painter.drawPoint(QPointF(xval,yval));

        }
    }

    //painter.drawLine(0 ,-2 ,width - 1, -2);
    //painter.drawLine(2 ,0 ,2, - height + 1);
    //painter.drawLine(0 ,-height + 3 ,width - 1, - height + 3);
    //painter.drawLine(width - 3 ,0 ,width - 3, - height + 1);

    //QRectF rectangle(0.0, 0.0, width - 1, -height + 1);

    //painter.drawEllipse(rectangle);

}

void TrackView::paintEvent( QPaintEvent * event ) {

	QSize viewportSize = m_scroll_area->viewport()->size();

	int width = viewportSize.width();
	int height = viewportSize.height();

	QRect r = QRect(-x(), -y(), width, height); //event->rect();
	qDebug() << QString("paintEvent : %1 %2 %3 %4   pos in parent: (%5, %6)  zoom value: %7").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).arg(x()).arg(y()).arg(m_zoom_value);

	if(m_rect != r)
	{
		m_rect = r;
		refreshPixmap();
	}
	//refreshPixmap();

	if(m_pixmap)
	{
		QPainter painter(this);
		painter.setClipRegion(QRegion(-x(), -y(), width, height) );

		painter.drawPixmap(-x(), -y(), *m_pixmap);
	}
}

void TrackView::paintEventold( QPaintEvent * event ) {
	qDebug("paintEvent");

//	setMinimumSize(0, 0);

	QSize viewportSize = m_scroll_area->viewport()->size();
	double w = (double)viewportSize.width();
    double h = (double)viewportSize.height();

    if(m_track_collection == 0 || m_track_collection->size() == 0) {
    	return;
    }

    QPainter painter(this);
    //QRectF dimension = m_track_collection->getDimension();
    QRectF dimension = m_track_collection->getDimensionXY();

    double dh = dimension.height();
    double dw = dimension.width();

    double ratio = dw / dh;

    double x_off = dimension.left();
    double y_off = dimension.bottom();


    double x_scale = (w / dw) * m_zoom_value;
    double y_scale = (h / dh) * m_zoom_value;

    double scale = (x_scale < y_scale) ? x_scale : y_scale;

	setMinimumSize(dw * scale, dh * scale);


    // painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(1, -1);          // , 15 * 1.0 / width(), 50 * 1.0 / height());
    painter.translate(0, 0); //-height());  // -11.5, -48.05);

//    const QRegion region = event->region();
//    QSize fs=frameSize();
//    qDebug() << QString("FrameSize: %1 %2 ").arg(region.width()).arg(region.height());

    painter.setPen(QColor(0,0,0));

    Track* tr_ptr;
    std::vector<int> mi = m_track_collection->getIndexList();
    for(unsigned mi_idx = 0; mi_idx < mi.size(); mi_idx++ ) {
    	int tr_idx = mi.at(mi_idx);

    	if(m_track_collection->at(tr_idx)->size() == 0) {
        	return;
        }
        tr_ptr = m_track_collection->at(tr_idx);
    	painter.setPen(tr_ptr->getColor());

        for(int tp_idx = 0; tp_idx < m_track_collection->at(tr_idx)->size(); tp_idx++) {
//        	double x = (tr_ptr->at(tp_idx)->getLong() - x_off) * x_scale;
//        	double y = (tr_ptr->at(tp_idx)->getLat() - y_off) * y_scale;
           	double x = (tr_ptr->at(tp_idx)->getX() - x_off) * scale;
         	double y = (tr_ptr->at(tp_idx)->getY() - y_off) * scale;

        	painter.drawPoint(QPointF(x,y));

        }
    }

}

TrackCollection* TrackView::getTrackCollection() {
	return m_track_collection;
}

void TrackView::setTrackColletcion(TrackCollection* tc) {
	m_track_collection = tc;
}

