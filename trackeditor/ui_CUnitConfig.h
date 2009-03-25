/********************************************************************************
** Form generated from reading ui file 'CUnitConfig.ui'
**
** Created: Sun Mar 22 14:57:55 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CUNITCONFIG_H
#define UI_CUNITCONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CUnitConfigClass
{
public:
    QLabel *distanceUnitLabel;
    QComboBox *distanceUnit;
    QComboBox *timeUnit;
    QLabel *timeUnitLabel;
    QLabel *speedUnitLabel;
    QComboBox *speedUnit;
    QComboBox *elevationUnit;
    QLabel *elevationUnitLabel;

    void setupUi(QWidget *CUnitConfigClass)
    {
    if (CUnitConfigClass->objectName().isEmpty())
        CUnitConfigClass->setObjectName(QString::fromUtf8("CUnitConfigClass"));
    CUnitConfigClass->resize(400, 300);
    distanceUnitLabel = new QLabel(CUnitConfigClass);
    distanceUnitLabel->setObjectName(QString::fromUtf8("distanceUnitLabel"));
    distanceUnitLabel->setGeometry(QRect(30, 30, 71, 21));
    distanceUnit = new QComboBox(CUnitConfigClass);
    distanceUnit->setObjectName(QString::fromUtf8("distanceUnit"));
    distanceUnit->setGeometry(QRect(120, 30, 141, 22));
    timeUnit = new QComboBox(CUnitConfigClass);
    timeUnit->setObjectName(QString::fromUtf8("timeUnit"));
    timeUnit->setGeometry(QRect(120, 70, 141, 22));
    timeUnitLabel = new QLabel(CUnitConfigClass);
    timeUnitLabel->setObjectName(QString::fromUtf8("timeUnitLabel"));
    timeUnitLabel->setGeometry(QRect(30, 70, 71, 20));
    speedUnitLabel = new QLabel(CUnitConfigClass);
    speedUnitLabel->setObjectName(QString::fromUtf8("speedUnitLabel"));
    speedUnitLabel->setGeometry(QRect(30, 110, 61, 20));
    speedUnit = new QComboBox(CUnitConfigClass);
    speedUnit->setObjectName(QString::fromUtf8("speedUnit"));
    speedUnit->setGeometry(QRect(120, 110, 141, 22));
    elevationUnit = new QComboBox(CUnitConfigClass);
    elevationUnit->setObjectName(QString::fromUtf8("elevationUnit"));
    elevationUnit->setGeometry(QRect(120, 150, 141, 22));
    elevationUnitLabel = new QLabel(CUnitConfigClass);
    elevationUnitLabel->setObjectName(QString::fromUtf8("elevationUnitLabel"));
    elevationUnitLabel->setGeometry(QRect(30, 150, 61, 20));

    retranslateUi(CUnitConfigClass);

    QMetaObject::connectSlotsByName(CUnitConfigClass);
    } // setupUi

    void retranslateUi(QWidget *CUnitConfigClass)
    {
    CUnitConfigClass->setWindowTitle(QApplication::translate("CUnitConfigClass", "CUnitConfig", 0, QApplication::UnicodeUTF8));
    distanceUnitLabel->setText(QApplication::translate("CUnitConfigClass", "Distance:", 0, QApplication::UnicodeUTF8));
    distanceUnit->clear();
    distanceUnit->insertItems(0, QStringList()
     << QApplication::translate("CUnitConfigClass", "Meters [m]", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "Kilometers [km]", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "Nautic Mils [nm]", 0, QApplication::UnicodeUTF8)
    );
    timeUnit->clear();
    timeUnit->insertItems(0, QStringList()
     << QApplication::translate("CUnitConfigClass", "Days [d]", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "Hours [h]", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "Minutes [min]", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "Seconds [sec]", 0, QApplication::UnicodeUTF8)
    );
    timeUnitLabel->setText(QApplication::translate("CUnitConfigClass", "Time:", 0, QApplication::UnicodeUTF8));
    speedUnitLabel->setText(QApplication::translate("CUnitConfigClass", "Speed:", 0, QApplication::UnicodeUTF8));
    speedUnit->clear();
    speedUnit->insertItems(0, QStringList()
     << QApplication::translate("CUnitConfigClass", "km/h", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "m/s", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "knots [nm/h]", 0, QApplication::UnicodeUTF8)
    );
    elevationUnit->clear();
    elevationUnit->insertItems(0, QStringList()
     << QApplication::translate("CUnitConfigClass", "Kilometers [km]", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "Meters [m]", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CUnitConfigClass", "Feet [ft]", 0, QApplication::UnicodeUTF8)
    );
    elevationUnitLabel->setText(QApplication::translate("CUnitConfigClass", "Elevation:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CUnitConfigClass);
    } // retranslateUi

};

namespace Ui {
    class CUnitConfigClass: public Ui_CUnitConfigClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUNITCONFIG_H
