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

#include <QtCore/QFile>

#include "Core/SIMPLRestClient.h"

#include "SIMPLRestClient/SIMPLClientRequest.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("BlueQuartz Software");
    app.setApplicationName("REST API Communication");

    QUrl mikeUrl = QUrl("http://10.0.1.142:8080/");
    QUrl matthewUrl = QUrl("http://10.0.1.109:8080/");

    // Create the SIMPL Rest client
    SIMPLRestClient* client = new SIMPLRestClient(matthewUrl);

    auto finishedLambda = [&app] {
        app.quit();
    };

    QObject::connect(client, &SIMPLRestClient::finished, finishedLambda);


//    // "API Not Found" Test
//    {
//      client->sendAPINotFoundRequest(30000);
//    }

    // "Execute Pipeline" Test
    {
      QJsonObject pipelineObj = client->extractPipelineFromFile("/Users/joeykleingers/Desktop/Granta_Synthetic_Pipeline.json");
      client->sendExecutePipelineRequest(pipelineObj, 30000);
    }

//    // "List Filter Parameters" Test
//    {
//      QJsonObject filterNameObj;
//      filterNameObj.insert("ClassName", "DataContainerReader");
//      client->sendListFilterParametersRequest(filterNameObj, 30000);
//    }

//    // "Loaded Plugins" Test
//    {
//      client->sendLoadedPluginsRequest(30000);
//    }

//    // "Names of Filters" Test
//    {
//      client->sendNamesOfFiltersRequest(30000);
//    }

//    // "Number Of Filters" Test
//    {
//      client->sendNumberOfFiltersRequest(30000);
//    }

//    // "Plugin Information" Test
//    {
//      client->sendPluginInformationRequest(30000);
//    }

//    // "Preflight Pipeline" Test
//    {
//      client->sendPreflightPipelineRequest(30000);
//    }

    return app.exec();
}
