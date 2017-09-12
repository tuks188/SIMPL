
#include <QtCore/QDebug>

// C Includes
#include <assert.h>
#include <stdlib.h>

// C++ Includes
#include <iostream>

// Qt Includes
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QtDebug>

// DREAM3DLib includes
#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/Common/FilterFactory.hpp"
#include "SIMPLib/Common/FilterManager.h"
#include "SIMPLib/Common/FilterPipeline.h"
#include "SIMPLib/FilterParameters/H5FilterParametersReader.h"
#include "SIMPLib/FilterParameters/JsonFilterParametersReader.h"
#include "SIMPLib/Plugin/ISIMPLibPlugin.h"
#include "SIMPLib/Plugin/SIMPLibPluginLoader.h"
#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/SIMPLibVersion.h"
#include "SIMPLib/Utilities/QMetaObjectUtilities.h"

int main(int argc, char const *argv[])
{
  // Register all the filters including trying to load those from Plugins
  FilterManager* fm = FilterManager::Instance();
  SIMPLibPluginLoader::LoadPluginFilters(fm);

  qDebug() << "Goodbye World";
  return 0;
}
