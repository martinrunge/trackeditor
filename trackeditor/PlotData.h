/*
 * PlotData.h
 *
 *  Created on: 17.11.2008
 *      Author: martin
 */

#ifndef PLOTDATA_H_
#define PLOTDATA_H_

#include <qwt-qt4/qwt_data.h>

#include "Track.h"

enum plotType {
	TYPE_ALT,
	TYPE_SPEED,
	TYPE_DGPS_DIFF,
	TYPE_HDOP,
	TYPE_PDOP,
	TYPE_NONE
};

class PlotData : public QwtData {
public:
	PlotData(Track* track, enum plotType type, int numPoints);
	PlotData(double *x_vals, double *y_vals, int size);
	virtual ~PlotData();

	virtual QwtData *copy() const;
    virtual size_t size() const;
    virtual double x(size_t i) const;
    virtual double y(size_t i) const;

private:
	enum plotType m_plot_type;

    size_t m_size;
    int m_num_points;

    double *m_x_values;
    double *m_y_values;


    Track* m_track;

    bool m_copied;
};

#endif /* PLOTDATA_H_ */
