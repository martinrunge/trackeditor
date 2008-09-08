/********************************************************************************
** Form generated from reading ui file 'DeviceDialog.ui'
**
** Created: Sat Sep 6 12:44:45 2008
**      by: Qt User Interface Compiler version 4.4.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DEVICEDIALOG_H
#define UI_DEVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DeviceDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox_2;

    void setupUi(QDialog *DeviceDialog)
    {
    if (DeviceDialog->objectName().isEmpty())
        DeviceDialog->setObjectName(QString::fromUtf8("DeviceDialog"));
    DeviceDialog->resize(400, 300);
    buttonBox = new QDialogButtonBox(DeviceDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(30, 240, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    comboBox = new QComboBox(DeviceDialog);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setGeometry(QRect(20, 110, 311, 23));
    label = new QLabel(DeviceDialog);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(20, 90, 211, 20));
    label_2 = new QLabel(DeviceDialog);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(20, 10, 131, 20));
    comboBox_2 = new QComboBox(DeviceDialog);
    comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
    comboBox_2->setGeometry(QRect(20, 30, 311, 23));

    retranslateUi(DeviceDialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), DeviceDialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), DeviceDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(DeviceDialog);
    } // setupUi

    void retranslateUi(QDialog *DeviceDialog)
    {
    DeviceDialog->setWindowTitle(QApplication::translate("DeviceDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("DeviceDialog", "Interface", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("DeviceDialog", "Device Model", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(DeviceDialog);
    } // retranslateUi

};

namespace Ui {
    class DeviceDialog: public Ui_DeviceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEDIALOG_H
