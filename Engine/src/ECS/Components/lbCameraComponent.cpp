#include "lbCameraComponent.h"
#include "ECS/lbEntity.h"
#include "ECS/System/lbCameraSystem.h"

namespace Lambix
{
    lbCameraComponent::lbCameraComponent(CameraProjectionType cameraType)
        : ProjectionType(cameraType)
    {
        switch (ProjectionType)
        {
        case CameraProjectionType::Perspective:
            SetPerspective();
            break;
        case CameraProjectionType::Orthographic:
            SetOrthographic();
            break;
        default:
            LOG_ERROR("Unknown camera type!");
            break;
        }
    }
    void lbCameraComponent::OnUpdate(lbTimestep ts)
    {
        // 先计算 Projection
        glm::mat4 Projection(1.0f);
        auto cameraSystem = static_cast<lbCameraSystem *>(m_Entity.lock()->GetScene()->GetSystem("CameraSystem"));
        float aspect = cameraSystem->GetViewportWidth() / cameraSystem->GetViewportHeight();
        if (ProjectionType == CameraProjectionType::Perspective)
        {
            Projection = glm::perspective(PerspectiveFOV, aspect, NearClip, FarClip);
        }
        else
        {
            float orthoLeft = -OrthographicSize * aspect * 0.5f;
            float orthoRight = OrthographicSize * aspect * 0.5f;
            float orthoBottom = -OrthographicSize * 0.5f;
            float orthoTop = OrthographicSize * 0.5f;
            Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, NearClip, FarClip);
        }
        // Projection * view， 其中 view 等于 WorldMatrix 的逆
        ViewProjectionMatrix = Projection * glm::inverse(m_Entity.lock()->GetComponent<lbTransformComponent>().m_Transform.GetWorldMatrix());
    }
    void lbCameraComponent::SetPerspective(float Fov, float nearClip, float farClip)
    {
        ProjectionType = CameraProjectionType::Perspective;
        PerspectiveFOV = Fov;
        NearClip = nearClip;
        FarClip = farClip;
    }
    void lbCameraComponent::SetOrthographic(float size, float nearClip, float farClip)
    {
        ProjectionType = CameraProjectionType::Orthographic;
        OrthographicSize = size;
        NearClip = nearClip;
        FarClip = farClip;
    }
    const glm::mat4 &lbCameraComponent::GetViewProjection() const
    {
        return ViewProjectionMatrix;
    }
}