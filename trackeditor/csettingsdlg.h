#ifndef CSETTINGSDLG_H
#define CSETTINGSDLG_H

#include <QtGui/QDialog>
#include "ui_csettingsdlg.h"

#include "CDiagramSettings.h"

class LogReader;


class CSettingsDlg : public QDialog
{
    Q_OBJECT

public:
    CSettingsDlg(LogReader *parent = 0);
    ~CSettingsDlg();

public slots:
	void apply();
	void accept();
	void reject();

	void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:

	void createIcons();

	void loadSettings();
	void saveSettings();

    Ui::CSettingsDlgClass ui;

    LogReader* m_parent;

    CDiagramSettings *m_diagram_settings;

};

#endif // CSETTINGSDLG_H
