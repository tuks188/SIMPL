#include "PipelineListener.h"

PipelineListener::PipelineListener(QObject* parent)
    : QObject(parent)
{

}

PipelineListener::~PipelineListener()
{

}

std::vector<PipelineMessage> PipelineListener::getMessages()
{
    return m_Messages;
}

std::vector<PipelineMessage> PipelineListener::getErrorMessages()
{
    std::vector<PipelineMessage> errorMessages;

    int numMessages = m_Messages.size();
    for(int i = 0; i < numMessages; i++)
    {
        if(m_Messages[i].getType() == PipelineMessage::MessageType::Error)
        {
            errorMessages.push_back(m_Messages[i]);
        }
    }

    return errorMessages;
}

std::vector<PipelineMessage> PipelineListener::getWarningMessages()
{
    std::vector<PipelineMessage> warningMessages;

    int numMessages = m_Messages.size();
    for(int i = 0; i < numMessages; i++)
    {
        if(m_Messages[i].getType() == PipelineMessage::MessageType::Warning)
        {
            warningMessages.push_back(m_Messages[i]);
        }
    }

    return warningMessages;
}

void PipelineListener::processPipelineMessage(const PipelineMessage& message)
{
    m_Messages.push_back(message);
}
