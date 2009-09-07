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
	inline void setTimeScaleX0125() {m_time_scale = 0.125; };
	inline void setTimeScaleX025() {m_time_scale = 0.25; };
	inline void setTimeScaleX05() {m_time_scale = 0.5; };
	inline void setTimeScaleX1() {m_time_scale = 1; };
	inline void setTimeScaleX2() {m_time_scale = 2; };
	inline void setTimeScaleX4() {m_time_scale = 4; };
	inline void setTimeScaleX8() {m_time_scale = 8; };
	inline void setTimeScaleX16() {m_time_scale = 16; };
	inline void setTimeScaleX32() {m_time_scale = 32; };
	inline void setUpdatePerSecond(int update_per_sec) { m_updates_per_second = update_per_sec; };

	void update();

signals:
	void setMarkers(QList<CMarker> markers);


private:
	double m_duration;
	double m_time_scale;

	double m_anim_time;

	int m_updates_per_second;
	int m_update_nr;

	TrackCollection* m_tc;

	QList<Track*> m_trackList;
	QList<int> m_track_indices;

	QTimer m_timer;

};

#endif /* CANIMATION_H_ */
