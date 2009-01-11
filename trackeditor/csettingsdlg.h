#ifndef CSETTINGSDLG_H
#define CSETTINGSDLG_H

#include <QtGui/QDialog>
#include "ui_csettingsdlg.h"

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

private:

	void loadSettings();
	void saveSettings();

    Ui::CSettingsDlgClass ui;

    LogReader* m_parent;

};

#endif // CSETTINGSDLG_H
