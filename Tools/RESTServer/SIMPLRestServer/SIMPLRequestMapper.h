

#ifndef SIMPLSIMPLRequestMapper_H_
#define SIMPLSIMPLRequestMapper_H_


#include <QtCore/QObject>

#include "QtWebApp/httpserver/httprequesthandler.h"


/**
  The request mapper dispatches incoming HTTP requests to controller classes
  depending on the requested path.
*/

class SIMPLRequestMapper : public HttpRequestHandler 
{
    Q_OBJECT
    Q_DISABLE_COPY(SIMPLRequestMapper)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    SIMPLRequestMapper(QObject* parent=0);

    /**
      Destructor.
    */
    virtual ~SIMPLRequestMapper();

    /**
      Dispatch incoming HTTP requests to different controllers depending on the URL.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(HttpRequest& request, HttpResponse& response);

};

#endif // SIMPLSIMPLRequestMapper_H_
