/*
 * TrackCollection.h
 *
 *  Created on: 03.08.2008
 *      Author: martin
 */

#ifndef TRACKCOLLECTION_H_
#define TRACKCOLLECTION_H_

#include "Track.h"
#include "CommonAttributes.h"

#include <QList>
#include <QDateTime>
#include <QRectF>
#include <QStandardItemModel>
#include <QModelIndex>

#include <vector>

class TrackCollection : public QStandardItemModel, public QList<Track*>, public CommonAttributes{

	Q_OBJECT

public:
	TrackCollection();
	virtual ~TrackCollection();


	void appendTrack(Track* track);

	void commit();
	void clear();


	int getNumWaypoints();
	Track* getWaypoints();

	QRectF getDimension();
	QRectF getDimension(QModelIndexList indices);
	QRectF getCompleteDimension();
	bool validBounds();

	void setModelIndexList(QModelIndexList index_list);
	QModelIndexList getModelIndexList(void);

	std::vector<int> getIndexList(void);

	QString getCreator();

	bool validAuthor();

	void setAuthorName(QString author);
	QString getAuthorName();
	bool validAuthorName();

	void setAuthorEMail(QString email);
	QString getAuthorEMail();
	bool validAuthorEmail();

	void setAuthorLinkUrl(QString url);
	QString getAuthorLinkUrl();
	bool validAuthorLinkUrl();

	void setAuthorLinkMimeType(QString mime_type);
	QString getAuthorLinkMimeType();

	void setAuthorLinkText(QString text);
	QString getAuthorLinkText();

	void setCopyrightAuthor(QString author);
	QString getCopyrightAuthor();
	bool validCopyrightAuthor();


	void setCopyrightYear(unsigned year);
	unsigned getCopyrightYear();
	bool validCopyrightYear();

	void setCopyrightLicenseUrl(QString license_url);
	QString getCopyrightLicenseUrl();
	bool validCopyrightLicenseUrl();


	void setDateTime(QDateTime date_time);
	QDateTime getDateTime();
	bool validDateTime();

	void setKeywords(QString keywords);
	QString getKeywords();
	bool validKeywords();

public slots:
    void editFinished(const QModelIndex & topLeft, const QModelIndex & bottomRight);

private:
	Track* m_waypoints;

	QStandardItem *m_parentItem;

	QModelIndexList m_model_index_list;
	std::vector<int> m_index_list;

	// creator of output file. Read only.
	QString m_creator_description;


	// <author> personType </author> [0..1] ?
	QString m_author_name;
	QString m_author_email;

	QString m_author_link_url;
	QString m_author_link_mimetype;
	QString m_author_link_text;

	// <copyright> copyrightType </copyright> [0..1] ?
	QString m_copyright_author;
	unsigned m_copyright_year;
	QString m_copyright_license_url;


	// <time> xsd:dateTime </time> [0..1] ?
	QDateTime m_date_time;

	// <keywords> xsd:string </keywords> [0..1] ?
	QString m_keywords;

	// <bounds> boundsType </bounds> [0..1] ?
	// see getDimensions()

	void initMetaData();

};

#endif /* TRACKCOLLECTION_H_ */
