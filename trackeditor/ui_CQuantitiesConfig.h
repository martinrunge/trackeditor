/********************************************************************************
** Form generated from reading ui file 'CQuantitiesConfig.ui'
**
** Created: Sun Mar 22 14:57:55 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CQUANTITIESCONFIG_H
#define UI_CQUANTITIESCONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CQuantitiesConfigClass
{
public:
    QCheckBox *timeCheckBox;
    QCheckBox *latLongCheckBox;
    QCheckBox *elevationCheckBox;
    QCheckBox *speedCheckBox;
    QCheckBox *courseCheckBox;
    QCheckBox *hdopCheckBox;
    QCheckBox *vdopCheckBox;
    QCheckBox *pdopCheckBox;
    QCheckBox *numSatsCheckBox;
    QComboBox *comboBox;
    QLabel *dataSourceLabel;

    void setupUi(QWidget *CQuantitiesConfigClass)
    {
    if (CQuantitiesConfigClass->objectName().isEmpty())
        CQuantitiesConfigClass->setObjectName(QString::fromUtf8("CQuantitiesConfigClass"));
    CQuantitiesConfigClass->resize(400, 300);
    timeCheckBox = new QCheckBox(CQuantitiesConfigClass);
    timeCheckBox->setObjectName(QString::fromUtf8("timeCheckBox"));
    timeCheckBox->setGeometry(QRect(230, 20, 101, 22));
    timeCheckBox->setChecked(true);
    latLongCheckBox = new QCheckBox(CQuantitiesConfigClass);
    latLongCheckBox->setObjectName(QString::fromUtf8("latLongCheckBox"));
    latLongCheckBox->setGeometry(QRect(230, 50, 101, 22));
    latLongCheckBox->setChecked(true);
    elevationCheckBox = new QCheckBox(CQuantitiesConfigClass);
    elevationCheckBox->setObjectName(QString::fromUtf8("elevationCheckBox"));
    elevationCheckBox->setGeometry(QRect(230, 80, 83, 22));
    elevationCheckBox->setChecked(true);
    speedCheckBox = new QCheckBox(CQuantitiesConfigClass);
    speedCheckBox->setObjectName(QString::fromUtf8("speedCheckBox"));
    speedCheckBox->setGeometry(QRect(230, 110, 83, 22));
    speedCheckBox->setChecked(true);
    courseCheckBox = new QCheckBox(CQuantitiesConfigClass);
    courseCheckBox->setObjectName(QString::fromUtf8("courseCheckBox"));
    courseCheckBox->setEnabled(false);
    courseCheckBox->setGeometry(QRect(230, 140, 83, 22));
    hdopCheckBox = new QCheckBox(CQuantitiesConfigClass);
    hdopCheckBox->setObjectName(QString::fromUtf8("hdopCheckBox"));
    hdopCheckBox->setGeometry(QRect(230, 170, 83, 22));
    vdopCheckBox = new QCheckBox(CQuantitiesConfigClass);
    vdopCheckBox->setObjectName(QString::fromUtf8("vdopCheckBox"));
    vdopCheckBox->setGeometry(QRect(230, 200, 83, 22));
    pdopCheckBox = new QCheckBox(CQuantitiesConfigClass);
    pdopCheckBox->setObjectName(QString::fromUtf8("pdopCheckBox"));
    pdopCheckBox->setGeometry(QRect(230, 230, 83, 22));
    numSatsCheckBox = new QCheckBox(CQuantitiesConfigClass);
    numSatsCheckBox->setObjectName(QString::fromUtf8("numSatsCheckBox"));
    numSatsCheckBox->setGeometry(QRect(230, 260, 161, 22));
    comboBox = new QComboBox(CQuantitiesConfigClass);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setGeometry(QRect(30, 50, 151, 22));
    dataSourceLabel = new QLabel(CQuantitiesConfigClass);
    dataSourceLabel->setObjectName(QString::fromUtf8("dataSourceLabel"));
    dataSourceLabel->setGeometry(QRect(30, 20, 91, 17));

    retranslateUi(CQuantitiesConfigClass);

    QMetaObject::connectSlotsByName(CQuantitiesConfigClass);
    } // setupUi

    void retranslateUi(QWidget *CQuantitiesConfigClass)
    {
    CQuantitiesConfigClass->setWindowTitle(QApplication::translate("CQuantitiesConfigClass", "CQuantitiesConfig", 0, QApplication::UnicodeUTF8));
    timeCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "Time", 0, QApplication::UnicodeUTF8));
    latLongCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "(Lat, Long)", 0, QApplication::UnicodeUTF8));
    elevationCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "Elevation", 0, QApplication::UnicodeUTF8));
    speedCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "Speed", 0, QApplication::UnicodeUTF8));
    courseCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "Course", 0, QApplication::UnicodeUTF8));
    hdopCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "HDOP", 0, QApplication::UnicodeUTF8));
    vdopCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "VDOP", 0, QApplication::UnicodeUTF8));
    pdopCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "PDOP", 0, QApplication::UnicodeUTF8));
    numSatsCheckBox->setText(QApplication::translate("CQuantitiesConfigClass", "number of Satellites", 0, QApplication::UnicodeUTF8));
    comboBox->clear();
    comboBox->insertItems(0, QStringList()
     << QApplication::translate("CQuantitiesConfigClass", "File", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CQuantitiesConfigClass", "Gps Logger", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CQuantitiesConfigClass", "NEMA GPS", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("CQuantitiesConfigClass", "gpsd", 0, QApplication::UnicodeUTF8)
    );
    dataSourceLabel->setText(QApplication::translate("CQuantitiesConfigClass", "Data Source:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CQuantitiesConfigClass);
    } // retranslateUi

};

namespace Ui {
    class CQuantitiesConfigClass: public Ui_CQuantitiesConfigClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CQUANTITIESCONFIG_H
