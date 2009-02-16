/*
 * CDiagramSettings.h
 *
 *  Created on: 12.01.2009
 *      Author: martin
 */

#ifndef CDIAGRAMSETTINGS_H_
#define CDIAGRAMSETTINGS_H_


#include <QtGui/QWidget>
#include "ui_diagramSettings.h"

class CDiagramSettings : public QWidget
{
    Q_OBJECT

public:
	CDiagramSettings(QWidget *parent = 0);
	virtual ~CDiagramSettings();

	QStringList getDistVals();
	QStringList getTimeVals();
	QStringList getTrackPointVals();

	void loadSettings();
	void saveSettings();

public slots:
	void addDist();
	void rmDist();

	void addTime();
	void rmTime();

	void addTrackpoints();
	void rmTrackpoints();

private:
	Ui::diagramSettingsWidget ui;
};

#endif /* CDIAGRAMSETTINGS_H_ */
