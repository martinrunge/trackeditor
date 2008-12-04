TEMPLATE = app
TARGET = trackeditor
QT += core \
    gui
HEADERS += PlotData.h \
    plotWidget.h \
    IDeviceIO.h \
    CWintec.h \
    TrackCollection.h \
    TrackEditor.h \
    TrackView.h
SOURCES += PlotData.cpp \
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
FORMS += ProgressDialog.ui \
    DeviceDialog.ui \
    TrackEditor.ui \
    ProgressDialog.ui
RESOURCES += 
LIBS += -lproj \
    -lqwt-qt4
