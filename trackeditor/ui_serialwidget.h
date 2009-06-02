/********************************************************************************
** Form generated from reading ui file 'serialwidget.ui'
**
** Created: Sat May 30 14:16:01 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SERIALWIDGET_H
#define UI_SERIALWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_genericserialwidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *speedLabel;
    QComboBox *comboBox;
    QLabel *databitsLabel;
    QComboBox *comboBox_2;
    QLabel *parityLabel;
    QComboBox *comboBox_3;
    QLabel *stopbitsLabel;
    QComboBox *comboBox_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *genericserialwidget)
    {
        if (genericserialwidget->objectName().isEmpty())
            genericserialwidget->setObjectName(QString::fromUtf8("genericserialwidget"));
        genericserialwidget->resize(400, 300);
        gridLayout = new QGridLayout(genericserialwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(genericserialwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        label = new QLabel(genericserialwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEdit = new QLineEdit(genericserialwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        speedLabel = new QLabel(genericserialwidget);
        speedLabel->setObjectName(QString::fromUtf8("speedLabel"));

        gridLayout->addWidget(speedLabel, 2, 0, 1, 1);

        comboBox = new QComboBox(genericserialwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        databitsLabel = new QLabel(genericserialwidget);
        databitsLabel->setObjectName(QString::fromUtf8("databitsLabel"));

        gridLayout->addWidget(databitsLabel, 3, 0, 1, 1);

        comboBox_2 = new QComboBox(genericserialwidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 3, 1, 1, 1);

        parityLabel = new QLabel(genericserialwidget);
        parityLabel->setObjectName(QString::fromUtf8("parityLabel"));

        gridLayout->addWidget(parityLabel, 4, 0, 1, 1);

        comboBox_3 = new QComboBox(genericserialwidget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 4, 1, 1, 1);

        stopbitsLabel = new QLabel(genericserialwidget);
        stopbitsLabel->setObjectName(QString::fromUtf8("stopbitsLabel"));

        gridLayout->addWidget(stopbitsLabel, 5, 0, 1, 1);

        comboBox_4 = new QComboBox(genericserialwidget);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        gridLayout->addWidget(comboBox_4, 5, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 95, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 1, 1, 1);


        retranslateUi(genericserialwidget);

        comboBox->setCurrentIndex(3);
        comboBox_2->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(genericserialwidget);
    } // setupUi

    void retranslateUi(QWidget *genericserialwidget)
    {
        genericserialwidget->setWindowTitle(QApplication::translate("genericserialwidget", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("genericserialwidget", "Manual interface settings:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("genericserialwidget", "Device File:", 0, QApplication::UnicodeUTF8));
        speedLabel->setText(QApplication::translate("genericserialwidget", "Speed [bit/s]:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("genericserialwidget", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "14400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "28800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "115200", 0, QApplication::UnicodeUTF8)
        );
        databitsLabel->setText(QApplication::translate("genericserialwidget", "Databits:", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("genericserialwidget", "6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "8", 0, QApplication::UnicodeUTF8)
        );
        parityLabel->setText(QApplication::translate("genericserialwidget", "Parity:", 0, QApplication::UnicodeUTF8));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("genericserialwidget", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "Odd", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "Even", 0, QApplication::UnicodeUTF8)
        );
        stopbitsLabel->setText(QApplication::translate("genericserialwidget", "Stopbits:", 0, QApplication::UnicodeUTF8));
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("genericserialwidget", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "1.5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("genericserialwidget", "2", 0, QApplication::UnicodeUTF8)
        );
        Q_UNUSED(genericserialwidget);
    } // retranslateUi

};

namespace Ui {
    class genericserialwidget: public Ui_genericserialwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALWIDGET_H
