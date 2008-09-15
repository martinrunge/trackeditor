/********************************************************************************
** Form generated from reading ui file 'ProgressDialog.ui'
**
** Created: Sat Sep 13 14:30:22 2008
**      by: Qt User Interface Compiler version 4.4.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PROGRESSDIALOG_H
#define UI_PROGRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ProgressDialog
{
public:
    QPushButton *cancelButton;
    QProgressBar *progressBar;
    QLabel *label;
    QLabel *label_2;
    QLabel *m_num_tracks;
    QLabel *m_num_logpoints;

    void setupUi(QDialog *ProgressDialog)
    {
    if (ProgressDialog->objectName().isEmpty())
        ProgressDialog->setObjectName(QString::fromUtf8("ProgressDialog"));
    ProgressDialog->resize(400, 222);
    cancelButton = new QPushButton(ProgressDialog);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
    cancelButton->setGeometry(QRect(130, 170, 123, 30));
    progressBar = new QProgressBar(ProgressDialog);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setGeometry(QRect(30, 30, 341, 23));
    progressBar->setValue(24);
    label = new QLabel(ProgressDialog);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(180, 70, 121, 22));
    label_2 = new QLabel(ProgressDialog);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(180, 100, 101, 22));
    m_num_tracks = new QLabel(ProgressDialog);
    m_num_tracks->setObjectName(QString::fromUtf8("m_num_tracks"));
    m_num_tracks->setGeometry(QRect(90, 70, 75, 22));
    m_num_tracks->setLayoutDirection(Qt::LeftToRight);
    m_num_tracks->setScaledContents(false);
    m_num_tracks->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    m_num_logpoints = new QLabel(ProgressDialog);
    m_num_logpoints->setObjectName(QString::fromUtf8("m_num_logpoints"));
    m_num_logpoints->setGeometry(QRect(90, 100, 75, 22));
    m_num_logpoints->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    retranslateUi(ProgressDialog);

    QMetaObject::connectSlotsByName(ProgressDialog);
    } // setupUi

    void retranslateUi(QDialog *ProgressDialog)
    {
    ProgressDialog->setWindowTitle(QApplication::translate("ProgressDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("ProgressDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ProgressDialog", "Tracks", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ProgressDialog", "Log Points ", 0, QApplication::UnicodeUTF8));
    m_num_tracks->setText(QApplication::translate("ProgressDialog", "0", 0, QApplication::UnicodeUTF8));
    m_num_logpoints->setText(QApplication::translate("ProgressDialog", "0", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ProgressDialog);
    } // retranslateUi

};

namespace Ui {
    class ProgressDialog: public Ui_ProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSDIALOG_H
