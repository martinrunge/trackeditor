#ifndef CUNITCONFIG_H
#define CUNITCONFIG_H

#include <QtGui/QWidget>
#include "ui_CUnitConfig.h"

class CUnitConfig : public QWidget
{
    Q_OBJECT

public:
    CUnitConfig(QWidget *parent = 0);
    ~CUnitConfig();

private:
    Ui::CUnitConfigClass ui;
};

#endif // CUNITCONFIG_H
