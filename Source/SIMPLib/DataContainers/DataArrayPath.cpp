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

#include "DataArrayPath.h"

#include <QtCore/QJsonObject>

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/DataArrays/NeighborList.hpp"
#include "SIMPLib/DataContainers/DataContainerArray.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath::HashType DataArrayPath::GetHash(const QString& name)
{
  std::hash<std::string> hashFn;
  return hashFn(name.toStdString());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QDebug operator<<(QDebug out, const DataArrayPath& v)
{
  out << v.getDataContainerName() << "|" << v.getAttributeMatrixName() << "|" << v.getDataArrayName();
  return out;
}

/* ############## Start API/Public Implementation ########################### */
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath::DataArrayPath() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath::DataArrayPath(const QString& dcName, const QString& amName, const QString& daName)
: m_DataContainerName(dcName)
, m_AttributeMatrixName(amName)
, m_DataArrayName(daName)
, m_DataContainerHash(GetHash(dcName))
, m_AttributeMatrixHash(GetHash(amName))
, m_DataArrayHash(GetHash(daName))
{
  updateDataType();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath::DataArrayPath(const QString& path)
{
  QStringList tokens = path.split(SIMPL::PathSep);

  if(!tokens.empty())
  {
    setDataContainerName(tokens.at(0));
  }
  if(tokens.size() > 1)
  {
    setAttributeMatrixName(tokens.at(1));
  }
  if(tokens.size() > 2)
  {
    setDataArrayName(tokens.at(2));
  }

  updateDataType();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath::DataArrayPath(const DataArrayPath& rhs)
{
  m_DataContainerName = rhs.m_DataContainerName;
  m_AttributeMatrixName = rhs.m_AttributeMatrixName;
  m_DataArrayName = rhs.m_DataArrayName;
  m_DataContainerHash = rhs.m_DataContainerHash;
  m_AttributeMatrixHash = rhs.m_AttributeMatrixHash;
  m_DataArrayHash = rhs.m_DataArrayHash;

  updateDataType();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath::~DataArrayPath() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QVector<DataArrayPath> DataArrayPath::ConvertToQVector(QStringList& paths)
{
  QVector<DataArrayPath> vPaths;
  foreach(const QString sPath, paths)
  {
    DataArrayPath p(sPath);
    vPaths.push_back(p);
  }
  return vPaths;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath& DataArrayPath::operator=(const DataArrayPath& rhs)
{
  m_DataContainerName = rhs.m_DataContainerName;
  m_AttributeMatrixName = rhs.m_AttributeMatrixName;
  m_DataArrayName = rhs.m_DataArrayName;
  m_DataContainerHash = rhs.m_DataContainerHash;
  m_AttributeMatrixHash = rhs.m_AttributeMatrixHash;
  m_DataArrayHash = rhs.m_DataArrayHash;

  updateDataType();
  return *this;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::operator==(const DataArrayPath& rhs) const
{
  return m_DataContainerHash == rhs.m_DataContainerHash && m_AttributeMatrixHash == rhs.m_AttributeMatrixHash && m_DataArrayHash == rhs.m_DataArrayHash;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::operator!=(const DataArrayPath& rhs) const
{
  bool b = (*this == rhs);
  return !b;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::operator<(const DataArrayPath& rhs) const
{
  return serialize() < rhs.serialize();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString DataArrayPath::serialize(const QString& delimiter) const
{
  QString s = "";
  if(!m_DataContainerName.isEmpty())
  {
    s = m_DataContainerName;
    if(!m_AttributeMatrixName.isEmpty())
    {
      s = s.append(delimiter);
      s = s.append(m_AttributeMatrixName);
      if(!m_DataArrayName.isEmpty())
      {
        s = s.append(delimiter);
        s = s.append(m_DataArrayName);
      }
    }
  }

  return s;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath DataArrayPath::Deserialize(const QString& str, const QString& delimiter)
{
  if(str.isEmpty())
  {
    return DataArrayPath();
  }

  int start = 0;
  QStringList daParts;
  int tokenIndex = 0;

  while(tokenIndex >= 0)
  {
    tokenIndex = str.indexOf(delimiter, start);
    QString part = str.mid(start, tokenIndex - start);
    daParts.push_back(part);
    start = tokenIndex + delimiter.size();
  }

  DataArrayPath path;
  switch(daParts.size())
  {
  case 3:
    path.setDataArrayName(daParts[2]);
  case 2:
    path.setAttributeMatrixName(daParts[1]);
  case 1:
    path.setDataContainerName(daParts[0]);
    break;
  }

  path.updateDataType();
  return path;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArrayPath::setDataContainerName(const QString& name)
{
  m_DataContainerName = name;
  m_DataContainerHash = GetHash(m_DataContainerName);
  updateDataType();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArrayPath::setAttributeMatrixName(const QString& name)
{
  m_AttributeMatrixName = name;
  m_AttributeMatrixHash = GetHash(m_AttributeMatrixName);
  updateDataType();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArrayPath::setDataArrayName(const QString& name)
{
  m_DataArrayName = name;
  m_DataArrayHash = GetHash(m_DataArrayName);
  updateDataType();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::CheckRenamePath(const DataContainerArrayShPtr& oldDca, const DataContainerArrayShPtr& newDca, const DataArrayPath& oldPath, const DataArrayPath& newPath)
{
  // If the paths are not possible renames, return false
  if(!oldPath.possibleRename(newPath))
  {
    return false;
  }

  // Check that the DataArrayPath targets are compatibles
  DataContainer::Pointer oldDc = oldDca->getDataContainer(oldPath.getDataContainerName());
  DataContainer::Pointer newDc = newDca->getDataContainer(newPath.getDataContainerName());

  // Data Container required
  if(oldDc && newDc)
  {
    IGeometry::Pointer oldGeom = oldDc->getGeometry();
    IGeometry::Pointer newGeom = newDc->getGeometry();

    bool hasGeom = oldGeom && newGeom;
    if((hasGeom && oldGeom->getGeometryType() == newGeom->getGeometryType()) || !hasGeom)
    {
      // No Attribute Matrix path
      if(oldPath.getAttributeMatrixName().isEmpty() && newPath.getAttributeMatrixName().isEmpty())
      {
        return true;
      }

      AttributeMatrix::Pointer oldAm = oldDc->getAttributeMatrix(oldPath.getAttributeMatrixName());
      AttributeMatrix::Pointer newAm = newDc->getAttributeMatrix(newPath.getAttributeMatrixName());

      bool hasAttributeMatrix = oldAm && newAm;
      if(hasAttributeMatrix && oldAm->getType() == newAm->getType() && oldAm->getNumberOfTuples() == newAm->getNumberOfTuples())
      {
        // No Data Array path
        if(oldPath.getDataArrayName().isEmpty() && newPath.getDataArrayName().isEmpty())
        {
          return true;
        }

        IDataArray::Pointer oldDa = oldAm->getAttributeArray(oldPath.getDataArrayName());
        IDataArray::Pointer newDa = newAm->getAttributeArray(newPath.getDataArrayName());

        bool hasDataArray = oldDa && newDa;
        bool hasSameType = oldDa->getTypeAsString() == newDa->getTypeAsString();
        bool hasSameCompDims = oldDa->getComponentDimensions() == newDa->getComponentDimensions();
        bool isNeighborList = hasSameType && newDa->getTypeAsString().startsWith("NeighborList");
        if(hasDataArray && hasSameType  && (hasSameCompDims || isNeighborList))
        {
          return true;
        }
      }
    }
  }

  return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath::RenameContainer DataArrayPath::CheckForRenamedPaths(const DataContainerArrayShPtr& oldDca, const DataContainerArrayShPtr& newDca, const std::list<DataArrayPath>& oldPaths, const std::list<DataArrayPath>& newPaths)
{
  RenameContainer container;
  std::list<DataArrayPath> duplicatedPaths;
  std::list<DataArrayPath> usedNewPaths;

  // For each older path, check for any matching new paths.  If only one new path matches, add it as a possibility
  for(const DataArrayPath& oldPath : oldPaths)
  {
    // If the same path exists in both oldPaths and newPaths, it was not renamed
    if(std::find(newPaths.begin(), newPaths.end(), oldPath) != newPaths.end())
    {
      continue;
    }

    // Find any potential renames in newPaths for the given oldPath
    std::list<DataArrayPath> matches;
    for(const DataArrayPath& newPath : newPaths)
    {
      // If the same path exists in both oldPaths and newPaths, it was not renamed
      if(std::find(oldPaths.begin(), oldPaths.end(), newPath) != oldPaths.end())
      {
        continue;
      }

      // Check that all geometries, AttributeMatrices, and DataArrays are compatible
      if(CheckRenamePath(oldDca, newDca, oldPath, newPath))
      {
        matches.push_back(newPath);
      }
    }
    // If this path was already used, mark it as duplicate and move on
    if(matches.size() == 1)
    {
      const DataArrayPath& newPath = matches.front();
      if(usedNewPaths.end() != std::find(usedNewPaths.begin(), usedNewPaths.end(), newPath))
      {
        duplicatedPaths.push_back(newPath);
      }
      else
      {
        usedNewPaths.push_back(newPath);
        container.push_back(std::make_pair(oldPath, newPath));
      }
    }
  }

  // Remove items with duplicated paths
  for(auto iter = container.begin(); iter != container.end(); )
  {
    const DataArrayPath& checkPath = std::get<1>(*iter);
    if(duplicatedPaths.end() != std::find(duplicatedPaths.begin(), duplicatedPaths.end(), checkPath))
    {
      iter = container.erase(iter);
    }
    else
    {
      iter++;
    }
  }

  return container;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArrayPath::updateDataType()
{
  const bool dcEmpty = m_DataContainerName.isEmpty();
  const bool amEmpty = m_AttributeMatrixName.isEmpty();
  const bool daEmpty = m_DataArrayName.isEmpty();

  if(dcEmpty)
  {
    m_DataType = DataArrayPathHelper::DataType::None;
    return;
  }
  if(amEmpty)
  {
    if(daEmpty)
    {
      m_DataType = DataArrayPathHelper::DataType::DataContainer;
      return;
    }
  }
  else
  {
    if(daEmpty)
    {
      m_DataType = DataArrayPathHelper::DataType::AttributeMatrix;
      return;
    }
    if(!amEmpty)
    {
      m_DataType = DataArrayPathHelper::DataType::DataArray;
      return;
    }
  }

  m_DataType = DataArrayPathHelper::DataType::None;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QVector<QString> DataArrayPath::toQVector() const
{
  QVector<QString> v(3);
  v[0] = getDataContainerName();
  v[1] = getAttributeMatrixName();
  v[2] = getDataArrayName();
  return v;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QList<QString> DataArrayPath::GetDataArrayNames(const QVector<DataArrayPath>& paths)
{
  QList<QString> arrayNames;
  for(int i = 0; i < paths.count(); i++)
  {
    arrayNames.push_back(paths.at(i).getDataArrayName());
  }

  return arrayNames;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPath DataArrayPath::GetAttributeMatrixPath(const QVector<DataArrayPath>& paths)
{
  if(paths.isEmpty())
  {
    return DataArrayPath();
  }

  return DataArrayPath(paths.first().getDataContainerName(), paths.first().getAttributeMatrixName(), "");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QStringList DataArrayPath::toQStringList() const
{
  QStringList l;
  l << getDataContainerName() << getAttributeMatrixName() << getDataArrayName();
  return l;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArrayPath::update(const QString& dcName, const QString& amName, const QString& daName)
{
  setDataContainerName(dcName);
  setAttributeMatrixName(amName);
  setDataArrayName(daName);
  updateDataType();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::hasSameDataContainer(const DataArrayPath& other) const
{
  return m_DataContainerHash == other.m_DataContainerHash;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::hasSameAttributeMatrix(const DataArrayPath& other) const
{
  return m_AttributeMatrixHash == other.m_AttributeMatrixHash;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::hasSameDataArray(const DataArrayPath& other) const
{
  return m_DataArrayHash == other.m_DataArrayHash;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::hasSameAttributeMatrixPath(const DataArrayPath& other) const
{
  return (hasSameDataContainer(other) && hasSameAttributeMatrix(other));
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::isSubset(const DataArrayPath& other) const
{
  // Check types
  const DataArrayPathHelper::DataType type = getDataType();
  const DataArrayPathHelper::DataType otherType = other.getDataType();

  // If both are of the same DataType, require identical paths
  if(type == otherType)
  {
    return (*this) == other;
  }

  switch(otherType)
  {
  case DataArrayPathHelper::DataType::DataArray:
    // [[fallthrough]];
  case DataArrayPathHelper::DataType::AttributeMatrix:
    if(type == DataArrayPathHelper::DataType::DataArray)
    {
      return false;
    }
    // [[fallthrough]];
  case DataArrayPathHelper::DataType::DataContainer:
    if(type == DataArrayPathHelper::DataType::AttributeMatrix || type == DataArrayPathHelper::DataType::DataArray)
    {
      return false;
    }
    break;
  case DataArrayPathHelper::DataType::None:
    if(type != DataArrayPathHelper::DataType::None)
    {
      return false;
    }
  }

  bool valid = true;
  switch(type)
  {
  case DataArrayPathHelper::DataType::DataArray:
    valid &= m_DataArrayHash == other.m_DataArrayHash;
    // [[fallthrough]];
  case DataArrayPathHelper::DataType::AttributeMatrix:
    valid &= m_AttributeMatrixHash == other.m_AttributeMatrixHash;
    // [[fallthrough]];
  case DataArrayPathHelper::DataType::DataContainer:
    valid &= m_DataContainerHash == other.m_DataContainerHash;
    break;
  case DataArrayPathHelper::DataType::None:
    break;
  }

  return valid;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::ValidateVector(const QVector<DataArrayPath>& other)
{
  QString dcName = "";
  QString amName = "";

  if(other.isEmpty())
  {
    return true;
  }

    dcName = other.first().getDataContainerName();
    amName = other.first().getAttributeMatrixName();

  for(int i = 0; i < other.size(); ++i)
  {
    if(other.at(i).getDataContainerName() != dcName || other.at(i).getAttributeMatrixName() != amName)
    {
      return false;
    }
  }

  return true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QJsonObject DataArrayPath::toJsonObject() const
{
  QJsonObject json;
  json["Data Container Name"] = getDataContainerName();
  json["Attribute Matrix Name"] = getAttributeMatrixName();
  json["Data Array Name"] = getDataArrayName();
  return json;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataArrayPath::writeJson(QJsonObject& json) const
{
  json["Data Container Name"] = getDataContainerName();
  json["Attribute Matrix Name"] = getAttributeMatrixName();
  json["Data Array Name"] = getDataArrayName();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool DataArrayPath::readJson(QJsonObject& json)
{
  if(json["Data Container Name"].isString() && json["Attribute Matrix Name"].isString() && json["Data Array Name"].isString())
  {
    setDataContainerName(json["Data Container Name"].toString());
    setAttributeMatrixName(json["Attribute Matrix Name"].toString());
    setDataArrayName(json["Data Array Name"].toString());
    return true;
  }
  return false;
}
