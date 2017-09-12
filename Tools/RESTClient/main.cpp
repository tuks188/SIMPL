/*******************************************************************************
Copyright (C) 2017 Milo Solutions
Contact: https://www.milosolutions.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/


#include <QCoreApplication>
#include <QLoggingCategory>

#include "Core/restapiclient.h"

#include "SIMPLRestClient/SIMPLClientRequest.h"

Q_LOGGING_CATEGORY(coreMain, "core.main")

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("BlueQuartz Software");
    app.setApplicationName("REST API Communication");

    qCInfo(coreMain) << "Application data set."
                 << "\n\tName:" << app.applicationName()
                 << "\n\tOrganisation:" << app.organizationName()
                 << "\n\tDomain:" << app.organizationDomain()
                 << "\n\tVersion:" << app.applicationVersion();

    // Crate rest api client.
    RestAPIClient client;


    // [1] ########  Simple example of usage, based on MrBabuQt project. ########.

//    Session session;
//    session.setClient(&client);

    // This is only example - we do not send any request here but we can see how use this classes.
    // session.registerUser(...);
    // session.login(...);
    // session.getUserInfo();

    // [1] ######################################################################


//    Weather weatherInLublin;

//    auto replyErrorLambda = [](const QString &error) {
//        // Do something with data
//        qCInfo(coreMain) << "Print error msg: " << error;
//    };

//    auto replyInfoLambda = [/*&weatherInLublin*/](const QString &cityName,
//            int humidity, int pressure, int temp) {

//        // do something with data
////        weatherInLublin.setCityName(cityName);
////        weatherInLublin.setHumidity(humidity);
////        weatherInLublin.setPressure(pressure);
////        weatherInLublin.setTemp(temp);
//    };

    QUrl serverUrl = QUrl("http://10.0.1.109:8080/api/v1/NumFilters");
    SIMPLClientRequest::Type msgType = SIMPLClientRequest::Type::Put;

    auto clientRequest = QSharedPointer<SIMPLClientRequest>::create(serverUrl, msgType);
//    QObject::connect(clientRequest.data(), &SIMPLClientRequest::replyError, replyErrorLambda);
//    QObject::connect(clientRequest.data(), &SIMPLClientRequest::replyInfo, replyInfoLambda);

    // send request
    client.send(clientRequest);

    return app.exec();
}
