/*
 * CommonTrackAttributes.h
 *
 *  Created on: 18.08.2008
 *      Author: martin
 */

#ifndef COMMONTRACKATTRIBUTES_H_
#define COMMONTRACKATTRIBUTES_H_

#include <QString>

class CommonTrackAttributes {
public:
	CommonTrackAttributes();
	virtual ~CommonTrackAttributes();

	void setType(QString type);
	QString getType(void);
	bool validType();

	void setComment(QString comment);
	QString getComment(void);
	bool validComment();

	void setDataSource(QString source);
	QString getDataSource(void);
	bool validDataSource();

protected:
	void initMetaData();

	// <cmt> xsd:string </cmt> [0..1]
	QString m_comment;

	// <src> xsd:string </src> [0..1]
	QString m_data_src;

	// <type> xsd:string </type> [0..1] ?
	QString m_type;




};

#endif /* COMMONTRACKATTRIBUTES_H_ */
