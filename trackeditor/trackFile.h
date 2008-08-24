/*
 * trackFile.h
 *
 *  Created on: 15.08.2008
 *      Author: martin
 */

#ifndef TRACKFILE_H_
#define TRACKFILE_H_

#include <QString>

class TrackCollection;

class trackFile {
public:
	trackFile();
	virtual ~trackFile();

	virtual TrackCollection* read(QString filename) = 0;
	virtual void write(TrackCollection* tc,  QString filename) = 0;

};

#endif /* TRACKFILE_H_ */
