TEMPLATE = app
TARGET = trackeditor
QT += core \
    gui
HEADERS += CQuantitiesConfig.h \
    CUnitConfig.h \
    CSettings.h \
    CDiagramsLayout.h \
    csettingsdlg.h \
    CDiagramSettings.h \
    PlotData.h \
    plotWidget.h \
    IDeviceIO.h \
    CWintec.h \
    TrackCollection.h \
    TrackEditor.h \
    TrackView.h
SOURCES += CQuantitiesConfig.cpp \
    CUnitConfig.cpp \
    CSettings.cpp \
    CDiagramsLayout.cpp \
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
FORMS += CQuantitiesConfig.ui \
    CUnitConfig.ui \
    diagramSettings.ui \
    csettingsdlg.ui \
    ProgressDialog.ui \
    DeviceDialog.ui \
    TrackEditor.ui \
    diagramSettings.ui
RESOURCES += trackeditor.qrc \
    trackeditor.qrc
LIBS += -lproj \
    -lqwt-qt4
