/********************************************************************************
** Form generated from reading ui file 'diagramSettings.ui'
**
** Created: Sun Mar 22 14:57:55 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIAGRAMSETTINGS_H
#define UI_DIAGRAMSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_diagramSettingsWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *quantitiesListWidget;
    QSpacerItem *horizontalSpacer;
    QPushButton *addDistBtn;
    QPushButton *rmDistBtn;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *addTimeBtn;
    QPushButton *rmTimeBtn;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *addTrackpointsBtn;
    QPushButton *rmTrackpointsBtn;
    QSpacerItem *horizontalSpacer_4;
    QListWidget *distListWidget;
    QListWidget *timeListWidget;
    QListWidget *trackpointsListWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *diagramSettingsWidget)
    {
    if (diagramSettingsWidget->objectName().isEmpty())
        diagramSettingsWidget->setObjectName(QString::fromUtf8("diagramSettingsWidget"));
    diagramSettingsWidget->resize(507, 335);
    gridLayout = new QGridLayout(diagramSettingsWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    label = new QLabel(diagramSettingsWidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(label, 0, 0, 1, 14);

    quantitiesListWidget = new QListWidget(diagramSettingsWidget);
    quantitiesListWidget->setObjectName(QString::fromUtf8("quantitiesListWidget"));

    gridLayout->addWidget(quantitiesListWidget, 1, 0, 1, 14);

    horizontalSpacer = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

    addDistBtn = new QPushButton(diagramSettingsWidget);
    addDistBtn->setObjectName(QString::fromUtf8("addDistBtn"));
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/images/images/arrow-down.png")), QIcon::Normal, QIcon::Off);
    addDistBtn->setIcon(icon);

    gridLayout->addWidget(addDistBtn, 2, 1, 2, 1);

    rmDistBtn = new QPushButton(diagramSettingsWidget);
    rmDistBtn->setObjectName(QString::fromUtf8("rmDistBtn"));
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8(":/images/images/arrow-up.png")), QIcon::Normal, QIcon::Off);
    rmDistBtn->setIcon(icon1);

    gridLayout->addWidget(rmDistBtn, 2, 2, 2, 1);

    horizontalSpacer_2 = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_2, 3, 3, 1, 1);

    line = new QFrame(diagramSettingsWidget);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line, 2, 4, 4, 2);

    horizontalSpacer_5 = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_5, 3, 5, 1, 1);

    addTimeBtn = new QPushButton(diagramSettingsWidget);
    addTimeBtn->setObjectName(QString::fromUtf8("addTimeBtn"));
    addTimeBtn->setIcon(icon);

    gridLayout->addWidget(addTimeBtn, 2, 6, 2, 1);

    rmTimeBtn = new QPushButton(diagramSettingsWidget);
    rmTimeBtn->setObjectName(QString::fromUtf8("rmTimeBtn"));
    rmTimeBtn->setIcon(icon1);

    gridLayout->addWidget(rmTimeBtn, 2, 7, 2, 1);

    horizontalSpacer_6 = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_6, 3, 8, 1, 1);

    line_2 = new QFrame(diagramSettingsWidget);
    line_2->setObjectName(QString::fromUtf8("line_2"));
    line_2->setFrameShape(QFrame::VLine);
    line_2->setFrameShadow(QFrame::Sunken);

    gridLayout->addWidget(line_2, 2, 9, 4, 2);

    horizontalSpacer_3 = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_3, 3, 10, 1, 1);

    addTrackpointsBtn = new QPushButton(diagramSettingsWidget);
    addTrackpointsBtn->setObjectName(QString::fromUtf8("addTrackpointsBtn"));
    addTrackpointsBtn->setIcon(icon);

    gridLayout->addWidget(addTrackpointsBtn, 2, 11, 2, 1);

    rmTrackpointsBtn = new QPushButton(diagramSettingsWidget);
    rmTrackpointsBtn->setObjectName(QString::fromUtf8("rmTrackpointsBtn"));
    rmTrackpointsBtn->setIcon(icon1);

    gridLayout->addWidget(rmTrackpointsBtn, 2, 12, 2, 1);

    horizontalSpacer_4 = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_4, 3, 13, 1, 1);

    distListWidget = new QListWidget(diagramSettingsWidget);
    distListWidget->setObjectName(QString::fromUtf8("distListWidget"));

    gridLayout->addWidget(distListWidget, 4, 0, 1, 4);

    timeListWidget = new QListWidget(diagramSettingsWidget);
    timeListWidget->setObjectName(QString::fromUtf8("timeListWidget"));

    gridLayout->addWidget(timeListWidget, 4, 5, 1, 4);

    trackpointsListWidget = new QListWidget(diagramSettingsWidget);
    trackpointsListWidget->setObjectName(QString::fromUtf8("trackpointsListWidget"));

    gridLayout->addWidget(trackpointsListWidget, 4, 10, 1, 4);

    label_2 = new QLabel(diagramSettingsWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(label_2, 5, 0, 1, 4);

    label_3 = new QLabel(diagramSettingsWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(label_3, 5, 5, 1, 4);

    label_4 = new QLabel(diagramSettingsWidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setAlignment(Qt::AlignCenter);

    gridLayout->addWidget(label_4, 5, 10, 1, 4);


    retranslateUi(diagramSettingsWidget);

    QMetaObject::connectSlotsByName(diagramSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *diagramSettingsWidget)
    {
    diagramSettingsWidget->setWindowTitle(QApplication::translate("diagramSettingsWidget", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("diagramSettingsWidget", "Track quanties", 0, QApplication::UnicodeUTF8));
    addDistBtn->setText(QString());
    rmDistBtn->setText(QString());
    addTimeBtn->setText(QString());
    rmTimeBtn->setText(QString());
    addTrackpointsBtn->setText(QString());
    rmTrackpointsBtn->setText(QString());
    label_2->setText(QApplication::translate("diagramSettingsWidget", "distance", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("diagramSettingsWidget", "time", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("diagramSettingsWidget", "trackpoints", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(diagramSettingsWidget);
    } // retranslateUi

};

namespace Ui {
    class diagramSettingsWidget: public Ui_diagramSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGRAMSETTINGS_H
