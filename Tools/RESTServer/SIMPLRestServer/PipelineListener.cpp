#include "PipelineListener.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
PipelineListener::PipelineListener(QObject* parent)
    : QObject(parent)
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
PipelineListener::~PipelineListener()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
std::vector<PipelineMessage> PipelineListener::getMessages()
{
    return m_Messages;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
std::vector<PipelineMessage> PipelineListener::getStatusMessages()
{
  std::vector<PipelineMessage> statusMessages;

  int numMessages = m_Messages.size();
  for(int i = 0; i < numMessages; i++)
  {
    if(m_Messages[i].getType() == PipelineMessage::MessageType::StatusMessage)
    {
      statusMessages.push_back(m_Messages[i]);
    }
  }

  return statusMessages;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
std::vector<PipelineMessage> PipelineListener::getStandardOutputMessages()
{
  std::vector<PipelineMessage> stdOutMessages;

  int numMessages = m_Messages.size();
  for(int i = 0; i < numMessages; i++)
  {
    if(m_Messages[i].getType() == PipelineMessage::MessageType::StandardOutputMessage)
    {
      stdOutMessages.push_back(m_Messages[i]);
    }
  }

  return stdOutMessages;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void PipelineListener::processPipelineMessage(const PipelineMessage& message)
{
    m_Messages.push_back(message);

    if(message.getType() == PipelineMessage::MessageType::StandardOutputMessage)
    {
        qDebug() << message.getText();
    }
}
