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


class TrackCollection;


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

signals:


private:
	double m_time_scale;

	TrackCollection* m_tc;

	QTimer m_timer;

};

#endif /* CANIMATION_H_ */
