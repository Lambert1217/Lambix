#include "lbLightComponent.h"
#include "Log/lbLog.h"
#include "ECS/lbEntity.h"
#include "ECS/System/lbLightSystem.h"

namespace Lambix
{
    lbLightType lbLightComponent::GetType() const
    {
        return m_Light ? m_Light->GetLightType() : lbLightType::None;
    }
    void lbLightComponent::OnUpdate(lbTimestep ts)
    {
        switch (GetType())
        {
        case lbLightType::Directional:
            ProcessDirectional();
            break;
        case lbLightType::Point:
            ProcessPoint();
            break;
        case lbLightType::Spot:
            ProcessSpot();
            break;
        default:
            LOG_WARN("Unknown light type!");
            break;
        }
    }
    void lbLightComponent::ProcessDirectional()
    {
        auto light = As<lbDirectionalLight>();
        auto lightSystem = dynamic_cast<lbLightSystem *>(m_Entity.lock()->GetScene()->GetSystem("LightSystem"));
        auto &lightsData = lightSystem->m_LightsData;

        if (lightsData.header.lightCounts.x >= MAX_DIRECTIONAL_LIGHT)
        {
            LOG_WARN("The number of directional lights exceeds the upper limit({}).", MAX_DIRECTIONAL_LIGHT);
            return;
        }
        auto &LightData = lightsData.DirectionalLights[lightsData.header.lightCounts.x++];
        LightData.color = light->color;
        LightData.intensity = light->intensity;
        LightData.direction = light->direction;
    }
    void lbLightComponent::ProcessPoint()
    {
        auto light = As<lbPointLight>();
        auto lightSystem = dynamic_cast<lbLightSystem *>(m_Entity.lock()->GetScene()->GetSystem("LightSystem"));
        auto &lightsData = lightSystem->m_LightsData;

        if (lightsData.header.lightCounts.y >= MAX_POINT_LIGHT)
        {
            LOG_WARN("The number of point lights exceeds the upper limit({}).", MAX_POINT_LIGHT);
            return;
        }
        auto &LightData = lightsData.PointLights[lightsData.header.lightCounts.y++];
        LightData.color = light->color;
        LightData.intensity = light->intensity;
        LightData.position = m_Entity.lock()->GetComponent<lbTransformComponent>().m_Transform.GetPosition();
        LightData.MinRange = light->MinRange;
        LightData.Range = light->Range;
    }
    void lbLightComponent::ProcessSpot()
    {
        auto light = As<lbSpotLight>();
        auto lightSystem = dynamic_cast<lbLightSystem *>(m_Entity.lock()->GetScene()->GetSystem("LightSystem"));
        auto &lightsData = lightSystem->m_LightsData;

        if (lightsData.header.lightCounts.z >= MAX_SPOT_LIGHT)
        {
            LOG_WARN("The number of spot lights exceeds the upper limit({}).", MAX_SPOT_LIGHT);
            return;
        }
        auto &LightData = lightsData.SpotLights[lightsData.header.lightCounts.z++];
        LightData.color = light->color;
        LightData.intensity = light->intensity;
        LightData.direction = light->direction;
        LightData.position = m_Entity.lock()->GetComponent<lbTransformComponent>().m_Transform.GetPosition();
        LightData.MinRange = light->MinRange;
        LightData.Range = light->Range;
        LightData.MinAngle = light->MinAngle;
        LightData.Angle = light->Angle;
    }
}