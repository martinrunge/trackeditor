/*
 * CAboutDialog.h
 *
 *  Created on: 20 Sep 2009
 *      Author: martin
 */

#ifndef CABOUTDIALOG_H_
#define CABOUTDIALOG_H_

#include <QDialog>

#include "ui_AboutDialog.h"

class CAboutDialog : public QDialog, public Ui::AboutDialog {
public:
	CAboutDialog(QWidget *parent);
	virtual ~CAboutDialog();
};

#endif /* CABOUTDIALOG_H_ */
