/**
  @file
  @author Stefan Frings
*/

#include "NamesOfFiltersController.h"

#include "SIMPLib/Common/FilterManager.h"
#include "SIMPLib/Plugin/PluginManager.h"
#include "SIMPLib/Plugin/SIMPLibPluginLoader.h"

#include <QVariant>
#include <QDateTime>

#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

NamesOfFiltersController::NamesOfFiltersController()
{}

void NamesOfFiltersController::service(HttpRequest& request, HttpResponse& response)
{
  
  
  QString content_type = request.getHeader(QByteArray("content-type"));
  
  QJsonObject rootObj;
  
  response.setHeader("Content-Type", "application/json");

  
  if(content_type.compare("application/json") != 0)
  {
    // Form Error response
    rootObj["Error"] = "Content Type is not application/json"; 
    QJsonDocument jdoc(rootObj);
    
    response.write(jdoc.toJson(),true);
    return;
  }
  
  //   response.setCookie(HttpCookie("firstCookie","hello",600,QByteArray(),QByteArray(),QByteArray(),false,true));
  //   response.setCookie(HttpCookie("secondCookie","world",600));
  
  FilterManager* fm = FilterManager::Instance();
 
  
  FilterManager::Collection factories = fm->getFactories();

  QJsonArray filters;
  QJsonArray humanLabels;
  QMap<QString, IFilterFactory::Pointer>::const_iterator i = factories.constBegin();
  while (i != factories.constEnd()) 
  {
    filters.append(i.value()->getNameOfClass());
    humanLabels.append(i.value()->getFilterHumanLabel());
    ++i;
  }
  
  rootObj["FilterClassNames"] = filters;
  rootObj["FilterHumanLabels"] = humanLabels;
  QJsonDocument jdoc(rootObj);
  
  response.write(jdoc.toJson(),true);
}
