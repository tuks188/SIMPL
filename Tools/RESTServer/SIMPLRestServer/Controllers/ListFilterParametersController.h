
#ifndef ListFilterParametersController_H_
#define ListFilterParametersController_H_

#include "QtWebApp/httpserver/httprequest.h"
#include "QtWebApp/httpserver/httpresponse.h"
#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  This controller dumps the received HTTP request in the response.
*/

class ListFilterParametersController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(ListFilterParametersController)
public:

    /** Constructor */
    ListFilterParametersController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // ListFilterParametersController_H_
