#ifndef _pipelinelistener_h_
#define _pipelinelistener_h_

#include <vector>

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Common/IObserver.h"
#include "SIMPLib/Common/PipelineMessage.h"

class PipelineListener : public QObject, public IObserver
{
    Q_OBJECT
public:
    SIMPL_TYPE_MACRO_SUPER(PipelineListener, IObserver)

    
    PipelineListener(QObject* parent);
    virtual ~PipelineListener();

    std::vector<PipelineMessage> getMessages();
    std::vector<PipelineMessage> getErrorMessages();
    std::vector<PipelineMessage> getWarningMessages();
    std::vector<PipelineMessage> getStatusMessages();
    std::vector<PipelineMessage> getStandardOutputMessages();

public slots:
    void processPipelineMessage(const PipelineMessage& pm);

private:
    std::vector<PipelineMessage> m_Messages;
};

#endif
