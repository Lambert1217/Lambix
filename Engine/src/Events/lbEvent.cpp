#include "lbEvent.h"

namespace Lambix
{
    void lbEvent::Set(const std::string &name, void *emitter, void *data)
    {
        m_EventName = name;
        m_Emitter = emitter;
        m_UserData = data;
    }

    void lbEventDispatcher::dispatchEvent(const lbEvent::Ptr &event)
    {
        const std::string &name = event->m_EventName;

        auto listenerQueueIter = m_Listeners.find(name);
        if (listenerQueueIter == m_Listeners.end())
        {
            return;
        }

        auto &queue = listenerQueueIter->second;
        for (const auto &listener : queue)
        {
            listener->m_EventFunction(event);
        }
    }
}