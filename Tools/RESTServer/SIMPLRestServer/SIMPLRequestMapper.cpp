/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>

#include <QtCore/QJsonDocument>


#include "SIMPLRequestMapper.h"

#include "QtWebApp/logging/filelogger.h"

#include "SIMPLRestServer/Controllers/ApiNotFoundController.h"   
#include "SIMPLRestServer/Controllers/ExecutePipelineController.h"   
#include "SIMPLRestServer/Controllers/NumFiltersController.h"
#include "SIMPLRestServer/Controllers/ListFilterParametersController.h"
#include "SIMPLRestServer/Controllers/PluginInfoController.h"
#include "SIMPLRestServer/Controllers/LoadedPluginsController.h"
#include "SIMPLRestServer/Controllers/PreflightPipelineController.h"
#include "SIMPLRestServer/Controllers/NamesOfFiltersController.h"

/** Redirects log messages to a file */
extern FileLogger* logger;

SIMPLRequestMapper::SIMPLRequestMapper(QObject* parent)
  :HttpRequestHandler(parent)
{
  qDebug("SIMPLRequestMapper: created");
}


SIMPLRequestMapper::~SIMPLRequestMapper()
{
  qDebug("SIMPLRequestMapper: deleted");
}


void SIMPLRequestMapper::service(HttpRequest& request, HttpResponse& response)
{
  QMultiMap<QByteArray, QByteArray> headerMap = request.getHeaderMap();
  
  QByteArray path=request.getPath();
  qDebug("SIMPLRequestMapper: path=%s",path.data());
  
  
  // For the following pathes, each request gets its own new instance of the related controller.
  
  if (path.startsWith("/api/v1/ExecutePipeline"))
  {
    ExecutePipelineController().service(request, response);
  }
  else if (path.startsWith("/api/v1/ListFilterParameters"))
  {
    NumFiltersController().service(request, response);
  }
  else if (path.startsWith("/api/v1/LoadedPlugins"))
  {
    ListFilterParametersController().service(request, response);
  }
  else if (path.startsWith("/api/v1/NamesOfFilters"))
  {
    PluginInfoController().service(request, response);
  }
  else if (path.startsWith("/api/v1/NumFilters"))
  {
    LoadedPluginsController().service(request, response);
  }
  else if (path.startsWith("/api/v1/PluginInformation"))
  {
    PreflightPipelineController().service(request, response);
  }
  else if (path.startsWith("/api/v1/PreflightPipeline"))
  {
    NamesOfFiltersController().service(request, response);
  }
  // All other pathes are mapped to the static file controller.
  // In this case, a single instance is used for multiple requests.
  else
  {
    ApiNotFoundController().service(request, response);
  }
  
  qDebug("SIMPLRequestMapper: finished request");
  
  // Clear the log buffer
  //    if (logger)
  //    {
  //       logger->clear();
  //    }
}
