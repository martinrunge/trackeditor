/********************************************************************************
** Form generated from reading ui file 'bluetoothwidget.ui'
**
** Created: Sat May 30 14:16:01 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_BLUETOOTHWIDGET_H
#define UI_BLUETOOTHWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bluetoothwidget
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QListView *listView;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_4;
    QLabel *deviceFileLabel;
    QPushButton *pushButton;
    QPushButton *pushButton_5;

    void setupUi(QWidget *bluetoothwidget)
    {
        if (bluetoothwidget->objectName().isEmpty())
            bluetoothwidget->setObjectName(QString::fromUtf8("bluetoothwidget"));
        bluetoothwidget->resize(707, 408);
        gridLayout_2 = new QGridLayout(bluetoothwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(bluetoothwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label = new QLabel(bluetoothwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 2, 1, 2);

        label_3 = new QLabel(bluetoothwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        listView = new QListView(bluetoothwidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout_2->addWidget(listView, 1, 2, 4, 2);

        pushButton_2 = new QPushButton(bluetoothwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 2, 0, 1, 1);

        pushButton_3 = new QPushButton(bluetoothwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setEnabled(false);

        gridLayout_2->addWidget(pushButton_3, 2, 1, 1, 1);

        label_4 = new QLabel(bluetoothwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        deviceFileLabel = new QLabel(bluetoothwidget);
        deviceFileLabel->setObjectName(QString::fromUtf8("deviceFileLabel"));

        gridLayout_2->addWidget(deviceFileLabel, 3, 1, 1, 1);

        pushButton = new QPushButton(bluetoothwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 5, 2, 1, 1);

        pushButton_5 = new QPushButton(bluetoothwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 5, 3, 1, 1);


        retranslateUi(bluetoothwidget);

        QMetaObject::connectSlotsByName(bluetoothwidget);
    } // setupUi

    void retranslateUi(QWidget *bluetoothwidget)
    {
        bluetoothwidget->setWindowTitle(QApplication::translate("bluetoothwidget", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("bluetoothwidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">&lt;none&gt;</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("bluetoothwidget", "Bluetooth devices found:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("bluetoothwidget", "MAC address", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("bluetoothwidget", "connect", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("bluetoothwidget", "disconnect", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("bluetoothwidget", "connected to:", 0, QApplication::UnicodeUTF8));
        deviceFileLabel->setText(QApplication::translate("bluetoothwidget", "<none>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("bluetoothwidget", "search", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("bluetoothwidget", "stop search", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(bluetoothwidget);
    } // retranslateUi

};

namespace Ui {
    class bluetoothwidget: public Ui_bluetoothwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTHWIDGET_H
