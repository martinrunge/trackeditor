cmake_minimum_required (VERSION 2.6)
project (trackeditor)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package ( Qt4 REQUIRED )
find_package ( Qwt5 REQUIRED )

add_definitions( ${QT4_DEFINITIONS} )

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS _TTY_POSIX_ ) 
add_subdirectory( qextserialport )

set( SOURCES  CAboutDialog.cpp
              CMarker.cpp
              csettingsdlg.cpp
              IDeviceIO.cpp
              TrackEditor.cpp
              CAnimation.cpp            
              CommonAttributes.cpp       
              CUnitConfig.cpp           
              main.cpp             
              trackFile.cpp
              CBluetoothDevice.cpp      
              CommonTrackAttributes.cpp  
              CUsbDevice.cpp            
              PlotData.cpp         
              TrackPoint.cpp
              CDeviceDialog.cpp         
              CQuantitiesConfig.cpp      
              CWintec.cpp               
              plotWidget.cpp       
              TrackView.cpp
              CDiagramSettings.cpp
              CScrolledTrackView.cpp     
              DeviceData.cpp            
              tk1File.cpp
              CDiagramsLayout.cpp       
              CSerialPortSettings.cpp    
              DeviceListWidgetItem.cpp  
              TrackCollection.cpp
              CGenericSerialDevice.cpp  
              CSettings.cpp              
              gpxFile.cpp               
              Track.cpp )

set( MOC_HEADERS  CAboutDialog.h
                  CScrolledTrackView.h
                  CMarker.h
                  DeviceListWidgetItem.h
                  CSerialPortSettings.h
                  CGenericSerialDevice.h
                  CBluetoothDevice.h
                  CUsbDevice.h
                  CDeviceDialog.h
                  CQuantitiesConfig.h
                  CUnitConfig.h
                  CSettings.h
                  CDiagramsLayout.h
                  csettingsdlg.h
                  CDiagramSettings.h
                  PlotData.h
                  plotWidget.h
                  IDeviceIO.h
                  CWintec.h
                  TrackCollection.h
                  TrackEditor.h
                  TrackView.h
#                  qextserialport/qextserialbase.h
#                  qextserialport/qextserialport.h
                  CAnimation.h )
 
SET(UIS  AboutDialog.ui      
         CQuantitiesConfig.ui  
         CUnitConfig.ui   
         diagramSettings.ui  
         serialwidget.ui  
         usbwidget.ui
         bluetoothwidget.ui  
         csettingsdlg.ui       
         DeviceDialog.ui  
         ProgressDialog.ui   
         TrackEditor.ui )

QT4_WRAP_UI(UIS_H ${UIS})


# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${Qwt5_INCLUDE_DIR} )

set (QT_USE_QTXML true )
set (QT_USE_QTDBUS true )
include ( ${QT_USE_FILE} )
qt4_wrap_cpp( MOC_SOURCES ${MOC_HEADERS} )


link_directories( ${QT_LIB_DIR} qextserialport )

add_executable( trackeditor ${SOURCES} ${MOC_SOURCES} ${UIS_H})
target_link_libraries( trackeditor qextserialport proj ${QT_LIBRARIES} ${Qwt5-Qt4_LIBRARY} )
 

install(TARGETS   trackeditor
        DESTINATION  bin)
