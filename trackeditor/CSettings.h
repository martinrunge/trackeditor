/*
 * CSettings.h
 *
 *  Created on: 14.02.2009
 *      Author: martin
 */

#ifndef CSETTINGS_H_
#define CSETTINGS_H_

#include <QSettings>
#include "PlotData.h"

class CSettings {
public:
	CSettings();
	virtual ~CSettings();

	void load();
	void save();

	QList<enum plotTypeY> getDistQuantities();
    void setDistQuantities(QList<enum plotTypeY> values);

	QList<enum plotTypeY> getTimeQuantities();
    void setTimeQuantities(QList<enum plotTypeY> values);

    QList<enum plotTypeY> getTrackpointsQuantities();
    void setTrackpointsQuantities(QList<enum plotTypeY> values);

private:
	QSettings m_settings;

	QList<enum plotTypeY> m_dist_quantities;
	QList<enum plotTypeY> m_time_quantities;
	QList<enum plotTypeY> m_trackpoints_quantities;

};

#endif /* CSETTINGS_H_ */
