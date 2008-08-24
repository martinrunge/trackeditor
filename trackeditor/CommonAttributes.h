/*
 * CommonAttributes.h
 *
 *  Created on: 18.08.2008
 *      Author: martin
 */

#ifndef COMMONATTRIBUTES_H_
#define COMMONATTRIBUTES_H_

#include <QString>

class CommonAttributes {
public:
	CommonAttributes();
	virtual ~CommonAttributes();

	void setName(QString name);
	QString getName();
	bool validName();

	void setDescription(QString desc);
	QString getDescription();
	bool validDescription();


	void setLinkUrl(QString url);
	QString getLinkUrl();
	bool validLinkUrl();

	void setLinkMimeType(QString mime_type);
	QString getLinkMimeType();
	bool validLinkMimeType();

	void setLinkText(QString text);
	QString getLinkText();
	bool validLinkText();

protected:
	void initMetaData();

	// <name> xsd:string </name> [0..1] ?
	QString m_name;

	// <desc> xsd:string </desc> [0..1] ?
	QString m_description;

	// <link> linkType </link> [0..*] ?
	QString m_link_url;
	QString m_link_mimetype;
	QString m_link_text;

};

#endif /* COMMONATTRIBUTES_H_ */
