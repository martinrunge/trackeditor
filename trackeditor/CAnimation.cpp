/*
 * CAnimation.cpp
 *
 *  Created on: 14 Jul 2009
 *      Author: martin
 */

#include <QDebug>

#include "CAnimation.h"

#include "TrackCollection.h"



CAnimation::CAnimation(QObject *parent) : QObject(parent),
										  m_time_scale(1.0),
										  m_updates_per_second(10),
										  m_tc(0)
{
	// TODO Auto-generated constructor stub

	connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));

	m_status_bar_widget = new QLabel("Animation");
}

CAnimation::~CAnimation()
{
	// TODO Auto-generated destructor stub
	delete m_status_bar_widget;
}

void CAnimation::setTrackCollection(TrackCollection* tc)
{
	m_tc = tc;
}


double CAnimation::getTimeScale()
{
	return m_time_scale;
}

void CAnimation::setTimeScale(double ts)
{
	m_time_scale = ts;
	qDebug() << QString("stetting time scale to %1").arg(ts);

	m_time_scale_text = QString("%1 x").arg(m_time_scale);
	setStatusBarText();
}



void CAnimation::start()
{
	qDebug() << QString("starting animation");
	m_trackList = m_tc->getSelectedTracks();
	m_track_indices.clear();


	m_duration = 0;

	for(int i = 0; i < m_trackList.size(); i++)
	{
		m_track_indices.append(0);
		if(m_trackList.at(i)->duration() > m_duration )
		{
			m_duration = m_trackList.at(i)->duration();
		}
	}

	m_update_nr = 0;
	m_anim_time = 0.0;
	m_timer.start( 1000 / m_updates_per_second );

	m_state_text = "Animation running ";
	setStatusBarText();
}

void CAnimation::stop()
{
	qDebug() << QString("stoping animation");
	m_timer.stop();

	m_state_text = "";
	setStatusBarText();
}


void CAnimation::update()
{
	QList<CMarker> markers;
	bool animationFinished = true;

	double anim_time = m_update_nr * m_time_scale / m_updates_per_second;
	m_anim_time += m_time_scale / m_updates_per_second;
	for(int i = 0; i < m_trackList.size(); i++)
	{
		Track* track = m_trackList.at(i);
		TrackPoint* tp;
		int j;
		for(j = m_track_indices.at(i); j < track->size(); j++)
		{
			tp = track->at(j);
			animationFinished = false;
			if(tp == 0)
			{
				int size = track->size();
				qDebug() << QString("track->size(): %1").arg(size);
			}
			if(tp->getTimeDiff() >= m_anim_time )
			{
				break;
			}
		}
		m_track_indices[i] = j;


		CMarker m(tp->getX(), tp->getY(), track->getColor());

		markers.append(m);

	}
	emit setMarkers(markers);


	if(animationFinished)
	{
		stop();
	}

	m_update_nr++;
}


QWidget* CAnimation::statusBarWidget()
{
	return m_status_bar_widget;
}

void CAnimation::setStatusBarText()
{
	QString text = QString("%1 %2 %3").arg(m_state_text).arg(m_time_scale_text).arg(m_progess_text);
	m_status_bar_widget->setText(text);
}


