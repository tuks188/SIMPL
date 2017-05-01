#include "SIMPLib/Utilities/ParameterSettings.h"

#include <limits>

const QString ParameterSettings::TAG_VALUE = "Value";
const QString ParameterSettings::TAG_MINIMUM = "Min";
const QString ParameterSettings::TAG_MAXIMUM = "Max";

const QString ParameterSettings::TAG_LOCKED = "Locked";

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ParameterSettings::ParameterSettings()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ParameterSettings::~ParameterSettings()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString ParameterSettings::GetTagValue(const QJsonValue& json, QString tagName)
{
  // Make sure the json value is a string before parsing
  if(json.isString())
  {
    QString jsonStr = json.toString();
    jsonStr.remove(" ");
    QStringList valueSeg = jsonStr.split(",");

    for(int i = 0; i < valueSeg.size(); i++)
    {
      if(valueSeg[i].startsWith(tagName + ":", Qt::CaseInsensitive))
      {
        return valueSeg[i].remove(tagName + ":", Qt::CaseInsensitive);
      }
    }
  }

  return "";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int ParameterSettings::GetValueInt(const QJsonValue& json)
{
  if(json.isDouble())
  {
    return json.toInt();
  }
  
  QString valueStr = GetTagValue(json, TAG_VALUE);
  int value = valueStr.toInt();

  return value;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
float ParameterSettings::GetValueFloat(const QJsonValue& json)
{
  if(json.isDouble())
  {
    return json.toDouble();
  }

  QString valueStr = GetTagValue(json, TAG_VALUE);
  float value = valueStr.toFloat();

  return value;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
double ParameterSettings::GetValueDouble(const QJsonValue& json)
{
  if(json.isDouble())
  {
    return json.toDouble();
  }

  QString valueStr = GetTagValue(json, TAG_VALUE);
  double value = valueStr.toDouble();

  return value;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int ParameterSettings::GetMinInt(const QJsonValue& json)
{
  int min = std::numeric_limits<int>::min();

  bool ok;
  QString valueStr = GetTagValue(json, TAG_MINIMUM);
  int value = valueStr.toInt(&ok);

  if(ok)
  {
    min = value;
  }

  return min;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
float ParameterSettings::GetMinFloat(const QJsonValue& json)
{
  float min = std::numeric_limits<float>::min();

  bool ok;
  QString valueStr = GetTagValue(json, TAG_MINIMUM);
  float value = valueStr.toFloat(&ok);

  if(ok)
  {
    min = value;
  }

  return min;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
double ParameterSettings::GetMinDouble(const QJsonValue& json)
{
  double min = std::numeric_limits<double>::min();

  bool ok;
  QString valueStr = GetTagValue(json, TAG_MINIMUM);
  double value = valueStr.toDouble(&ok);

  if(ok)
  {
    min = value;
  }

  return min;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int ParameterSettings::GetMaxInt(const QJsonValue& json)
{
  int max = std::numeric_limits<int>::max();

  bool ok;
  QString valueStr = GetTagValue(json, TAG_MAXIMUM);
  int value = valueStr.toInt(&ok);

  if(ok)
  {
    max = value;
  }

  return max;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
float ParameterSettings::GetMaxFloat(const QJsonValue& json)
{
  float max = std::numeric_limits<float>::max();

  bool ok;
  QString valueStr = GetTagValue(json, TAG_MAXIMUM);
  float value = valueStr.toFloat(&ok);

  if(ok)
  {
    max = value;
  }

  return max;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
double ParameterSettings::GetMaxDouble(const QJsonValue& json)
{
  double max = std::numeric_limits<double>::max();

  bool ok;
  QString valueStr = GetTagValue(json, TAG_MAXIMUM);
  double value = valueStr.toDouble(&ok);

  if(ok)
  {
    max = value;
  }

  return max;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ParameterSettings::ReadJsonInt(const QJsonValue& json, int& value, int& min, int& max)
{
  value = GetValueInt(json);
  min = GetMinInt(json);
  max = GetMaxInt(json);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ParameterSettings::ReadJsonFloat(const QJsonValue& json, float& value, float& min, float& max)
{
  value = GetValueFloat(json);
  min = GetMinFloat(json);
  max = GetMaxFloat(json);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ParameterSettings::ReadJsonDouble(const QJsonValue& json, double& value, double& min, double& max)
{
  value = GetValueDouble(json);
  min = GetMinDouble(json);
  max = GetMaxDouble(json);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool ParameterSettings::GetValueLocked(const QJsonValue& json)
{
  if(json.isString())
  {
    QString valueStr = GetTagValue(json, TAG_MAXIMUM);
    return valueStr.contains("true", Qt::CaseInsensitive);
  }

  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::ToJson(int value, bool locked)
{
  QString outputStr = TAG_VALUE + ":" + QString::number(value);

  if(locked)
  {
    outputStr += ", " + TAG_LOCKED + ":true";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::ToJson(int value, int min, int max, bool locked)
{
  QString outputStr = TAG_VALUE + ":" + QString::number(value) + ", " + 
    TAG_MINIMUM + ":" + QString::number(min) + ", " + 
    TAG_MAXIMUM + ":" + QString::number(max);

  if(locked)
  {
    outputStr += ", " + TAG_LOCKED + ":true";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::ToJson(double value, bool locked)
{
  QString outputStr = TAG_VALUE + ":" + QString::number(value);

  if(locked)
  {
    outputStr += ", " + TAG_LOCKED + ":true";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::ToJson(double value, double min, double max, bool locked)
{
  QString outputStr = TAG_VALUE + ":" + QString::number(value) + ", " +
    TAG_MINIMUM + ":" + QString::number(min) + ", " +
    TAG_MAXIMUM + ":" + QString::number(max);

  if(locked)
  {
    outputStr += ", " + TAG_LOCKED + ":true";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool ParameterSettings::IsLocked(const QJsonObject& json)
{
  if(json.contains(TAG_LOCKED))
  {
    QJsonValue value = json.find(TAG_LOCKED).value();
    if(value.isBool())
    {
      return value.toBool();
    }
  }

  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ParameterSettings::SetLocked(bool locked, QJsonObject& json)
{
  json.insert(TAG_LOCKED, locked);
}