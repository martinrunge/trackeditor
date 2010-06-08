
find_package ( Qt4 REQUIRED )

set( SOURCES  qextserialbase.cpp  
              qextserialenumerator.cpp  
              qextserialport.cpp )

set( MOC_HEADERS  qextserialbase.h
                  qextserialport.h )

              
if(UNIX)
  set( SOURCES ${SOURCES} posix_qextserialport.cpp )
  set( MOC_HEADERS ${MOC_HEADERS} posix_qextserialport.h )
else(UNIX)
  set( SOURCES ${SOURCES} win_qextserialport.cpp )
  set( MOC_HEADERS ${MOC_HEADERS} win_qextserialport.h )
endif(UNIX)              
               
                  
include ( ${QT_USE_FILE} )
qt4_wrap_cpp( MOC_SOURCES ${MOC_HEADERS} )
add_definitions( ${QT4_DEFINITIONS} )

link_directories( ${QT_LIB_DIR} )

message(STATUS "Compile definitions in subdir: " ${COMPILE_DEFINITIONS})

add_library( qextserialport STATIC ${SOURCES} ${MOC_SOURCES} )
                  
