
#ifndef ApiNotFoundController_H_
#define ApiNotFoundController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class ApiNotFoundController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(ApiNotFoundController)
public:

    /** Constructor */
    ApiNotFoundController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // ApiNotFoundController_H_
