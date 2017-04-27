#include "SIMPLib/Utilities/ParameterSettings.h"

#include <limits>


const QString ParameterSettings::LOCKED_ID = "Locked";

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
int ParameterSettings::getValueInt(const QJsonValue& json)
{
  if(json.isDouble())
  {
    return json.toInt();
  }
  
  int value = 0;

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 0)
    {
      bool ok = false;
      int newValue = valueSeg[0].toInt(&ok);
      
      if(ok)
      {
        value = newValue;
      }
    }
  }

  return value;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
float ParameterSettings::getValueFloat(const QJsonValue& json)
{
  if(json.isDouble())
  {
    return json.toDouble();
  }

  float value = 0.0f;

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 0)
    {
      bool ok = false;
      float newValue = valueSeg[0].toFloat(&ok);

      if(ok)
      {
        value = newValue;
      }
    }
  }

  return value;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
double ParameterSettings::getValueDouble(const QJsonValue& json)
{
  if(json.isDouble())
  {
    return json.toDouble();
  }

  double value = 0.0;

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 0)
    {
      bool ok = false;
      double newValue = valueSeg[0].toDouble(&ok);

      if(ok)
      {
        value = newValue;
      }
    }
  }

  return value;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int ParameterSettings::getMinInt(const QJsonValue& json)
{
  int min = std::numeric_limits<int>::min();

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 1)
    {
      bool ok = false;
      int newMin = valueSeg[1].toInt(&ok);

      if(ok)
      {
        min = newMin;
      }
    }
  }

  return min;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
float ParameterSettings::getMinFloat(const QJsonValue& json)
{
  float min = std::numeric_limits<float>::min();

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 1)
    {
      bool ok = false;
      float newMin = valueSeg[1].toFloat(&ok);

      if(ok)
      {
        min = newMin;
      }
    }
  }

  return min;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
double ParameterSettings::getMinDouble(const QJsonValue& json)
{
  double min = std::numeric_limits<double>::min();

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 1)
    {
      bool ok = false;
      double newMin = valueSeg[1].toDouble(&ok);

      if(ok)
      {
        min = newMin;
      }
    }
  }

  return min;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int ParameterSettings::getMaxInt(const QJsonValue& json)
{
  int max = std::numeric_limits<int>::max();

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 2)
    {
      bool ok = false;
      int newMax = valueSeg[2].toInt(&ok);

      if(ok)
      {
        max = newMax;
      }
    }
  }

  return max;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
float ParameterSettings::getMaxFloat(const QJsonValue& json)
{
  float max = std::numeric_limits<float>::max();

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 2)
    {
      bool ok = false;
      float newMax = valueSeg[2].toFloat(&ok);

      if(ok)
      {
        max = newMax;
      }
    }
  }

  return max;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
double ParameterSettings::getMaxDouble(const QJsonValue& json)
{
  double max = std::numeric_limits<double>::max();

  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    if(valueSeg.size() > 2)
    {
      bool ok = false;
      double newMax = valueSeg[2].toDouble(&ok);

      if(ok)
      {
        max = newMax;
      }
    }
  }

  return max;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ParameterSettings::readJsonInt(const QJsonValue& json, int& value, int& min, int& max)
{
  value = getValueInt(json);
  min = getMinInt(json);
  max = getMaxInt(json);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ParameterSettings::readJsonFloat(const QJsonValue& json, float& value, float& min, float& max)
{
  value = getValueFloat(json);
  min = getMinFloat(json);
  max = getMaxFloat(json);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ParameterSettings::readJsonDouble(const QJsonValue& json, double& value, double& min, double& max)
{
  value = getValueDouble(json);
  min = getMinDouble(json);
  max = getMaxDouble(json);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool ParameterSettings::getValueLocked(const QJsonValue& json)
{
  if(json.isString())
  {
    QString jsonStr = json.toString();
    QStringList valueSeg = jsonStr.split(",");

    // Value, Min, Max, Lock
    if(valueSeg.size() > 3)
    {
      if(valueSeg[3] == "true")
      {
        return true;
      }
      else if(valueSeg[3] == "false")
      {
        return false;
      }
    }

    // Value, Lock
    if(valueSeg.size() > 1)
    {
      if(valueSeg[1] == "true")
      {
        return true;
      }
      else if(valueSeg[1] == "false")
      {
        return false;
      }
    }
  }

  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::toJson(int value, bool locked)
{
  QString outputStr = QString::number(value);

  if(locked)
  {
    outputStr += ",true";
  }
  else
  {
    outputStr += ",false";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::toJson(int value, int min, int max, bool locked)
{
  QString outputStr = QString::number(value) + "," + QString::number(min) + "," + QString::number(max);

  if(locked)
  {
    outputStr += ",true";
  }
  else
  {
    outputStr += ",false";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::toJson(double value, bool locked)
{
  QString outputStr = QString::number(value);

  if(locked)
  {
    outputStr += ",true";
  }
  else
  {
    outputStr += ",false";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonValue ParameterSettings::toJson(double value, double min, double max, bool locked)
{
  QString outputStr = QString::number(value) + "," + QString::number(min) + "," + QString::number(max);

  if(locked)
  {
    outputStr += ",true";
  }
  else
  {
    outputStr += ",false";
  }

  return QJsonValue(outputStr);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool ParameterSettings::isLocked(const QJsonObject& json)
{
  if(json.contains(LOCKED_ID))
  {
    QJsonValue value = json.find(LOCKED_ID).value();
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
void ParameterSettings::setLocked(bool locked, QJsonObject& json)
{
  json.insert(LOCKED_ID, locked);
}