TEMPLATE = app
TARGET = trackeditor
QT += core \
    gui
HEADERS += CWintec.h \
    IDeviceIO.h \
    CommonTrackAttributes.h \
    CommonAttributes.h \
    trackFile.h \
    tk1File.h \
    gpxFile.h \
    Track.h \
    TrackCollection.h \
    TrackView.h \
    TrackPoint.h \
    DeviceData.h \
    TrackEditor.h
SOURCES += CWintec.cpp \
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
FORMS += DeviceDialog.ui \
    TrackEditor.ui \
    ProgressDialog.ui
RESOURCES += 
