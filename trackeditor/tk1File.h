/*
 * tk1File.h
 *
 *  Created on: 15.08.2008
 *      Author: martin
 */

#ifndef TK1FILE_H_
#define TK1FILE_H_

#include "trackFile.h"

class tk1File :public trackFile {
public:
	tk1File();
	virtual ~tk1File();

	TrackCollection* read(QString filename);
	void write(TrackCollection* tc,  QString filename);

};

#endif /* TK1FILE_H_ */
