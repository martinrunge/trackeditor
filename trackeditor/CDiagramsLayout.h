/*
 * CDiagramsLayout.h
 *
 *  Created on: 26.01.2009
 *      Author: martin
 */

#ifndef CDIAGRAMSLAYOUT_H_
#define CDIAGRAMSLAYOUT_H_

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QString>

#include "PlotData.h"
#include "CMarker.h"

class plotWidget;
class Track;

class CDiagramsLayout: public QGridLayout {
	Q_OBJECT;
public:
	CDiagramsLayout(QWidget * parent = 0);
	virtual ~CDiagramsLayout();

	// void setTrack(Track* track);
	void setTracks(QList<Track*> track);

	void setQuantities(QStringList distVals, QStringList timeVals, QStringList trackPointVals );
	void setQuantities(QList<enum plotTypeY> distVals, QList<enum plotTypeY> timeVals, QList<enum plotTypeY> trackPointVals );

public slots:
	void drawMarkers(QList<CMarker> markers);

signals:
	void drawMarkers(QList<CMarker> markers);



private:
	void clear();
	// plotWidget *m_plotWidget;
	QList<plotWidget*> m_distPlots;
	QList<plotWidget*> m_timePlots;
	QList<plotWidget*> m_trackPointPlots;

};

#endif /* CDIAGRAMSLAYOUT_H_ */
