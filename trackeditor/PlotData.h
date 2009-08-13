/*
 * PlotData.h
 *
 *  Created on: 17.11.2008
 *      Author: martin
 */

#ifndef PLOTDATA_H_
#define PLOTDATA_H_

#include <qwt-qt4/qwt_data.h>
#include <QMap>
#include <QDateTime>

// #include "Track.h"

enum plotTypeX {
	TYPE_X_DIST,
	TYPE_X_TIME,
	TYPE_X_POINTS,
	TYPE_X_NONE
};

enum plotTypeY {
	TYPE_Y_ALT,
	TYPE_Y_SPEED,
	TYPE_Y_DGPS_DIFF,
	TYPE_Y_HDOP,
	TYPE_Y_VDOP,
	TYPE_Y_PDOP,
	TYPE_Y_NONE
};

class Track;
class TrackPoint;

class PlotData : public QwtData {
public:
	PlotData(Track* track, enum plotTypeX xtype, enum plotTypeY ytype, int numPoints);
	PlotData(double *x_vals, double *y_vals, int size);
	virtual ~PlotData();

	virtual QwtData *copy() const;
    virtual size_t size() const;
    virtual double x(size_t i) const;
    virtual double y(size_t i) const;

    int index(size_t i) const;

    static QMap<enum plotTypeY, QString> YTypeName;
    static QMap<enum plotTypeX, QString> XTypeName;
    static QMap<QString, enum plotTypeY> YTypeNamesForSettings;
    static void initializeMaps();

private:

	double getXVal(TrackPoint* tp);
	double getYVal(TrackPoint* tp);

	enum plotTypeX m_plot_type_x;
	enum plotTypeY m_plot_type_y;

	QDateTime  m_start_time;

    size_t m_size;
    int m_num_points;

    double *m_x_values;
    double *m_y_values;

    int    *m_index_in_track;


    Track* m_track;
    long m_tp_index;

    bool m_copied;

};

#endif /* PLOTDATA_H_ */
