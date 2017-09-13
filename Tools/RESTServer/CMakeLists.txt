project(SIMPLRestServer)

INCLUDE_DIRECTORIES(${SIMPLRestServer_SOURCE_DIR})


set(QtWebApp_SRCS
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandler.cpp     
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httprequesthandler.cpp
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandlerpool.cpp 
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpresponse.cpp
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpcookie.cpp                
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpsession.cpp
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpglobal.cpp                
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpsessionstore.cpp
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httplistener.cpp              
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/staticfilecontroller.cpp
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httprequest.cpp
  
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/dualfilelogger.cpp 
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/filelogger.cpp     
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/logger.cpp         
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/logmessage.cpp
)

set(QtWebApp_HDRS
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandler.h     
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httprequesthandler.h
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandlerpool.h 
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpresponse.h
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpcookie.h                
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpsession.h
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpglobal.h                
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpsessionstore.h
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httplistener.h              
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/staticfilecontroller.h
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httprequest.h

  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/dualfilelogger.h 
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/filelogger.h     
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/logger.h         
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/logmessage.h
)

set(SIMPLRestServerController_SRCS
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/SIMPLRequestMapper.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/PipelineListener.cpp

  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/NumFiltersController.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/V1RequestMapper.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/ExecutePipelineController.cpp      
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/NumFiltersController.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/ListFilterParametersController.cpp 
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/PluginInfoController.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/LoadedPluginsController.cpp        
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/PreflightPipelineController.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/NamesOfFiltersController.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/ApiNotFoundController.cpp
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/SIMPLStaticFileController.cpp
)

set(SIMPLRestServerController_HDRS
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/SIMPLRequestMapper.h
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/PipelineListener.h

  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/V1RequestMapper.h
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/ExecutePipelineController.h      
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/NumFiltersController.h
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/ListFilterParametersController.h 
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/PluginInfoController.h
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/LoadedPluginsController.h        
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/PreflightPipelineController.h
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/NamesOfFiltersController.h
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/ApiNotFoundController.h
  ${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer/V1Controllers/SIMPLStaticFileController.h
)

QT5_WRAP_CPP( QtWebApp_MOC_SRCS 
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandler.h     
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httprequesthandler.h
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpconnectionhandlerpool.h 
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httpsessionstore.h
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/httplistener.h              
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/httpserver/staticfilecontroller.h

  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/dualfilelogger.h 
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/filelogger.h     
  ${SIMPLRestServer_SOURCE_DIR}/QtWebApp/logging/logger.h

  ${SIMPLRestServerController_HDRS}
  )

set(SIMPLRestServer_SRCS
  ${SIMPLRestServer_SOURCE_DIR}/main.cpp
  ${SIMPLRestServerController_SRCS}
  ${SIMPLRestServerController_HDRS}
  ${QtWebApp_SRCS}
  ${QtWebApp_HDRS}
  ${QtWebApp_MOC_SRCS}
  )

configure_file(${SIMPLRestServer_SOURCE_DIR}/SIMPLRestServer.ini
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SIMPLRestServer.ini )

add_custom_target(DocRootFolderCopy ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${SIMPLRestServer_SOURCE_DIR}/docroot
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/docroot/
            COMMENT "Copying Data Folder into Binary Directory")
set_target_properties(DocRootFolderCopy PROPERTIES FOLDER ZZ_COPY_FILES)


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

if(0)
add_executable(SIMPLRestServer ${SIMPLRestServer_SRCS})
target_link_libraries(SIMPLRestServer Qt5::Core Qt5::Network SIMPLib)
else()

BuildToolBundle(
    TARGET SIMPLRestServer
    SOURCES ${SIMPLRestServer_SRCS}
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



