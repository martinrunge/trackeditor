TEMPLATE = app
TARGET = trackeditor
QT += core \
    gui
HEADERS += CDiagramsLayout.h \
    csettingsdlg.h \
    CDiagramSettings.h \
    PlotData.h \
    plotWidget.h \
    IDeviceIO.h \
    CWintec.h \
    TrackCollection.h \
    TrackEditor.h \
    TrackView.h
SOURCES += CDiagramsLayout.cpp \
    csettingsdlg.cpp \
    CDiagramSettings.cpp \
    PlotData.cpp \
    plotWidget.cpp \
    CWintec.cpp \
    IDeviceIO.cpp \
    CommonTrackAttributes.cpp \
    CommonAttributes.cpp \
    trackFile.cpp \
    tk1File.cpp \
    gpxFile.cpp \
    Track.cpp \
    TrackCollection.cpp \
    TrackView.cpp \
    TrackPoint.cpp \
    DeviceData.cpp \
    main.cpp \
    TrackEditor.cpp
FORMS += csettingsdlg.ui \
    ProgressDialog.ui \
    DeviceDialog.ui \
    TrackEditor.ui \
    diagramSettings.ui
RESOURCES += trackeditor.qrc
LIBS += -lproj \
    -lqwt-qt4
