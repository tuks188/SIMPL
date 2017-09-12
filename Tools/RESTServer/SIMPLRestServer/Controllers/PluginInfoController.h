
#ifndef PluginInfoController_H_
#define PluginInfoController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class PluginInfoController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(PluginInfoController)
public:

    /** Constructor */
    PluginInfoController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // PluginInfoController_H_
