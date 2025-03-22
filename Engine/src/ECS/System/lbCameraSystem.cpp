#include "lbCameraSystem.h"
#include "ECS/lbEntity.h"
#include "ECS/lbScene.h"

namespace Lambix
{
    lbCameraSystem::lbCameraSystem(lbScene *scene) : lbSystem(scene, 2, "CameraSystem")
    {
        lbEventDispatcher::Get()->addEventListener<lbCameraSystem>("ViewportResize", this, &lbCameraSystem::OnViewportResize);
    }

    lbCameraSystem::~lbCameraSystem()
    {
        lbEventDispatcher::Get()->removeEventListener<lbCameraSystem>("ViewportResize", this, &lbCameraSystem::OnViewportResize);
    }

    void lbCameraSystem::Init()
    {
        m_PrimaryCameraEntity = m_Scene->CreateEntity("PrimaryCamera");
        m_PrimaryCameraEntity->AddComponent<lbCameraComponent>();
        auto &trans = m_PrimaryCameraEntity->GetComponent<lbTransformComponent>();
        trans.m_Transform.SetPosition({0.0f, 3.0f, 5.f});
        trans.m_Transform.LookAt({0.0f, 0.0f, 0.0f});
    }

    void lbCameraSystem::OnUpdate(lbTimestep ts)
    {
        // 主摄像机更新
        m_PrimaryCameraEntity->GetComponent<lbCameraComponent>().OnUpdate(ts);
    }

    void lbCameraSystem::SetViewportSize(float width, float height)
    {
        viewportWidth = width;
        viewportHeight = height;
    }

    void lbCameraSystem::OnViewportResize(const lbEvent::Ptr &event)
    {
        float *size = static_cast<float *>(event->m_UserData);
        SetViewportSize(size[0], size[1]);
    }

} // namespace Lambix
