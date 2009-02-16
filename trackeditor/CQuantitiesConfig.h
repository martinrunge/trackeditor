#ifndef CQUANTITIESCONFIG_H
#define CQUANTITIESCONFIG_H

#include <QtGui/QWidget>
#include "ui_CQuantitiesConfig.h"

class CQuantitiesConfig : public QWidget
{
    Q_OBJECT

public:
    CQuantitiesConfig(QWidget *parent = 0);
    ~CQuantitiesConfig();

private:
    Ui::CQuantitiesConfigClass ui;
};

#endif // CQUANTITIESCONFIG_H
