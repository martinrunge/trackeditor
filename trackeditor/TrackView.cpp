/*
 * TrackView.cpp
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */

#include "TrackView.h"
#include "CScrolledTrackView.h"

#include <QPainter>
#include <QRegion>
#include <QPaintEvent>
#include <QTime>
#include <QDebug>
#include <QVector>
#include <QFrame>
#include <QLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QPoint>
#include <QLabel>
#include <QSettings>

#include "TrackCollection.h"
#include "Track.h"
#include "TrackPoint.h"

TrackView::TrackView(QWidget* parent) : QWidget(parent), m_track_collection(0), m_pixmap(0) {

	m_scroll_area = reinterpret_cast<CScrolledTrackView*>(parent);

	setAttribute(Qt::WA_PaintOnScreen);

	m_zoom_value = 1;

	m_status_bar_widget = new QLabel();
	setStatusBarText();

	recalculateOffset();
	refreshPixmap();

	restoreLayout();
}

TrackView::~TrackView() {

}

void TrackView::increaseZoomValue(int delta)
{

	int zoom_val = m_zoom_value + delta;
	if(zoom_val < 1) zoom_val = 1;

	zoomValueChanged( zoom_val );
}


void TrackView::zoomValueChanged(int value) {
	m_zoom_value = value;

	recalculateOffset();
	QRectF dimension = m_track_collection->getDimensionXY();

    double dh = dimension.height();
    double dw = dimension.width();
//
//    QSize viewportSize = m_scroll_area->viewport()->size();
//
//	double w = (double)viewportSize.width();
//	double h = (double)viewportSize.height();
//
//
//    double x_scale = (w / dw) * m_zoom_value;
//    double y_scale = (h / dh) * m_zoom_value;
//
//    double scale = (x_scale < y_scale) ? x_scale : y_scale;

	setMinimumSize(dw * m_scale, dh * m_scale);


	refreshPixmap();

	m_zoom_text = QString("zoom %1").arg(m_zoom_value);
	setStatusBarText();

	update();

}

void TrackView::setMarkers(QList<CMarker> markers)
{
	m_markers = markers;
	update();
}

QPointF TrackView::widgetToViweport(QPointF point)
{
   	double xval = (point.x() - m_x_offset) * m_scale;  // + x();
   	double yval = (point.y() - m_y_offset) * m_scale;  // - y();

    return QPointF(xval,yval);
}

QPoint TrackView::widgetToViweport(QPoint point)
{
   	int xval = (point.x() - m_x_offset) * m_scale;  // + x();
   	int yval = (point.y() - m_y_offset) * m_scale;  // - y();

    return QPoint(xval,yval);
}

QPointF TrackView::viewportToWidget(QPointF point)
{
   	double xval = (point.x() / m_scale ) + m_x_offset;
   	double yval = (point.y() / m_scale ) + m_y_offset;

    return QPointF(xval,yval);
}




QPoint TrackView::viewportToWidget(QPoint point)
{
	double one_over_scale = 1 / m_scale;

   	int xval = ( one_over_scale * point.x() ) + m_x_offset;
   	int yval = ( one_over_scale * point.y() ) + m_y_offset;

    return QPoint(xval,yval);
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

//    double x_off = dimension.left();
//    double y_off = dimension.bottom();


//    double x_scale = (w / dw);
//    double y_scale = (h / dh);

//    double scale = (x_scale < y_scale) ? x_scale : y_scale;


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
           	double xval = (tr_ptr->at(tp_idx)->getX() - m_x_offset) * m_scale + x();
         	double yval = (tr_ptr->at(tp_idx)->getY() - m_y_offset) * m_scale - y();

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
	// qDebug() << QString("paintEvent : %1 %2 %3 %4   pos in parent: (%5, %6)  zoom value: %7").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).arg(x()).arg(y()).arg(m_zoom_value);

	if(m_rect != r)
	{
		m_rect = r;
		refreshPixmap();
	}
	//refreshPixmap();

	QPainter painter(this);

	if(m_pixmap)
	{
		painter.setClipRegion(QRegion(-x(), -y(), width, height) );

		painter.drawPixmap(-x(), -y(), *m_pixmap);
	}
    painter.scale(1, -1);          // , 15 * 1.0 / width(), 50 * 1.0 / height());
    painter.translate(0, 0); //-height());  // -11.5, -48.05);

	drawMarkers(&painter);
}

TrackCollection* TrackView::getTrackCollection() {
	return m_track_collection;
}

void TrackView::setTrackColletcion(TrackCollection* tc) {
	m_track_collection = tc;
	recalculateOffset();
	refreshPixmap();
	update();
}

void TrackView::drawMarkers(QPainter *painter)
{
	for(int i = 0; i < m_markers.size(); i++)
	{
		CMarker mark = m_markers.at(i);
		painter->setPen(mark.color());
		QPointF screenCoord = widgetToViweport(QPointF(mark.x(), mark.y()));
		painter->drawEllipse(screenCoord, 10, 10 );
		//qDebug() << QString("TrackView::drawMarkers: (%1,%2)").arg(mark.x()).arg(mark.y());
	}
}

void TrackView::resizeEvent( QResizeEvent * event )
{
	recalculateOffset();
	QWidget::resizeEvent(event);
}

void TrackView::moveEvent( QMoveEvent * event )
{
	recalculateOffset();
	QWidget::moveEvent(event);
}

//void TrackView::mousePressEvent(QMouseEvent *event)
//{
//	if (event->button() == Qt::LeftButton)
//    {
//		m_start_move = event->pos();
//
//		m_start_horizontal_slider = m_scroll_area->horizontalScrollBar()->value();
//		m_start_vertical_slider = m_scroll_area->verticalScrollBar()->value();
//    }
//}
//
//void TrackView::mouseMoveEvent(QMouseEvent *event)
//{
//	QPoint pos = event->pos() - m_start_move;
//
//	qDebug() << QString("mouseMoveEvent pos(%1,%2)").arg(event->pos().x()).arg(event->pos().y());
//
//	m_scroll_area->horizontalScrollBar()->setValue(m_start_horizontal_slider - pos.x());
//	m_scroll_area->verticalScrollBar()->setValue( m_start_vertical_slider - pos.y());
//
//}


void TrackView::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if (event->orientation() == Qt::Vertical) {


    	QPoint globalPos = event->globalPos();
    	QPoint oldWidgetPos = mapFromGlobal(globalPos);

    	QPoint mapPos = viewportToWidget(oldWidgetPos);

    	// resize widget
        increaseZoomValue(numSteps);

    	QPoint newWidgetPos = widgetToViweport(mapPos);


    	m_scroll_area->scrollTo(newWidgetPos, globalPos);

        qDebug() << QString("ScrollEvent at (%1,%2)").arg(event->x()).arg(event->y());
        event->accept();
    }
    else
    {
        event->ignore();
    }

}


void TrackView::recalculateOffset()
{
	if(!m_track_collection)
	{
		return;
	}

    QRectF dimension = m_track_collection->getDimensionXY();

    double dh = dimension.height();
    double dw = dimension.width();

    double ratio = dw / dh;

    QSize viewportSize = m_scroll_area->viewport()->size();

	int width = viewportSize.width();
	int height = viewportSize.height();

	double w = (double)width * m_zoom_value;
    double h = (double)height * m_zoom_value;

    m_x_offset = dimension.left();
    m_y_offset = dimension.bottom();

    double x_scale = (w / dw);
    double y_scale = (h / dh);

    m_scale = (x_scale < y_scale) ? x_scale : y_scale;

}



QWidget* TrackView::statusBarWidget()
{
	return m_status_bar_widget;
}

void TrackView::setStatusBarText()
{
	m_status_bar_widget->setText(m_zoom_text);
}



// to be removed: old PaintEvent implementation


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

void TrackView::closeEvent(QCloseEvent *event)
{
	qDebug() << QString("TrackView::closeEvent");
    QSettings settings;
    settings.setValue("TrackView/geometry", saveGeometry());
    QWidget::closeEvent(event);
}

void TrackView::restoreLayout()
{
    QSettings settings;
    restoreGeometry(settings.value("TrackView/geometry").toByteArray());
}

