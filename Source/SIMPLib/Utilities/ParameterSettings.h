/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef _parametersettings_h_
#define _parametersettings_h_

#include <QtCore/QJsonValue>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"

class SIMPLib_EXPORT ParameterSettings
{
public:
  virtual ~ParameterSettings();

  static int GetValueInt(const QJsonValue& json);
  static float GetValueFloat(const QJsonValue& json);
  static double GetValueDouble(const QJsonValue& json);

  static int GetMinInt(const QJsonValue& json);
  static float GetMinFloat(const QJsonValue& json);
  static double GetMinDouble(const QJsonValue& json);

  static int GetMaxInt(const QJsonValue& json);
  static float GetMaxFloat(const QJsonValue& json);
  static double GetMaxDouble(const QJsonValue& json);

  static void ReadJsonInt(const QJsonValue& json, int& value, int& min, int& max);
  static void ReadJsonFloat(const QJsonValue& json, float& value, float& min, float& max);
  static void ReadJsonDouble(const QJsonValue& json, double& value, double& min, double& max);

  static bool GetValueLocked(const QJsonValue& json);

  static QJsonValue ToJson(int value, bool locked = false);
  static QJsonValue ToJson(int value, int min, int max, bool locked = false);
  
  static QJsonValue ToJson(double value, bool locked = false);
  static QJsonValue ToJson(double value, double min, double max, bool locked = false);

  static bool IsLocked(const QJsonObject& json);
  static void SetLocked(bool locked, QJsonObject& json);

  static const QString TAG_VALUE;
  static const QString TAG_MINIMUM;
  static const QString TAG_MAXIMUM;
  static const QString TAG_LOCKED;

protected:
  ParameterSettings();

  static QString GetTagValue(const QJsonValue& json, QString tagName);
  
private:
  ParameterSettings(const ParameterSettings&); // Copy Constructor Not Implemented
  void operator=(const ParameterSettings&); // Operator '=' Not Implemented
};

#endif