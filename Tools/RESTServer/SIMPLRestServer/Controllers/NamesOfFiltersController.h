
#ifndef NamesOfFiltersController_H_
#define NamesOfFiltersController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class NamesOfFiltersController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(NamesOfFiltersController)
public:

    /** Constructor */
    NamesOfFiltersController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // NamesOfFiltersController_H_
