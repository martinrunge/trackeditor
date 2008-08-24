TEMPLATE = app
TARGET = trackeditor
QT += core \
    gui
HEADERS += CommonTrackAttributes.h \
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
SOURCES += CommonTrackAttributes.cpp \
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
FORMS += TrackEditor.ui
RESOURCES += 
