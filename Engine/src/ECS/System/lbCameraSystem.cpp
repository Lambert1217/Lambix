#include "lbCameraSystem.h"
#include "ECS/lbEntity.h"
#include "ECS/lbScene.h"

namespace Lambix
{
    lbCameraSystem::lbCameraSystem(lbScene *scene) : lbSystem(scene, 2, "CameraSystem")
    {
    }

    void lbCameraSystem::Init()
    {
        m_PrimaryCameraEntity = m_Scene->CreateEntity("PrimaryCamera");
        m_PrimaryCameraEntity->AddComponent<lbCameraComponent>();
        auto &trans = m_PrimaryCameraEntity->GetComponent<lbTransformComponent>();
        trans.m_Transform.SetPosition({0.0f, 0.0f, 10.f});
    }

    void lbCameraSystem::OnUpdate(lbTimestep ts)
    {
        // 主摄像机更新
        m_PrimaryCameraEntity->GetComponent<lbCameraComponent>().OnUpdate(ts);
    }

    void lbCameraSystem::OnEvent(Event &event)
    {
        // 主摄像机更新
        m_PrimaryCameraEntity->GetComponent<lbCameraComponent>().OnEvent(event);
    }

    void lbCameraSystem::SetViewportSize(float width, float height)
    {
        viewportWidth = width;
        viewportHeight = height;
    }

} // namespace Lambix
