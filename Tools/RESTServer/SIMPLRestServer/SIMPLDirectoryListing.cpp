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

#include "SIMPLDirectoryListing.h"

#include <QtCore/QTextStream>

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLDirectoryListing::ParseDir(QDir directory, QVector<QString>& fileNames, QVector<QDateTime>& dates)
{
  QFileInfoList fiList = directory.entryInfoList();

  int count = fiList.size();
  for(int i = 0; i < count; i++)
  {
    QFileInfo fi = fiList[i];
    fileNames.push_back(fi.fileName());
    dates.push_back(fi.lastModified());
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString SIMPLDirectoryListing::CreateHTMLTable(QVector<QString> fileNames, QVector<QDateTime> dates)
{
  if (fileNames.size() != dates.size())
  {
    return QString();
  }

  QString html;
  QTextStream ss(&html);

  ss << "<table>\n";
  ss << "<tr>\n";
  ss << "<th>File</th>\n";
  ss << "<th>Date</th>\n";
  ss << "</tr>\n";

  for (int i = 0; i < fileNames.size(); i++)
  {
    QString fileName = fileNames[i];
    QDateTime date = dates[i];

    ss << "<tr>\n";
    ss << QObject::tr("<td>%1</td>").arg(fileName);
    ss << QObject::tr("<td>%1</td>").arg(date.toString());
    ss << "</tr>\n";
  }

  ss << "</table>\n";

  return html;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString SIMPLDirectoryListing::ParseDirForTable(QDir directory)
{
  QVector<QString> fileNames;
  QVector<QDateTime> dates;
  ParseDir(directory, fileNames, dates);
  return CreateHTMLTable(fileNames, dates);
}
