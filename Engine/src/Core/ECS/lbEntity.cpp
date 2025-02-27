#include "Core/ECS/lbEntity.h"

namespace Lambix
{
    lbEntity::lbEntity(entt::entity handle, lbScene *scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {
    }
}