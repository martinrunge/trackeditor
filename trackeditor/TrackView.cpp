/*
 * TrackView.cpp
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */

#include "TrackView.h"

#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QVector>
#include <QFrame>
#include <QLayout>

#include "TrackCollection.h"
#include "Track.h"
#include "TrackPoint.h"

TrackView::TrackView(QWidget* parent) : QWidget(parent) {
	// TODO Auto-generated constructor stub
	QVBoxLayout *layout = new QVBoxLayout;
	m_frame = new QFrame(this);
	m_frame->setFrameRect(QRect(0,0,40,40));
	layout->addWidget(m_frame);
	setLayout(layout);
	setMinimumSize(400,400);

}

TrackView::~TrackView() {
	// TODO Auto-generated destructor stub
}

QSize TrackView::sizeHint() {
	return QSize(1000,1000);
}

QSize TrackView::minimumSizeHint() {
	return QSize(500,700);
}


void TrackView::paintEvent( QPaintEvent * event ) {
	qDebug("paintEvent");

    double w = (double)width();
    double h = (double)height();

    if(m_track_collection == 0 || m_track_collection->size() == 0) {
    	return;
    }

    QPainter painter(this);
    //QRectF dimension = m_track_collection->getDimension();
    QRectF dimension = m_track_collection->getDimensionXY();

    double dh = dimension.top() - dimension.bottom();
    double dw = dimension.right() - dimension.left();

    double x_off = dimension.left();
    double y_off = dimension.bottom();


    double x_scale = w / dw;
    double y_scale = h / dh;

    // painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(1, -1);          // , 15 * 1.0 / width(), 50 * 1.0 / height());
    painter.translate(0, -height());  // -11.5, -48.05);


    painter.setPen(QColor(0,0,0));

    Track* tr_ptr;
    std::vector<int> mi = m_track_collection->getIndexList();
    for(int mi_idx = 0; mi_idx < mi.size(); mi_idx++ ) {
    	int tr_idx = mi.at(mi_idx);

        if(m_track_collection->at(tr_idx)->size() == 0) {
        	return;
        }
        tr_ptr = m_track_collection->at(tr_idx);
        for(int tp_idx = 0; tp_idx < m_track_collection->at(tr_idx)->size(); tp_idx++) {
//        	double x = (tr_ptr->at(tp_idx)->getLong() - x_off) * x_scale;
//        	double y = (tr_ptr->at(tp_idx)->getLat() - y_off) * y_scale;
           	double x = (tr_ptr->at(tp_idx)->getX() - x_off) * x_scale;
         	double y = (tr_ptr->at(tp_idx)->getY() - y_off) * y_scale;

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

