#include "ECS/System/lbLightSystem.h"
#include "ECS/Components/lbTransformComponent.h"
#include "Log/lbLog.h"
#include "ECS/lbScene.h"

namespace Lambix
{
    lbLightSystem::lbLightSystem(lbScene *scene) : lbSystem(scene, 3, "LightSystem")
    {
    }

    void lbLightSystem::Init()
    {
        // 创建UBO，绑定点为1
        m_LightingUBO = lbUniformBuffer::Create({sizeof(lbLightsData), 1, true});
    }

    void lbLightSystem::OnUpdate(lbTimestep ts)
    {
        // 先刷新 m_LightsData
        m_LightsData = {};
        m_LightsData.header.ambient = glm::vec3(1.0f);
        m_LightsData.header.ambientIntensity = 0.3f;
        m_LightsData.header.lightCounts = glm::ivec4(0);
        // 逐一更新光源组件
        auto &registry = m_Scene->GetRegistry();
        registry.view<lbLightComponent>().each([ts](auto entity, auto &lightComp)
                                               { lightComp.OnUpdate(ts); });
        // 计算总数
        m_LightsData.header.lightCounts.w = m_LightsData.header.lightCounts.x + m_LightsData.header.lightCounts.y + m_LightsData.header.lightCounts.z;
        // 上传数据
        m_LightingUBO->SetData(&m_LightsData, sizeof(lbLightsData));
        m_LightingUBO->Bind();
    }
}