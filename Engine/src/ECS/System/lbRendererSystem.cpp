#include "lbRendererSystem.h"
#include "ECS/lbScene.h"
#include "ECS/Components/lbMeshRendererComponent.h"

namespace Lambix
{
    lbRendererSystem::lbRendererSystem(lbScene *scene)
        : lbSystem(scene, 4, "RendererSystem")
    {
    }

    void lbRendererSystem::Init()
    {
        mAttributes = lbDriverAttributes::Create();
        mInfo = lbDriverInfo::Create();
        mBindingStates = lbDriverBindingStates::Create(mAttributes);
        mGeometries = lbDriverGeometries::Create(mAttributes, mInfo, mBindingStates);
    }

    void lbRendererSystem::OnUpdate(lbTimestep ts)
    {
        auto view = m_Scene->GetRegistry().view<lbMeshRendererComponent>();
        view.each([ts](auto entity, auto &meshRendererComp)
                  { meshRendererComp.OnUpdate(ts); });

        mInfo->reset();
    }

} // namespace Lambix
