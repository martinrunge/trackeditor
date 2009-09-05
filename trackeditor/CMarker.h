/*
 * CMarker.h
 *
 *  Created on: 28 Aug 2009
 *      Author: martin
 */

#ifndef CMARKER_H_
#define CMARKER_H_

#include <QColor>

class CMarker
{
public:
	CMarker(double x, double y, QColor color);
	virtual ~CMarker();

	inline QColor color() { return m_color; };
	inline double x() { return m_x; };
	inline double y() { return m_y; };

private:
	double m_x;
	double m_y;

	QColor m_color;

};

#endif /* CMARKER_H_ */
