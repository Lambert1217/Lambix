#include "lbRendererSystem.h"
#include "ECS/lbScene.h"
#include "ECS/Components/lbMeshRendererComponent.h"
#include "Renderer/lbRendererCommand.h"

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
        // 渲染前
        m_Scene->GetFrameBuffer()->Bind();
        lbRendererCommand::SetClearColor(clearColor);
        lbRendererCommand::Clear();
        // 渲染
        auto view = m_Scene->GetRegistry().view<lbMeshRendererComponent>();
        view.each([ts](auto entity, auto &meshRendererComp)
                  { meshRendererComp.OnUpdate(ts); });

        mInfo->mRender.mDurationTime += ts;
        mInfo->reset();

        m_Scene->GetFrameBuffer()->Unbind();
    }

} // namespace Lambix
