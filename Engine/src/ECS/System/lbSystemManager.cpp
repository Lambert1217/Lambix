#include "lbSystemManager.h"

namespace Lambix
{
    lbSystemManager::~lbSystemManager()
    {
        Clear();
    }
    void lbSystemManager::OnUpdate(lbTimestep ts)
    {
        for (auto it : m_Systems)
        {
            it->OnUpdate(ts);
        }
    }
    lbSystem *lbSystemManager::GetSystem(const std::string &name)
    {
        auto it = m_SystemMap.find(name);
        return (it != m_SystemMap.end()) ? it->second : nullptr;
    }
    void lbSystemManager::Clear()
    {
        m_Systems.clear();
        m_SystemMap.clear();
        m_OwnedSystems.clear();
    }
}