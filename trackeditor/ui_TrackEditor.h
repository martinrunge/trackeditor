/********************************************************************************
** Form generated from reading ui file 'TrackEditor.ui'
**
** Created: Sat Sep 6 12:44:45 2008
**      by: Qt User Interface Compiler version 4.4.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TRACKEDITOR_H
#define UI_TRACKEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackEditor2Class
{
public:
    QAction *action_Connect;
    QAction *actionExit;
    QAction *action_Read_Log;
    QAction *action_Save_Track;
    QAction *action_Save_Track_As;
    QAction *action_Load_Track;
    QAction *action_Disconnect;
    QAction *action_Start_Recording;
    QAction *action_Stop_Recording;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *nemaText;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTrack;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TrackEditor2Class)
    {
    if (TrackEditor2Class->objectName().isEmpty())
        TrackEditor2Class->setObjectName(QString::fromUtf8("TrackEditor2Class"));
    TrackEditor2Class->resize(1030, 878);
    action_Connect = new QAction(TrackEditor2Class);
    action_Connect->setObjectName(QString::fromUtf8("action_Connect"));
    actionExit = new QAction(TrackEditor2Class);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    action_Read_Log = new QAction(TrackEditor2Class);
    action_Read_Log->setObjectName(QString::fromUtf8("action_Read_Log"));
    action_Save_Track = new QAction(TrackEditor2Class);
    action_Save_Track->setObjectName(QString::fromUtf8("action_Save_Track"));
    action_Save_Track_As = new QAction(TrackEditor2Class);
    action_Save_Track_As->setObjectName(QString::fromUtf8("action_Save_Track_As"));
    action_Load_Track = new QAction(TrackEditor2Class);
    action_Load_Track->setObjectName(QString::fromUtf8("action_Load_Track"));
    action_Disconnect = new QAction(TrackEditor2Class);
    action_Disconnect->setObjectName(QString::fromUtf8("action_Disconnect"));
    action_Start_Recording = new QAction(TrackEditor2Class);
    action_Start_Recording->setObjectName(QString::fromUtf8("action_Start_Recording"));
    action_Stop_Recording = new QAction(TrackEditor2Class);
    action_Stop_Recording->setObjectName(QString::fromUtf8("action_Stop_Recording"));
    centralwidget = new QWidget(TrackEditor2Class);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(0, 24, 1030, 830));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
    centralwidget->setSizePolicy(sizePolicy);
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    treeView = new QTreeView(centralwidget);
    treeView->setObjectName(QString::fromUtf8("treeView"));
    treeView->setMinimumSize(QSize(324, 0));
    treeView->setMaximumSize(QSize(508, 16777215));

    horizontalLayout->addWidget(treeView);

    scrollArea = new QScrollArea(centralwidget);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 498, 600));
    scrollArea->setWidget(scrollAreaWidgetContents);

    horizontalLayout->addWidget(scrollArea);


    verticalLayout->addLayout(horizontalLayout);

    nemaText = new QPlainTextEdit(centralwidget);
    nemaText->setObjectName(QString::fromUtf8("nemaText"));
    nemaText->setEnabled(true);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(nemaText->sizePolicy().hasHeightForWidth());
    nemaText->setSizePolicy(sizePolicy1);
    nemaText->setMinimumSize(QSize(0, 200));

    verticalLayout->addWidget(nemaText);

    TrackEditor2Class->setCentralWidget(centralwidget);
    menubar = new QMenuBar(TrackEditor2Class);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1030, 24));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuTrack = new QMenu(menubar);
    menuTrack->setObjectName(QString::fromUtf8("menuTrack"));
    TrackEditor2Class->setMenuBar(menubar);
    statusbar = new QStatusBar(TrackEditor2Class);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    statusbar->setGeometry(QRect(0, 854, 1030, 24));
    TrackEditor2Class->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuTrack->menuAction());
    menuFile->addAction(action_Connect);
    menuFile->addAction(action_Load_Track);
    menuFile->addAction(action_Save_Track);
    menuFile->addAction(action_Save_Track_As);
    menuFile->addSeparator();
    menuFile->addAction(action_Disconnect);
    menuFile->addAction(actionExit);
    menuTrack->addAction(action_Read_Log);
    menuTrack->addAction(action_Start_Recording);
    menuTrack->addAction(action_Stop_Recording);

    retranslateUi(TrackEditor2Class);

    QMetaObject::connectSlotsByName(TrackEditor2Class);
    } // setupUi

    void retranslateUi(QMainWindow *TrackEditor2Class)
    {
    TrackEditor2Class->setWindowTitle(QApplication::translate("TrackEditor2Class", "MainWindow", 0, QApplication::UnicodeUTF8));
    action_Connect->setText(QApplication::translate("TrackEditor2Class", "&Connect to GPS Device ...", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("TrackEditor2Class", "E&xit", 0, QApplication::UnicodeUTF8));
    action_Read_Log->setText(QApplication::translate("TrackEditor2Class", "Read &Log", 0, QApplication::UnicodeUTF8));
    action_Save_Track->setText(QApplication::translate("TrackEditor2Class", "&Save Track", 0, QApplication::UnicodeUTF8));
    action_Save_Track_As->setText(QApplication::translate("TrackEditor2Class", "Save Track &As ...", 0, QApplication::UnicodeUTF8));
    action_Load_Track->setText(QApplication::translate("TrackEditor2Class", "&Load Track ...", 0, QApplication::UnicodeUTF8));
    action_Disconnect->setText(QApplication::translate("TrackEditor2Class", "&Disconnect", 0, QApplication::UnicodeUTF8));
    action_Start_Recording->setText(QApplication::translate("TrackEditor2Class", "Start &Recording", 0, QApplication::UnicodeUTF8));
    action_Stop_Recording->setText(QApplication::translate("TrackEditor2Class", "&Stop Recording", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("TrackEditor2Class", "File", 0, QApplication::UnicodeUTF8));
    menuTrack->setTitle(QApplication::translate("TrackEditor2Class", "Track", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrackEditor2Class: public Ui_TrackEditor2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKEDITOR_H
