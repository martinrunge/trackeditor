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

class TrackView : public QWidget {

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
	QFrame *m_frame;
};

#endif /* TRACKVIEW_H_ */
