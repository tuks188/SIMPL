
#ifndef LoadedPluginsController_H_
#define LoadedPluginsController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class LoadedPluginsController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(LoadedPluginsController)
public:

    /** Constructor */
    LoadedPluginsController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // LoadedPluginsController_H_
