#ifndef _pipelinelistener_h_
#define _pipelinelistener_h_

#include <vector>

#include "SIMPLib/Common/PipelineMessage.h"

class PipelineListener : public QObject
{
    Q_OBJECT
public:
    PipelineListener(QObject* parent);
    ~PipelineListener();

    std::vector<PipelineMessage> getMessages();
    std::vector<PipelineMessage> getErrorMessages();
    std::vector<PipelineMessage> getWarningMessages();
    std::vector<PipelineMessage> getStatusMessages();
    std::vector<PipelineMessage> getStandardOutputMessages();

public slots:
    void processPipelineMessage(const PipelineMessage&);

private:
    std::vector<PipelineMessage> m_Messages;
};

#endif
