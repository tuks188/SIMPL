
#ifndef NumFiltersController_H_
#define NumFiltersController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class NumFiltersController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(NumFiltersController)
public:

    /** Constructor */
    NumFiltersController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // NumFiltersController_H_
