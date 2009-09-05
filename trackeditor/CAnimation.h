/*
 * CAnimation.h
 *
 *  Created on: 14 Jul 2009
 *      Author: martin
 */

#ifndef CANIMATION_H_
#define CANIMATION_H_

#include <QObject>
#include <QTimer>
#include <QList>

#include "CMarker.h"

class TrackCollection;
class Track;


class CAnimation : public QObject
{
	Q_OBJECT;
public:
	CAnimation(QObject* parent = 0);
	virtual ~CAnimation();

	void setTrackCollection(TrackCollection* tc);

	double getTimeScale();

public slots:

	void start();
	void stop();
	void setTimeScale(double ts);
	void setUpdatePerSecond(int update_per_sec);

	void update();

signals:
	void setMarkers(QList<CMarker> markers);


private:
	double m_duration;
	double m_time_scale;

	int m_updates_per_second;
	int m_update_nr;

	TrackCollection* m_tc;

	QList<Track*> m_trackList;
	QList<int> m_track_indices;

	QTimer m_timer;

};

#endif /* CANIMATION_H_ */
