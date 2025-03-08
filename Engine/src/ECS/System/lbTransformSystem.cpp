#include "lbTransformSystem.h"
#include "ECS/Components/lbTransformComponent.h"
#include "ECS/lbScene.h"

namespace Lambix
{
    lbTransformSystem::lbTransformSystem(lbScene *scene) : lbSystem(scene, 1, "TransformSystem")
    {
    }

    void lbTransformSystem::OnUpdate(lbTimestep ts)
    {
        // 逐一更新光源组件
        auto &registry = m_Scene->GetRegistry();
        registry.view<lbTransformComponent>().each([ts](auto entity, auto &lightComp)
                                                   { lightComp.OnUpdate(ts); });
    }

} // namespace Lambix
