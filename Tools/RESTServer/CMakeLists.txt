project(RESTServer)








set(QtWebApp_SRCS
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandler.cpp     
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httprequesthandler.cpp
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandlerpool.cpp 
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpresponse.cpp
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpcookie.cpp                
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpsession.cpp
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpglobal.cpp                
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpsessionstore.cpp
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httplistener.cpp              
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/staticfilecontroller.cpp
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httprequest.cpp
  
  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/dualfilelogger.cpp 
  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/filelogger.cpp     
  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/logger.cpp         
  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/logmessage.cpp
)

set(QtWebApp_HDRS
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandler.h     
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httprequesthandler.h
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandlerpool.h 
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpresponse.h
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpcookie.h                
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpsession.h
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpglobal.h                
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httpsessionstore.h
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httplistener.h              
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/staticfilecontroller.h
  ${RESTServer_SOURCE_DIR}/QtWebApp/httpserver/httprequest.h

  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/dualfilelogger.h 
  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/filelogger.h     
  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/logger.h         
  ${RESTServer_SOURCE_DIR}/QtWebApp/logging/logmessage.h
)

QT5_WRAP_CPP( QtWebApp_MOC_SRCS ${QtWebApp_SRCS})
message(STATUS "QtWebApp_MOC_SRCS: ${QtWebApp_MOC_SRCS}")

set(RESTServer_SRCS
  ${RESTServer_SOURCE_DIR}/main.cpp
  ${QtWebApp_SRCS}
  ${QtWebApp_HDRS}
  ${QtWebApp_MOC_SRCS}
  )

set(install_dir "bin")
set(lib_install_dir "lib")

if(APPLE)
  get_property(DREAM3D_PACKAGE_DEST_PREFIX GLOBAL PROPERTY DREAM3D_PACKAGE_DEST_PREFIX)
  set(install_dir "${DREAM3D_PACKAGE_DEST_PREFIX}bin")
  set(lib_install_dir "${DREAM3D_PACKAGE_DEST_PREFIX}lib")
elseif(WIN32)
  set(install_dir ".")
  set(lib_install_dir ".")
endif()


add_executable(RESTServer ${RESTServer_SRCS})
target_link_libraries(RESTServer Qt5::Core Qt5::Network )

if(0)
BuildToolBundle(
    TARGET RESTServer
    SOURCES ${RESTServer_SRCS}
    DEBUG_EXTENSION ${EXE_DEBUG_EXTENSION}
    VERSION_MAJOR ${SIMPL_VER_MAJOR}
    VERSION_MINOR ${SIMPL_VER_MINOR}
    VERSION_PATCH ${SIMPL_VER_PATCH}
    BINARY_DIR    ${${PROJECT_NAME}_BINARY_DIR}
    LINK_LIBRARIES Qt5::Core Qt5::Network SIMPLib
    LIB_SEARCH_DIRS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMPONENT     Tools
    INSTALL_DEST  "${install_dir}"
    SOLUTION_FOLDER "Applications"
)
endif()



