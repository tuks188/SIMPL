
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
#pragma once

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/FilterParameters/DynamicTableData.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

/**
* @class DynamicTableExample DynamicTableExample.h ExamplePlugin/Code/ExamplePluginFilters/DynamicTableExample.h
* @brief
* @author
* @date
* @version 1.0
*/
class SIMPLib_EXPORT DynamicTableExample : public AbstractFilter
{
  Q_OBJECT
  PYB11_CREATE_BINDINGS(DynamicTableExample SUPERCLASS AbstractFilter)

  PYB11_PROPERTY(DynamicTableData DynamicData1 READ getDynamicData1 WRITE setDynamicData1)
  PYB11_PROPERTY(DynamicTableData DynamicData2 READ getDynamicData2 WRITE setDynamicData2)
  PYB11_PROPERTY(DynamicTableData DynamicData3 READ getDynamicData3 WRITE setDynamicData3)
  PYB11_PROPERTY(DynamicTableData DynamicData4 READ getDynamicData4 WRITE setDynamicData4)
  PYB11_PROPERTY(DynamicTableData DynamicData5 READ getDynamicData5 WRITE setDynamicData5)
public:
  SIMPL_SHARED_POINTERS(DynamicTableExample)
  SIMPL_FILTER_NEW_MACRO(DynamicTableExample)
  SIMPL_TYPE_MACRO_SUPER_OVERRIDE(DynamicTableExample, AbstractFilter)

  ~DynamicTableExample() override;

  /* Place your input parameters here. You can use some of the DREAM3D Macros if you want to */
  SIMPL_FILTER_PARAMETER(DynamicTableData, DynamicData1)
  Q_PROPERTY(DynamicTableData DynamicData1 READ getDynamicData1 WRITE setDynamicData1)

  SIMPL_FILTER_PARAMETER(DynamicTableData, DynamicData2)
  Q_PROPERTY(DynamicTableData DynamicData2 READ getDynamicData2 WRITE setDynamicData2)

  SIMPL_FILTER_PARAMETER(DynamicTableData, DynamicData3)
  Q_PROPERTY(DynamicTableData DynamicData3 READ getDynamicData3 WRITE setDynamicData3)

  SIMPL_FILTER_PARAMETER(DynamicTableData, DynamicData4)
  Q_PROPERTY(DynamicTableData DynamicData4 READ getDynamicData4 WRITE setDynamicData4)

  SIMPL_FILTER_PARAMETER(DynamicTableData, DynamicData5)
  Q_PROPERTY(DynamicTableData DynamicData5 READ getDynamicData5 WRITE setDynamicData5)

  const QString getCompiledLibraryName() const override;
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;
  const QString getGroupName() const override;

  /**
  * @brief This returns a string that is displayed in the GUI. It should be readable
  * and understandable by humans.
  */
  const QString getHumanLabel() const override;

  /**
  * @brief This returns a string that is displayed in the GUI and helps to sort the filters into
  * a subgroup. It should be readable and understandable by humans.
  */
  const QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  const QUuid getUuid() override;

  /**
  * @brief This method will instantiate all the end user settable options/parameters
  * for this filter
  */
  void setupFilterParameters() override;

  /**
  * @brief This method will read the options from a file
  * @param reader The reader that is used to read the options from a file
  */
  void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

  /**
  * @brief Reimplemented from @see AbstractFilter class
  */
  void execute() override;

  /**
  * @brief This function runs some sanity checks on the DataContainer and inputs
  * in an attempt to ensure the filter can process the inputs.
  */
  void preflight() override;

signals:
  void updateFilterParameters(AbstractFilter* filter);
  void parametersChanged();
  void preflightAboutToExecute();
  void preflightExecuted();

protected:
  DynamicTableExample();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

public:
  DynamicTableExample(const DynamicTableExample&) = delete; // Copy Constructor Not Implemented
  DynamicTableExample(DynamicTableExample&&) = delete;      // Move Constructor Not Implemented
  DynamicTableExample& operator=(const DynamicTableExample&) = delete; // Copy Assignment Not Implemented
  DynamicTableExample& operator=(DynamicTableExample&&) = delete;      // Move Assignment Not Implemented
};

