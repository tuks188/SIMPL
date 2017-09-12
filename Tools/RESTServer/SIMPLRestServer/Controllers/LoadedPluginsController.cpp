/**
  @file
  @author Stefan Frings
*/

#include "LoadedPluginsController.h"

#include "SIMPLib/Common/FilterManager.h"
#include "SIMPLib/Plugin/PluginManager.h"
#include "SIMPLib/Plugin/SIMPLibPluginLoader.h"

#include <QVariant>
#include <QDateTime>

#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
LoadedPluginsController::LoadedPluginsController()
{}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void LoadedPluginsController::service(HttpRequest& request, HttpResponse& response)
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
  
  PluginManager* pm = PluginManager::Instance();
   
  QJsonArray pluginNames;
  QVector<ISIMPLibPlugin*> plugins = pm->getPluginsVector();
  foreach(ISIMPLibPlugin* plugin, plugins)
  {
    pluginNames.append(plugin->getPluginName());  
  }
  rootObj["Plugin Names"] = pluginNames;
    
  QJsonDocument jdoc(rootObj);
  
  response.write(jdoc.toJson(),true);
}
