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

class plotWidget;
class Track;

class CDiagramsLayout: public QGridLayout {
	Q_OBJECT;
public:
	CDiagramsLayout(QWidget * parent = 0);
	virtual ~CDiagramsLayout();

	void setTrack(Track* track);
	void setTracks(QList<Track*> track);

	void setQuantities(QStringList distVals, QStringList timeVals, QStringList trackPointVals );

private:
	void clear();
	plotWidget *m_plotWidget;
	QList<plotWidget*> m_distPlots;
	QList<plotWidget*> m_timePlots;
	QList<plotWidget*> m_trackPointPlots;

};

#endif /* CDIAGRAMSLAYOUT_H_ */
