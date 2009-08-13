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
										  m_tc(0)
{
	// TODO Auto-generated constructor stub

}

CAnimation::~CAnimation()
{
	// TODO Auto-generated destructor stub
}

void CAnimation::setTrackCollection(TrackCollection* tc)
{
	m_tc = tc;
}


double CAnimation::getTimeScale()
{

}

void CAnimation::setTimeScale(double ts)
{
	m_time_scale = ts;
	qDebug() << QString("stetting time scale to %1").arg(ts);

}


void CAnimation::start()
{
	qDebug() << QString("starting animation");
}

void CAnimation::stop()
{
	qDebug() << QString("stoping animation");
}
