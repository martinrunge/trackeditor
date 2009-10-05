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
#include <QLabel>

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

	QWidget* statusBarWidget();

public slots:

	void start();
	void stop();
	void setTimeScale(double ts);
	inline void setTimeScaleX0125() { setTimeScale(0.125); };
	inline void setTimeScaleX025() { setTimeScale(0.25); };
	inline void setTimeScaleX05() { setTimeScale(0.5); };
	inline void setTimeScaleX1() { setTimeScale(1); };
	inline void setTimeScaleX2() { setTimeScale(2); };
	inline void setTimeScaleX4() { setTimeScale(4); };
	inline void setTimeScaleX8() { setTimeScale(8); };
	inline void setTimeScaleX16() { setTimeScale(16); };
	inline void setTimeScaleX32() { setTimeScale(32); };
	inline void setTimeScaleX64() { setTimeScale(64); };
	inline void setTimeScaleX128() { setTimeScale(128); };
	inline void setUpdatePerSecond(int update_per_sec) { m_updates_per_second = update_per_sec; };

	inline void incSpeed() { setTimeScale(m_time_scale * 2); };
	inline void decSpeed() { setTimeScale(m_time_scale * 0.5); };

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

	QLabel *m_status_bar_widget;
	QString m_time_scale_text;
	QString m_state_text;
	QString m_progess_text;

	void setStatusBarText();
};

#endif /* CANIMATION_H_ */

