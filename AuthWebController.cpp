#include "AuthWebController.h"

AuthWebController::AuthWebController(QObject* parent)
    : HttpRequestHandler(parent) {
}

void AuthWebController::service(HttpRequest &request, HttpResponse &response) {
    response.write("<!DOCTYPE html>"
                   "<html lang=\" en\">"
                   "<head>"
                   "    <meta charset=\"utf-8\">"
                   "    <title>Xor 7 Argon 微软身份验证</title>"
                   "</head>"
                   "<body>"
                   "    <nav align=center>"
                   "        <h3 align=center>浏览器侧身份验证已经结束，您可以放心的关闭此窗口。</h3>"
                   "    </nav>"
                   "</body>"
                   "</html>",true);
    QString referer=request.getHeader("referer");
    if(referer.contains("localhost")){
        try {
            if(referer.contains("&error_description"))
                emit over(false,referer.split("error=")[1].split("&error_description")[0]);
            else
                emit over(true,referer.split("code=")[1]);
        } catch (...) {
            emit over(false,"X7A-AuthCore-UnknownException");
        }
    }
}
