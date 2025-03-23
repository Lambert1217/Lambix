#include "lbCameraSystem.h"
#include "ECS/lbEntity.h"
#include "ECS/lbScene.h"
#include "Core/lbInput.h"

namespace Lambix
{
    lbCameraSystem::lbCameraSystem(lbScene *scene) : lbSystem(scene, 2, "CameraSystem")
    {
        lbEventDispatcher::Get()->addEventListener<lbCameraSystem>("ViewportResize", this, &lbCameraSystem::OnViewportResize);
        lbEventDispatcher::Get()->addEventListener<lbCameraSystem>("ViewportReadyForCameraControl", this, &lbCameraSystem::OnViewportReadyForCameraControl);
    }

    lbCameraSystem::~lbCameraSystem()
    {
        lbEventDispatcher::Get()->removeEventListener<lbCameraSystem>("ViewportResize", this, &lbCameraSystem::OnViewportResize);
        lbEventDispatcher::Get()->removeEventListener<lbCameraSystem>("ViewportReadyForCameraControl", this, &lbCameraSystem::OnViewportReadyForCameraControl);
    }

    void lbCameraSystem::Init()
    {
        m_PrimaryCameraEntity = m_Scene->CreateEntity("PrimaryCamera");
        m_PrimaryCameraEntity->AddComponent<lbCameraComponent>();
        auto &trans = m_PrimaryCameraEntity->GetComponent<lbTransformComponent>();
        trans.m_Transform.SetPosition({0.0f, 3.0f, 5.f});
        trans.m_Transform.LookAt({0.0f, 0.0f, 0.0f});
        // 摄像机控制
        m_PrimaryCameraController.camera = m_PrimaryCameraEntity;
    }

    void lbCameraSystem::OnUpdate(lbTimestep ts)
    {
        // 摄像机操控
        m_PrimaryCameraController.OnUpdate(ts);
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

    void lbCameraSystem::OnViewportReadyForCameraControl(const lbEvent::Ptr &event)
    {
        m_PrimaryCameraController.flag = true;
    }

    lbCameraSystem::lbCameraController::lbCameraController()
    {
    }

    lbCameraSystem::lbCameraController::lbCameraController(const std::shared_ptr<lbEntity> &cameraEntity) : camera(cameraEntity)
    {
    }

    lbCameraSystem::lbCameraController::~lbCameraController()
    {
    }

    void lbCameraSystem::lbCameraController::OnUpdate(lbTimestep ts)
    {
        if (!camera)
            return;
        if (flag)
        {
            flag = false;
            auto &tc = camera->GetComponent<lbTransformComponent>();
            glm::vec3 front = tc.m_Transform.GetFront();
            glm::vec3 right = tc.m_Transform.GetRight();
            glm::vec3 up = tc.m_Transform.GetUp();
            glm::vec3 direction = {0.0f, 0.0f, 0.0f};

            if (lbInput::IsMouseButtonPressed(LB_MOUSE_BUTTON_2))
            {
                auto [currentMouseX, currentMouseY] = lbInput::GetMousePosition();

                // 初始化上一帧位置
                if (m_LastMouseX == -1.0f || m_LastMouseY == -1.0f)
                {
                    m_LastMouseX = currentMouseX;
                    m_LastMouseY = currentMouseY;
                }
                else
                {
                    // 计算偏移量（考虑时间步长）
                    float xOffset = (m_LastMouseX - currentMouseX) * rotationSpeed * ts;
                    float yOffset = (m_LastMouseY - currentMouseY) * rotationSpeed * ts;

                    // 更新旋转角度
                    glm::vec3 rotation = tc.m_Transform.GetRotation();
                    rotation.y += xOffset;
                    rotation.x += yOffset;

                    // 限制俯仰角
                    rotation.x = glm::clamp(rotation.x, -89.0f, 89.0f);

                    tc.m_Transform.SetRotation(rotation);

                    // 保存当前鼠标位置
                    m_LastMouseX = currentMouseX;
                    m_LastMouseY = currentMouseY;
                }
            }
            else
            {
                // 重置鼠标记录
                m_LastMouseX = m_LastMouseY = -1.0f;
            }
            if (lbInput::IsKeyPressed(LB_KEY_SPACE))
            {
                direction += up;
            }
            if (lbInput::IsKeyPressed(LB_KEY_LEFT_SHIFT))
            {
                direction -= up;
            }
            if (lbInput::IsKeyPressed(LB_KEY_W))
            {
                direction += front;
            }
            if (lbInput::IsKeyPressed(LB_KEY_A))
            {
                direction -= right;
            }
            if (lbInput::IsKeyPressed(LB_KEY_S))
            {
                direction -= front;
            }
            if (lbInput::IsKeyPressed(LB_KEY_D))
            {
                direction += right;
            }
            if (direction.x != 0.0 || direction.y != 0.0 || direction.z != 0.0)
            {
                direction = glm::normalize(direction);
            }
            tc.m_Transform.Translate(direction * speed * (float)ts);
            tc.OnUpdate(ts);
        }
    }
} // namespace Lambix
