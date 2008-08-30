/*
 * Track.h
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */

#ifndef TRACK_H_
#define TRACK_H_

#include "TrackPoint.h"
#include "CommonAttributes.h"
#include "CommonTrackAttributes.h"

#include <QList>
#include <QDateTime>
#include <QStandardItem>

class Track :public QList<TrackPoint*> , public QStandardItem, public CommonAttributes, public CommonTrackAttributes {
public:
	Track();
	virtual ~Track();

	double getMinLat();
	double getMaxLat();
	double getMinLong();
	double getMaxLong();

	QDateTime getTrackBegin();
	QDateTime getTrackEnd();

	void setIndex(int index);
	int getIndex();
	bool validIndex(void);

	void dataChanged(int column);
	QList<QStandardItem*> getItemList();

	void commit();

private:
	void initMetaData();

	double m_min_lat, m_max_lat, m_min_lng, m_max_lng;

	QDateTime m_min_time, m_max_time;

	QList<QStandardItem*> m_itemlist;

	QStandardItem* m_index_item;
	QStandardItem* m_start_time_item;
	QStandardItem* m_end_time_item;
	QStandardItem* m_name_item;
	QStandardItem* m_num_points_item;



	// <number> xsd:nonNegativeInteger </number> [0..1] ?
	int m_track_index;

};

#endif /* TRACK_H_ */
