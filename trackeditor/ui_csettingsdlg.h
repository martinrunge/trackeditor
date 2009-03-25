/********************************************************************************
** Form generated from reading ui file 'csettingsdlg.ui'
**
** Created: Sun Mar 22 14:57:55 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CSETTINGSDLG_H
#define UI_CSETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSettingsDlgClass
{
public:
    QGridLayout *gridLayout;
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    QWidget *page_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *applyButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *CSettingsDlgClass)
    {
    if (CSettingsDlgClass->objectName().isEmpty())
        CSettingsDlgClass->setObjectName(QString::fromUtf8("CSettingsDlgClass"));
    CSettingsDlgClass->resize(742, 484);
    gridLayout = new QGridLayout(CSettingsDlgClass);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    contentsWidget = new QListWidget(CSettingsDlgClass);
    contentsWidget->setObjectName(QString::fromUtf8("contentsWidget"));
    contentsWidget->setMinimumSize(QSize(128, 0));
    contentsWidget->setMaximumSize(QSize(128, 16777215));
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Snap);
    contentsWidget->setSpacing(12);
    contentsWidget->setViewMode(QListView::IconMode);

    gridLayout->addWidget(contentsWidget, 0, 0, 3, 1);

    pagesWidget = new QStackedWidget(CSettingsDlgClass);
    pagesWidget->setObjectName(QString::fromUtf8("pagesWidget"));
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    pagesWidget->addWidget(page_2);

    gridLayout->addWidget(pagesWidget, 0, 1, 1, 1);

    line = new QFrame(CSettingsDlgClass);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line, 1, 1, 1, 1);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    okButton = new QPushButton(CSettingsDlgClass);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    horizontalLayout->addWidget(okButton);

    applyButton = new QPushButton(CSettingsDlgClass);
    applyButton->setObjectName(QString::fromUtf8("applyButton"));

    horizontalLayout->addWidget(applyButton);

    cancelButton = new QPushButton(CSettingsDlgClass);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    horizontalLayout->addWidget(cancelButton);


    gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);


    retranslateUi(CSettingsDlgClass);

    QMetaObject::connectSlotsByName(CSettingsDlgClass);
    } // setupUi

    void retranslateUi(QDialog *CSettingsDlgClass)
    {
    CSettingsDlgClass->setWindowTitle(QApplication::translate("CSettingsDlgClass", "CSettingsDlg", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("CSettingsDlgClass", "Ok", 0, QApplication::UnicodeUTF8));
    applyButton->setText(QApplication::translate("CSettingsDlgClass", "Apply", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("CSettingsDlgClass", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(CSettingsDlgClass);
    } // retranslateUi

};

namespace Ui {
    class CSettingsDlgClass: public Ui_CSettingsDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSETTINGSDLG_H
