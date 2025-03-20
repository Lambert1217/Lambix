#include "lbMeshRendererComponent.h"
#include "Log/lbLog.h"
#include "ECS/lbEntity.h"
#include "ECS/System/lbRendererSystem.h"
#include "Renderer/lbRendererCommand.h"
#include "ECS/Components/lbTransformComponent.h"
#include "ECS/System/lbCameraSystem.h"

namespace Lambix
{
    void lbMeshRendererComponent::OnUpdate(lbTimestep ts)
    {
        auto rendererSystem = static_cast<lbRendererSystem *>(m_Entity.lock()->GetScene()->GetSystem("RendererSystem"));
        auto cameraSystem = static_cast<lbCameraSystem *>(m_Entity.lock()->GetScene()->GetSystem("CameraSystem"));
        auto cameraComp = cameraSystem->GetPrimaryCameraEntity()->GetComponent<lbCameraComponent>();
        // 获取到当前的geometry，get中可以做一些处理
        const auto geometry = rendererSystem->mGeometries->Get(mGeometry);
        // 更新geometry，创建VBO，VBO  （可以确保每帧只更新一次）
        rendererSystem->mGeometries->OnUpdate(geometry);
        // 渲染
        auto position = geometry->GetAttribute("a_Position");
        auto index = geometry->GetIndex();

        rendererSystem->mBindingStates->setup(geometry, index);

        // 更新材质
        mMaterial->Bind();
        auto model = m_Entity.lock()->GetComponent<lbTransformComponent>().m_Transform.GetWorldMatrix();
        auto view = cameraComp.GetViewMatrix();
        auto projection = cameraComp.GetProjectionMatrix();
        mMaterial->UpdateUniforms(model, view, projection);

        if (index)
        {
            lbRendererCommand::DrawIndexed(mMaterial->GetRenderState().drawMode, index->GetCount());
        }
        else
        {
            lbRendererCommand::DrawArray(mMaterial->GetRenderState().drawMode, position->GetCount());
        }
    }
}