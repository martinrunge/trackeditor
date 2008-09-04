/*
 * tk1File.cpp
 *
 *  Created on: 15.08.2008
 *      Author: martin
 */

#include <QDebug>

#include "tk1File.h"

tk1File::tk1File() {
	// TODO Auto-generated constructor stub

}

tk1File::~tk1File() {
	// TODO Auto-generated destructor stub
}

TrackCollection* tk1File::read(QString filename) {
	qDebug() << QString("tk1File::read( %1 )").arg(filename);
	return 0;
}

void tk1File::write(TrackCollection* tc,  QString filename) {
	qDebug() << QString("tk1File::write( %1 )").arg(filename);

}
