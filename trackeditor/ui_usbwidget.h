/********************************************************************************
** Form generated from reading ui file 'usbwidget.ui'
**
** Created: Sat May 30 14:16:01 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_USBWIDGET_H
#define UI_USBWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_usbwidget
{
public:
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;

    void setupUi(QWidget *usbwidget)
    {
        if (usbwidget->objectName().isEmpty())
            usbwidget->setObjectName(QString::fromUtf8("usbwidget"));
        usbwidget->resize(387, 395);
        gridLayout_2 = new QGridLayout(usbwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        listWidget = new QListWidget(usbwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_2->addWidget(listWidget, 0, 0, 1, 1);


        retranslateUi(usbwidget);

        QMetaObject::connectSlotsByName(usbwidget);
    } // setupUi

    void retranslateUi(QWidget *usbwidget)
    {
        usbwidget->setWindowTitle(QApplication::translate("usbwidget", "Form", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(usbwidget);
    } // retranslateUi

};

namespace Ui {
    class usbwidget: public Ui_usbwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBWIDGET_H
