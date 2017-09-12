/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>

#include <QtCore/QJsonDocument>


#include "SIMPLRequestMapper.h"
#include "filelogger.h"
#include "staticfilecontroller.h"
#include "controller/dumpcontroller.h"
#include "controller/templatecontroller.h"
#include "controller/formcontroller.h"
#include "controller/fileuploadcontroller.h"
#include "controller/sessioncontroller.h"

/** Redirects log messages to a file */
extern FileLogger* logger;

/** Controller for static files */
extern StaticFileController* staticFileController;

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
    
    QByteArray method = request.getMethod();
    
    QString content_type = request.getHeader(QByteArray("content-type"));
    
    if(content_type.compare("application/json") == 0)
    {
      QByteArray jsonRequest = request.getBody();
      QJsonParseError parseError;
      QJsonDocument requestJson = QJsonDocument::fromJson(jsonRequest, &parseError);
       
               staticFileController->service(request, response);

    }
    QByteArray path=request.getPath();
    qDebug("SIMPLRequestMapper: path=%s",path.data());
    
    
    // For the following pathes, each request gets its own new instance of the related controller.

    if (path.startsWith("/dump"))
    {
        DumpController().service(request, response);
    }

    else if (path.startsWith("/template"))
    {
        TemplateController().service(request, response);
    }

    else if (path.startsWith("/form"))
    {
        FormController().service(request, response);
    }

    else if (path.startsWith("/file"))
    {
        FileUploadController().service(request, response);
    }

    else if (path.startsWith("/session"))
    {
        SessionController().service(request, response);
    }

    // All other pathes are mapped to the static file controller.
    // In this case, a single instance is used for multiple requests.
    else
    {
        staticFileController->service(request, response);
    }

    qDebug("SIMPLRequestMapper: finished request");

    // Clear the log buffer
    if (logger)
    {
       logger->clear();
    }
}
