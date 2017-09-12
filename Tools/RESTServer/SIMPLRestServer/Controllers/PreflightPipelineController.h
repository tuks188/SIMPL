
#ifndef PreflightPipelineController_H_
#define PreflightPipelineController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class PreflightPipelineController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(PreflightPipelineController)
public:

    /** Constructor */
    PreflightPipelineController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // PreflightPipelineController_H_
