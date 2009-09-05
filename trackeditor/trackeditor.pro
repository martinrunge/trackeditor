QT += core \
    gui \
    dbus
HEADERS += CMarker.h \
    DeviceListWidgetItem.h \
    CSerialPortSettings.h \
    CGenericSerialDevice.h \
    CBluetoothDevice.h \
    CUsbDevice.h \
    CDeviceDialog.h \
    CQuantitiesConfig.h \
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
    TrackView.h \
    qextserialport/qextserialbase.h \
    qextserialport/qextserialport.h \
    CAnimation.h
SOURCES += CMarker.cpp \
    DeviceListWidgetItem.cpp \
    CSerialPortSettings.cpp \
    CDeviceDialog.cpp \
    CGenericSerialDevice.cpp \
    CBluetoothDevice.cpp \
    CUsbDevice.cpp \
    CQuantitiesConfig.cpp \
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
    TrackEditor.cpp \
    qextserialport/qextserialbase.cpp \
    qextserialport/qextserialport.cpp \
    CAnimation.cpp
FORMS += serialwidget.ui \
    bluetoothwidget.ui \
    usbwidget.ui \
    CQuantitiesConfig.ui \
    CUnitConfig.ui \
    diagramSettings.ui \
    csettingsdlg.ui \
    ProgressDialog.ui \
    DeviceDialog.ui \
    TrackEditor.ui \
    diagramSettings.ui
RESOURCES += trackeditor.qrc \
    trackeditor.qrc
unix:HEADERS += qextserialport/posix_qextserialport.h
unix:SOURCES += qextserialport/posix_qextserialport.cpp
unix:DEFINES += _TTY_POSIX_
win32:HEADERS += qextserialport/win_qextserialport.h
win32:SOURCES += qextserialport/win_qextserialport.cpp
win32:DEFINES += _TTY_WIN_
LIBS += -lproj \
    -lqwt-qt4
TARGET = trackeditor
