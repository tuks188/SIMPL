project(RESTClient)

set(RESTClient_MOC_HDRS
  ${RESTClient_SOURCE_DIR}/Core/config.h
  ${RESTClient_SOURCE_DIR}/Core/mrestrequest.h
  ${RESTClient_SOURCE_DIR}/Core/mrestrequestmanager.h
  ${RESTClient_SOURCE_DIR}/Core/mrestrequestptr.h
  ${RESTClient_SOURCE_DIR}/Core/mrestrequestqueue.h
  ${RESTClient_SOURCE_DIR}/Core/restapiclient.h
  ${RESTClient_SOURCE_DIR}/Core/userptr.h

  ${RESTClient_SOURCE_DIR}/SIMPLRestClient/SIMPLClientRequest.h

)

set(RESTClient_HDRS

)

set(RESTClient_SRCS
  ${RESTClient_SOURCE_DIR}/main.cpp

  ${RESTClient_SOURCE_DIR}/Core/mrestrequest.cpp
  ${RESTClient_SOURCE_DIR}/Core/mrestrequestmanager.cpp
  ${RESTClient_SOURCE_DIR}/Core/mrestrequestqueue.cpp
  ${RESTClient_SOURCE_DIR}/Core/restapiclient.cpp
  ${RESTClient_SOURCE_DIR}/Core/config.cpp

  ${RESTClient_SOURCE_DIR}/SIMPLRestClient/SIMPLClientRequest.cpp
)

cmp_IDE_SOURCE_PROPERTIES( "RestClient" "${RESTClient_MOC_HDRS};${RESTClient_HDRS}" "${RESTClient_SRCS}" "0")

# --------------------------------------------------------------------
# and finally this will run moc:
QT5_WRAP_CPP( RESTClient_Generated_MOC_SRCS ${RESTClient_MOC_HDRS} )
set_source_files_properties( ${RESTClient_Generated_MOC_SRCS} PROPERTIES GENERATED TRUE)
# set_source_files_properties( ${RESTClient_Generated_MOC_SRCS} PROPERTIES HEADER_FILE_ONLY TRUE)

# --------------------------------------------------------------------
#-- Put the Qt generated files into their own group for IDEs
cmp_IDE_SOURCE_PROPERTIES( "Generated/Qt_Moc" "" "${RESTClient_Generated_MOC_SRCS}" "0")

set(RESTClient_SRCS_Compiled
  ${RESTClient_MOC_HDRS}
  ${RESTClient_SRCS}
  ${RESTClient_HDRS}
  ${RESTClient_Generated_MOC_SRCS}
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


BuildToolBundle(
    TARGET RESTClient
    SOURCES ${RESTClient_SRCS_Compiled}
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

