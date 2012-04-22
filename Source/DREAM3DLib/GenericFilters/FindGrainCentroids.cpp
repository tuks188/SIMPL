/* ============================================================================
 * Copyright (c) 2011 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2011 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * All rights reserved.
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
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
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
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "FindGrainCentroids.h"

#include <sstream>

#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/Common/IDataArray.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindGrainCentroids::FindGrainCentroids() :
AbstractFilter(),
m_GrainIdsArrayName(DREAM3D::CellData::GrainIds),
m_CentroidsArrayName(DREAM3D::FieldData::Centroids),
m_GrainIds(NULL),
m_Centroids(NULL)
{
  graincenters = NULL;

  INIT_DataArray(m_GrainCenters,float);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindGrainCentroids::~FindGrainCentroids()
{
}
// -----------------------------------------------------------------------------
void FindGrainCentroids::writeFilterOptions(AbstractFilterOptionsWriter* writer)
{
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindGrainCentroids::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{

  setErrorCondition(0);
  std::stringstream ss;
  DataContainer* m = getDataContainer();

  GET_PREREQ_DATA(m, DREAM3D, CellData, GrainIds, ss, -300, int32_t, Int32ArrayType, voxels, 1);

  CREATE_NON_PREREQ_DATA(m, DREAM3D, FieldData, Centroids, ss, float, FloatArrayType, 0, fields, 3);

  setErrorMessage(ss.str());
}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindGrainCentroids::preflight()
{
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindGrainCentroids::execute()
{
  setErrorCondition(0);
  DataContainer* m = getDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-1);
    std::stringstream ss;
    ss << getNameOfClass() << " DataContainer was NULL";
    setErrorMessage(ss.str());
    return;
  }
  setErrorCondition(0);

  int64_t totalPoints = m->getTotalPoints();
  size_t totalFields = m->getNumFieldTuples();
  size_t totalEnsembles = m->getNumEnsembleTuples();
  dataCheck(false, totalPoints, totalFields, totalEnsembles);
  if (getErrorCondition() < 0)
  {
    return;
  }

  if(m->getZPoints() > 1) find_centroids();
  if(m->getZPoints() == 1) find_centroids2D();

  std::stringstream ss;
  ss.str("");
  ss << getNameOfClass() << " - Complete";
  notify(ss.str(), 0, Observable::UpdateProgressMessage);
}
void FindGrainCentroids::find_centroids()
{
  DataContainer* m = getDataContainer();
  int64_t totalPoints = m->getTotalPoints();
  float x, y, z;
  int col, row, plane;
//  float allvol = 0.0;
  size_t numgrains = m->getNumFieldTuples();
  graincenters = m_GrainCenters->WritePointer(0, numgrains * 5);

  int xPoints = static_cast<int>(m->getXPoints());
  int yPoints = static_cast<int>(m->getYPoints());
//  int zPoints = static_cast<int>(m->getZPoints());

  float xRes = m->getXRes();
  float yRes = m->getYRes();
  float zRes = m->getZRes();

  // Initialize every element to 0.0
  for (size_t i = 0; i < numgrains * 5; i++)
  {
    graincenters[i] = 0.0f;
  }
  for (int j = 0; j < totalPoints; j++)
  {
    int gnum = m_GrainIds[j];
    graincenters[gnum * 5 + 0]++;
    col = j % xPoints;
    row = (j / xPoints) % yPoints;
    plane = j / (xPoints * yPoints);
    x = float(col) * xRes;
    y = float(row) * yRes;
    z = float(plane) *zRes;
    graincenters[gnum * 5 + 1] = graincenters[gnum * 5 + 1] + x;
    graincenters[gnum * 5 + 2] = graincenters[gnum * 5 + 2] + y;
    graincenters[gnum * 5 + 3] = graincenters[gnum * 5 + 3] + z;
  }
 // float res_scalar = xRes * yRes * zRes;
//  float vol_term = (4.0f / 3.0f) * m_pi;
  for (size_t i = 1; i < numgrains; i++)
  {
    graincenters[i * 5 + 1] = graincenters[i * 5 + 1] / graincenters[i * 5 + 0];
    graincenters[i * 5 + 2] = graincenters[i * 5 + 2] / graincenters[i * 5 + 0];
    graincenters[i * 5 + 3] = graincenters[i * 5 + 3] / graincenters[i * 5 + 0];
    m_Centroids[3 * i] = graincenters[i * 5 + 1];
    m_Centroids[3 * i + 1] = graincenters[i * 5 + 2];
    m_Centroids[3 * i + 2] = graincenters[i * 5 + 3];
  }
}
void FindGrainCentroids::find_centroids2D()
{
  DataContainer* m = getDataContainer();
  int64_t totalPoints = m->getTotalPoints();

  float x, y;
  int col, row;
  size_t numgrains = m->getNumFieldTuples();
  graincenters = m_GrainCenters->WritePointer(0, numgrains * 5);

  int xPoints = static_cast<int>(m->getXPoints());
  int yPoints = static_cast<int>(m->getYPoints());
//  int zPoints = static_cast<int>(m->getZPoints());

  float xRes = m->getXRes();
  float yRes = m->getYRes();
//  float zRes = m->getZRes();

  for (size_t i = 0; i < numgrains*5; i++)
  {
      graincenters[i] = 0.0f;
  }
  for (int j = 0; j < totalPoints; j++)
  {
    int gnum = m_GrainIds[j];
    graincenters[gnum*5 + 0]++;
    col = j % xPoints;
    row = (j / xPoints) % yPoints;
	  x = float(col)*xRes;
	  y = float(row)*yRes;
    graincenters[gnum*5 + 1] = graincenters[gnum*5 + 1] + x;
    graincenters[gnum*5 + 2] = graincenters[gnum*5 + 2] + y;
  }
  for (size_t i = 1; i < numgrains; i++)
  {
    graincenters[i*5 + 1] = graincenters[i*5 + 1] / graincenters[i*5 + 0];
    graincenters[i*5 + 2] = graincenters[i*5 + 2] / graincenters[i*5 + 0];
    m_Centroids[3*i] = graincenters[i*5 + 1];
    m_Centroids[3*i+1] = graincenters[i*5 + 2];

  }
}

