/* ============================================================================
 * Copyright (c) 2017 BlueQuartz Softwae, LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the names of any of the BlueQuartz Software contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <QCoreApplication>

#include <QtCore/QJsonDocument>

#include "SIMPLRequestMapper.h"

#include "QtWebApp/logging/filelogger.h"

#include "SIMPLRestServer/Controllers/ApiNotFoundController.h"
#include "SIMPLRestServer/Controllers/ExecutePipelineController.h"
#include "SIMPLRestServer/Controllers/ListFilterParametersController.h"
#include "SIMPLRestServer/Controllers/LoadedPluginsController.h"
#include "SIMPLRestServer/Controllers/NamesOfFiltersController.h"
#include "SIMPLRestServer/Controllers/NumFiltersController.h"
#include "SIMPLRestServer/Controllers/PluginInfoController.h"
#include "SIMPLRestServer/Controllers/PreflightPipelineController.h"

/** Redirects log messages to a file */
extern FileLogger* logger;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SIMPLRequestMapper::SIMPLRequestMapper(QObject* parent)
: HttpRequestHandler(parent)
{
  qDebug("SIMPLRequestMapper: created");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SIMPLRequestMapper::~SIMPLRequestMapper()
{
  qDebug("SIMPLRequestMapper: deleted");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLRequestMapper::service(HttpRequest& request, HttpResponse& response)
{
  QMultiMap<QByteArray, QByteArray> headerMap = request.getHeaderMap();

  QByteArray path = request.getPath();
  qDebug("SIMPLRequestMapper: path=%s", path.data());

  // For the following pathes, each request gets its own new instance of the related controller.

  if(path.startsWith("/api/v1/ExecutePipeline"))
  {
    ExecutePipelineController().service(request, response);
  }
  else if(path.startsWith("/api/v1/ListFilterParameters"))
  {
    ListFilterParametersController().service(request, response);
  }
  else if(path.startsWith("/api/v1/LoadedPlugins"))
  {
    LoadedPluginsController().service(request, response);
  }
  else if(path.startsWith("/api/v1/NamesOfFilters"))
  {
    NamesOfFiltersController().service(request, response);
  }
  else if(path.startsWith("/api/v1/NumFilters"))
  {
    NumFiltersController().service(request, response);
  }
  else if(path.startsWith("/api/v1/PluginInformation"))
  {
    PluginInfoController().service(request, response);
  }
  else if(path.startsWith("/api/v1/PreflightPipeline"))
  {
    PreflightPipelineController().service(request, response);
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
