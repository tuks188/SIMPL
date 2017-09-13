/**
  @file
  @author Stefan Frings
*/

#include "PreflightPipelineController.h"

#include "SIMPLib/Common/FilterManager.h"
#include "SIMPLib/Common/FilterPipeline.h"
#include "SIMPLib/Plugin/PluginManager.h"
#include "SIMPLib/Plugin/SIMPLibPluginLoader.h"

#include <QVariant>
#include <QDateTime>

#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

#include "SIMPLRestServer/PipelineListener.h"

PreflightPipelineController::PreflightPipelineController()
{}

void PreflightPipelineController::service(HttpRequest& request, HttpResponse& response)
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

  QString requestBody = request.getBody();
  QJsonDocument requestDoc = QJsonDocument::fromJson(requestBody.toUtf8());
  QJsonObject requestObj = requestDoc.object();

  QJsonObject pipelineObj = requestObj["Pipeline"].toObject();
  FilterPipeline::Pointer pipeline = FilterPipeline::FromJson(pipelineObj);
  PipelineListener* listener = new PipelineListener(nullptr);
  pipeline->addMessageReceiver(listener);
  pipeline->preflightPipeline();
  
  //   response.setCookie(HttpCookie("firstCookie","hello",600,QByteArray(),QByteArray(),QByteArray(),false,true));
  //   response.setCookie(HttpCookie("secondCookie","world",600));
  
  std::vector<PipelineMessage> errorMessages = listener->getErrorMessages();
  bool completed = (errorMessages.size() == 0);
  if(!completed)
  {
      QJsonArray errors;
      int numErrors = errorMessages.size();
      for(int i = 0; i < numErrors; i++)
      {
          QJsonObject error;
          error["Code"] = errorMessages[i].generateErrorString();
          error["Message"] = errorMessages[i].getText();
          error["FilterHumanLabel"] = errorMessages[i].getFilterHumanLabel();
          error["FilterIndex"] = errorMessages[i].getPipelineIndex();

          errors.push_back(error);
      }

      rootObj["Errors"] = errors;
  }

  delete listener;
  rootObj["Completed"] = completed;
  QJsonDocument jdoc(rootObj);
  
  response.write(jdoc.toJson(),true);
}
