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
#include "V1RequestMapper.h"


#include <QtCore/QCoreApplication>
#include <QtCore/QJsonDocument>


#include "QtWebApp/logging/filelogger.h"

#include "SIMPLRestServer/V1Controllers/ApiNotFoundController.h"
#include "SIMPLRestServer/V1Controllers/ExecutePipelineController.h"
#include "SIMPLRestServer/V1Controllers/ListFilterParametersController.h"
#include "SIMPLRestServer/V1Controllers/LoadedPluginsController.h"
#include "SIMPLRestServer/V1Controllers/NamesOfFiltersController.h"
#include "SIMPLRestServer/V1Controllers/NumFiltersController.h"
#include "SIMPLRestServer/V1Controllers/PluginInfoController.h"
#include "SIMPLRestServer/V1Controllers/PreflightPipelineController.h"
#include "SIMPLRestServer/V1Controllers/SIMPLStaticFileController.h"

/** Redirects log messages to a file */
extern FileLogger* logger;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
V1RequestMapper::V1RequestMapper(QObject* parent)
: HttpRequestHandler(parent)
{
  qDebug("V1RequestMapper: created");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
V1RequestMapper::~V1RequestMapper()
{
  qDebug("V1RequestMapper: deleted");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void V1RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
  QMultiMap<QByteArray, QByteArray> headerMap = request.getHeaderMap();

  QString path(request.getPath());
  qDebug() << "V1RequestMapper: path=" << path.data();

  // For the following pathes, each request gets its own new instance of the related controller.

  if(path.endsWith(ExecutePipelineController::EndPoint()))
  {
    ExecutePipelineController().service(request, response);
  }
  else if(path.endsWith(ListFilterParametersController::EndPoint()))
  {
    ListFilterParametersController().service(request, response);
  }
  else if(path.endsWith(LoadedPluginsController::EndPoint()))
  {
    LoadedPluginsController().service(request, response);
  }
  else if(path.endsWith(NamesOfFiltersController::EndPoint()))
  {
    NamesOfFiltersController().service(request, response);
  }
  else if(path.endsWith(NumFiltersController::EndPoint()))
  {
    NumFiltersController().service(request, response);
  }
  else if(path.endsWith(PluginInfoController::EndPoint()))
  {
    PluginInfoController().service(request, response);
  }
  else if(path.endsWith(PreflightPipelineController::EndPoint()))
  {
    PreflightPipelineController().service(request, response);
  }
  // All other pathes are mapped to the static file controller.
  // In this case, a single instance is used for multiple requests.
  else
  {
    SIMPLStaticFileController::Instance()->service(request, response);
    //ApiNotFoundController().service(request, response);
  }

  qDebug("V1RequestMapper: finished request");

  // Clear the log buffer
  //    if (logger)
  //    {
  //       logger->clear();
  //    }
}
