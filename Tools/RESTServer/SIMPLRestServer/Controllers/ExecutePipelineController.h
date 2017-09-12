
#ifndef ExecutePipelineController_H_
#define ExecutePipelineController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class ExecutePipelineController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(ExecutePipelineController)
public:

    /** Constructor */
    ExecutePipelineController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // ExecutePipelineController_H_
