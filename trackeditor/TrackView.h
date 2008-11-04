/*
 * TrackView.h
 *
 *  Created on: 03.08.2008
 *      Author: martin.runge@web.de
 */

#ifndef TRACKVIEW_H_
#define TRACKVIEW_H_

#include <QWidget>

class TrackCollection;
class QFrame;
class QScrollArea;

class TrackView : public QWidget {
	Q_OBJECT

public slots:
	void zoomValueChanged(int value);


public:
	TrackView(QWidget* parent = 0);
	virtual ~TrackView();

	TrackCollection* getTrackCollection();
	void setTrackColletcion(TrackCollection* tc);

	QSize sizeHint();
	QSize minimumSizeHint();

protected:
	void paintEvent( QPaintEvent * event );


private:
	TrackCollection* m_track_collection;
	QScrollArea* m_scroll_area;
	QFrame *m_frame;

	int m_zoom_value;
};

#endif /* TRACKVIEW_H_ */
