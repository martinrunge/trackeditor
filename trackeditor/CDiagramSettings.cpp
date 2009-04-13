/*
 * CDiagramSettings.cpp
 *
 *  Created on: 12.01.2009
 *      Author: martin
 */


#include "CDiagramSettings.h"
#include <QSettings>


CDiagramSettings::CDiagramSettings(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	loadSettings();

	QList<enum plotTypeY> quantityKeys = PlotData::YTypeName.keys();

	for(int i = 0; i < quantityKeys.size(); i++) {
		QString quantityName = PlotData::YTypeName[ quantityKeys[i] ];

		QListWidgetItem *item = new QListWidgetItem(ui.quantitiesListWidget);
		item->setText(quantityName);

	}

//	QListWidgetItem *elevation = new QListWidgetItem(ui.quantitiesListWidget);
//	elevation->setText(tr("Elevation"));
//	QListWidgetItem *speed = new QListWidgetItem(ui.quantitiesListWidget);
//	speed->setText(tr("Speed"));
//	QListWidgetItem *hdop = new QListWidgetItem(ui.quantitiesListWidget);
//	hdop->setText(tr("hdop"));
//	QListWidgetItem *vdop = new QListWidgetItem(ui.quantitiesListWidget);
//	vdop->setText(tr("vdop"));
//	QListWidgetItem *pdop = new QListWidgetItem(ui.quantitiesListWidget);
//	pdop->setText(tr("pdop"));



	connect(ui.addDistBtn, SIGNAL(clicked()), this, SLOT(addDist()));
	connect(ui.rmDistBtn, SIGNAL(clicked()), this, SLOT(rmDist()));

	connect(ui.addTimeBtn, SIGNAL(clicked()), this, SLOT(addTime()));
	connect(ui.rmTimeBtn, SIGNAL(clicked()), this, SLOT(rmTime()));

	connect(ui.addTrackpointsBtn, SIGNAL(clicked()), this, SLOT(addTrackpoints()));
	connect(ui.rmTrackpointsBtn, SIGNAL(clicked()), this, SLOT(rmTrackpoints()));

}

CDiagramSettings::~CDiagramSettings() {
	// TODO Auto-generated destructor stub

	// saveSettings();
}


void CDiagramSettings::loadSettings() {
	QSettings settings;

	QStringList distList;
	distList = settings.value("diagrams/distance").toStringList();

	QStringList::iterator it;
	for(it = distList.begin(); it != distList.end(); it++) {
		QListWidgetItem* item = new QListWidgetItem();
		QString text = PlotData::YTypeName[ PlotData::YTypeNamesForSettings[*it] ];
		item->setText(text);
		ui.distListWidget->addItem(item);
	}

	QStringList timeList;
	timeList = settings.value("diagrams/time").toStringList();

	for(it = timeList.begin(); it != timeList.end(); it++) {
		QListWidgetItem* item = new QListWidgetItem();
		QString text = PlotData::YTypeName[ PlotData::YTypeNamesForSettings[*it] ];
		item->setText(text);
		ui.timeListWidget->addItem(item);
	}

	QStringList trackpointsList;
	trackpointsList = settings.value("diagrams/trackpoints").toStringList();

	for(it = trackpointsList.begin(); it != trackpointsList.end(); it++) {
		QListWidgetItem* item = new QListWidgetItem();
		QString text = PlotData::YTypeName[ PlotData::YTypeNamesForSettings[*it] ];
		item->setText(text);
		ui.trackpointsListWidget->addItem(item);
	}

}

QStringList CDiagramSettings::getDistValStrings() {
	QStringList distList;

	for(int i=0; i < ui.distListWidget->count(); i++) {
		distList.append(ui.distListWidget->item(i)->text());
	}

	return distList;
}

QStringList CDiagramSettings::getTimeValStrings() {
	QStringList timeList;

	for(int i=0; i < ui.timeListWidget->count(); i++) {
		timeList.append(ui.timeListWidget->item(i)->text());
	}
	return timeList;
}

QStringList CDiagramSettings::getTrackPointValStrings() {
	QStringList trackpointsList;

	for(int i=0; i < ui.trackpointsListWidget->count(); i++) {
		trackpointsList.append(ui.trackpointsListWidget->item(i)->text());
	}
	return trackpointsList;
}

QList<enum plotTypeY> CDiagramSettings::getDistVals() {
	QList<enum plotTypeY> distList;

	for(int i=0; i < ui.distListWidget->count(); i++) {
		// get the translated name of value
		QString valueName = ui.distListWidget->item(i)->text();
		// if no key is found for this value, discard it.
		enum plotTypeY val = PlotData::YTypeName.key(valueName, TYPE_Y_NONE);
		if(val != TYPE_Y_NONE ) {
			distList.append(val);
		}
	}

	return distList;
}

QList<enum plotTypeY> CDiagramSettings::getTimeVals() {
	QList<enum plotTypeY> timeList;

	for(int i=0; i < ui.timeListWidget->count(); i++) {
		// get the translated name of value
		QString valueName = ui.timeListWidget->item(i)->text();
		// if no key is found for this value, discard it.
		enum plotTypeY val = PlotData::YTypeName.key(valueName, TYPE_Y_NONE);
		if(val != TYPE_Y_NONE ) {
			timeList.append(val);
		}
	}
	return timeList;
}

QList<enum plotTypeY> CDiagramSettings::getTrackPointVals() {
	QList<enum plotTypeY> trackpointsList;

	for(int i=0; i < ui.trackpointsListWidget->count(); i++) {
		// get the translated name of value
		QString valueName = ui.trackpointsListWidget->item(i)->text();
		// if no key is found for this value, discard it.
		enum plotTypeY val = PlotData::YTypeName.key(valueName, TYPE_Y_NONE);
		if(val != TYPE_Y_NONE ) {
			trackpointsList.append(val);
		}
	}
	return trackpointsList;
}

//void CDiagramSettings::saveSettings() {
//	QSettings settings;
//
//	QList<enum plotTypeY> distList = getDistVals();
//	QStringList savelist;
//	for(int i = 0; i < distList.count(); i++) {
//		savelist.append( );
//	}
//	settings.setValue("diagrams/distance", distList);
//
//	QList<enum plotTypeY> timeList = getTimeVals();
//	settings.setValue("diagrams/time", timeList);
//
//	QList<enum plotTypeY> trackpointsList = getTrackPointVals();
//	settings.setValue("diagrams/trackpoints", trackpointsList);
//
//}


void CDiagramSettings::addDist() {
	QListWidgetItem* item = ui.quantitiesListWidget->currentItem();
	if(item) {
		bool already_in = false;
		for(int i=0; i < ui.distListWidget->count(); i++) {
			if(ui.distListWidget->item(i)->text().compare(item->text()) == 0 ) {
				already_in = true;
			}
		}
		if(!already_in) {
			QListWidgetItem* newitem = new QListWidgetItem(*item);
			ui.distListWidget->addItem(newitem);
		}
	}
}

void CDiagramSettings::rmDist() {
	QListWidgetItem* item = ui.distListWidget->currentItem();
	if(item) {
		// ui.distListWidget->removeItemWidget(item);
		QListWidgetItem* item = ui.distListWidget->takeItem(ui.distListWidget->currentRow());
		delete item;
	}
}

void CDiagramSettings::addTime() {
	QListWidgetItem* item = ui.quantitiesListWidget->currentItem();
	if(item) {
		bool already_in = false;
		for(int i=0; i < ui.timeListWidget->count(); i++) {
			if(ui.timeListWidget->item(i)->text().compare(item->text()) == 0 ) {
				already_in = true;
			}
		}
		if(!already_in) {
			QListWidgetItem* newitem = new QListWidgetItem(*item);
			ui.timeListWidget->addItem(newitem);
		}
	}
}

void CDiagramSettings::rmTime() {
	QListWidgetItem* item = ui.timeListWidget->currentItem();
	if(item) {
		// ui.distListWidget->removeItemWidget(item);
		QListWidgetItem* item = ui.timeListWidget->takeItem(ui.timeListWidget->currentRow());
		delete item;
	}
}

void CDiagramSettings::addTrackpoints() {
	QListWidgetItem* item = ui.quantitiesListWidget->currentItem();
	if(item) {
		bool already_in = false;
		for(int i=0; i < ui.trackpointsListWidget->count(); i++) {
			if(ui.trackpointsListWidget->item(i)->text().compare(item->text()) == 0 ) {
				already_in = true;
			}
		}
		if(!already_in) {
			QListWidgetItem* newitem = new QListWidgetItem(*item);
			ui.trackpointsListWidget->addItem(newitem);
		}
	}
}

void CDiagramSettings::rmTrackpoints() {
	QListWidgetItem* item = ui.trackpointsListWidget->currentItem();
	if(item) {
		// ui.distListWidget->removeItemWidget(item);
		QListWidgetItem* item = ui.trackpointsListWidget->takeItem(ui.trackpointsListWidget->currentRow());
		delete item;
	}
}


