#include "Core/ECS/System/lbLightSystem.h"
#include "Core/ECS/Components/lbTransformComponent.h"
#include "Core/Base/lbLog.h"

namespace Lambix
{
    lbLightSystem::lbLightSystem(lbScene *scene)
        : m_Scene(scene)
    {
    }

    void lbLightSystem::Init()
    {
        // 创建UBO，假设绑定点为1
        m_LightingUBO = lbUniformBuffer::Create({sizeof(lbLightData), 1, true});
    }

    void lbLightSystem::OnUpdate(lbTimestep ts)
    {
        CollectLightData();
        m_LightingUBO->SetData(&m_LightData, sizeof(lbLightData));
        m_LightingUBO->Bind();
    }

    void lbLightSystem::CollectLightData()
    {
        m_LightData = {}; // 重置数据
        m_LightData.header.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

        auto &registry = m_Scene->GetRegistry();

        // 单次遍历所有光源实体
        auto view = registry.view<lbLightComponent, lbTransformComponent>();
        view.each([&](auto entity, auto &light, auto &trans)
                  {
        switch (light.Type) {
            case LightType::Directional: {
                if (m_LightData.header.lightCounts.x >= MAX_DIRECTIONAL_LIGHT) {
                    LOG_WARN("Directional light limit exceeded: {}", MAX_DIRECTIONAL_LIGHT);
                    return;
                }
                auto& data = m_LightData.directionalLights[m_LightData.header.lightCounts.x++];
                data.direction = glm::vec4(trans.GetForward(), 0.0f);
                data.base.color = glm::vec4(light.Color, light.Intensity);
                break;
            }
            
            case LightType::Point: {
                if (m_LightData.header.lightCounts.y >= MAX_POINT_LIGHT) {
                    LOG_WARN("Point light limit exceeded: {}", MAX_POINT_LIGHT);
                    return;
                }
                auto& data = m_LightData.pointLights[m_LightData.header.lightCounts.y++];
                data.position = glm::vec4(trans.GetWorldPosition(), light.Range);
                data.base.color = glm::vec4(light.Color, light.Intensity);
                data.attenuation = glm::vec4(light.Attenuation, 0.0f);
                break;
            }
            
            case LightType::Spot: {
                if (m_LightData.header.lightCounts.z >= MAX_SPOT_LIGHT) {
                    LOG_WARN("Spot light limit exceeded: {}", MAX_SPOT_LIGHT);
                    return;
                }
                auto& data = m_LightData.spotLights[m_LightData.header.lightCounts.z++];
                data.position = glm::vec4(trans.GetWorldPosition(), light.Range);
                data.direction = glm::vec4(trans.GetForward(), glm::cos(light.InnerAngle));
                data.base.color = glm::vec4(light.Color, light.Intensity);
                data.spotParams = glm::vec4(
                    glm::cos(light.OuterAngle),
                    light.Attenuation.y, // 使用线性衰减项
                    0.0f, 0.0f
                );
                break;
            }
            
            default:
                LOG_ERROR("Unsupported light type: {}", static_cast<int>(light.Type));
        } });

        // 更新总光源数
        m_LightData.header.lightCounts.w =
            m_LightData.header.lightCounts.x +
            m_LightData.header.lightCounts.y +
            m_LightData.header.lightCounts.z;
    }
}