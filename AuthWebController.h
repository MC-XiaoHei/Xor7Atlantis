#ifndef AuthWebController_H
#define AuthWebController_H

#include "stable.h"

using namespace stefanfrings;

class AuthWebController : public HttpRequestHandler {
    Q_OBJECT
public:
    AuthWebController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
signals:
    void over(bool state,QString data);
};

#endif // AuthWebController_H
