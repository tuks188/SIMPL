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
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

/**
 * @brief The DataContainerWriter class. See [Filter documentation](@ref datacontainerwriter) for details.
 */
class SIMPLib_EXPORT DataContainerWriter : public AbstractFilter
{
    Q_OBJECT
    
    // This line MUST be first when exposing a class and properties to Python
    PYB11_CREATE_BINDINGS(DataContainerWriter SUPERCLASS AbstractFilter)
    PYB11_PROPERTY(QString OutputFile READ getOutputFile WRITE setOutputFile)
    PYB11_PROPERTY(bool WriteXdmfFile READ getWriteXdmfFile WRITE setWriteXdmfFile)
    PYB11_PROPERTY(bool WriteTimeSeries READ getWriteTimeSeries WRITE setWriteTimeSeries)

  public:
    SIMPL_SHARED_POINTERS(DataContainerWriter)
    SIMPL_FILTER_NEW_MACRO(DataContainerWriter)
    SIMPL_TYPE_MACRO_SUPER_OVERRIDE(DataContainerWriter, AbstractFilter)

    ~DataContainerWriter() override;

    SIMPL_FILTER_PARAMETER(QString, OutputFile)
    Q_PROPERTY(QString OutputFile READ getOutputFile WRITE setOutputFile)

    SIMPL_INSTANCE_PROPERTY(bool, WritePipeline)

    SIMPL_FILTER_PARAMETER(bool, WriteXdmfFile)
    Q_PROPERTY(bool WriteXdmfFile READ getWriteXdmfFile WRITE setWriteXdmfFile)

    SIMPL_FILTER_PARAMETER(bool, WriteTimeSeries)
    Q_PROPERTY(bool WriteTimeSeries READ getWriteTimeSeries WRITE setWriteTimeSeries)

    SIMPL_INSTANCE_PROPERTY(bool, AppendToExisting)

    /**
     * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
     */
    const QString getCompiledLibraryName() const override;

    /**
     * @brief getBrandingString Returns the branding string for the filter, which is a tag
     * used to denote the filter's association with specific plugins
     * @return Branding string
     */
    const QString getBrandingString() const override;

    /**
     * @brief getFilterVersion Returns a version string for this filter. Default
     * value is an empty string.
     * @return
     */
    const QString getFilterVersion() const override;

    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

    /**
     * @brief getGroupName Reimplemented from @see AbstractFilter class
     */
    const QString getGroupName() const override;

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    const QString getSubGroupName() const override;

    /**
     * @brief getUuid Return the unique identifier for this filter.
     * @return A QUuid object.
     */
    const QUuid getUuid() override;

    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    const QString getHumanLabel() const override;

    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    void setupFilterParameters() override;

    /**
     * @brief readFilterParameters Reimplemented from @see AbstractFilter class
     */
    void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

    /**
     * @brief execute Reimplemented from @see AbstractFilter class
     */
    void execute() override;

    /**
    * @brief preflight Reimplemented from @see AbstractFilter class
    */
    void preflight() override;

  signals:
    /**
     * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
     * be pushed from a user-facing control (such as a widget)
     * @param filter Filter instance pointer
     */
    void updateFilterParameters(AbstractFilter* filter);

    /**
     * @brief parametersChanged Emitted when any Filter parameter is changed internally
     */
    void parametersChanged();

    /**
     * @brief preflightAboutToExecute Emitted just before calling dataCheck()
     */
    void preflightAboutToExecute();

    /**
     * @brief preflightExecuted Emitted just after calling dataCheck()
     */
    void preflightExecuted();

  protected:
    DataContainerWriter();
    /**
     * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
     */
    void dataCheck();

    /**
     * @brief Initializes all the private instance variables.
     */
    void initialize();


    /**
     * @brief openFile Opens or creates an HDF5 file to write data into
     * @param append Should a new file be created or append data to a currently existing file
     * @return
     */
    hid_t openFile(bool append = false);

    /**
     * @brief closeFile Closes the currently open file
     * @return Integer error value
     */
    herr_t closeFile();

    /**
     * @brief writePipeline Writes the existing pipeline to the HDF5 file
     * @return
     */
    int writePipeline();

    /**
     * @brief writeDataContainerBundles Writes any existing DataContainerBundles to the HDF5 file
     * @param fileId Group Id for the DataContainerBundles
     * @return
     */
    int writeDataContainerBundles(hid_t fileId);

    /**
     * @brief writeXdmfHeader Writes the Xdmf header
     * @param out QTextStream for output
     */
    void writeXdmfHeader(QTextStream& out);

    /**
     * @brief writeXdmfFooter Writes the Xdmf footer
     * @param out QTextStream for output
     */
    void writeXdmfFooter(QTextStream& out);

  private:
    hid_t m_FileId;

  public:
    DataContainerWriter(const DataContainerWriter&) = delete; // Copy Constructor Not Implemented
    DataContainerWriter(DataContainerWriter&&) = delete;      // Move Constructor Not Implemented
    DataContainerWriter& operator=(const DataContainerWriter&) = delete; // Copy Assignment Not Implemented
    DataContainerWriter& operator=(DataContainerWriter&&) = delete;      // Move Assignment Not Implemented
};

