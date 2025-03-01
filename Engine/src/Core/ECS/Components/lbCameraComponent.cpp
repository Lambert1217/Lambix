#include "Core/ECS/Components/lbCameraComponent.h"

namespace Lambix
{
    glm::mat4 lbCameraComponent::GetProjection(float viewportWidth, float viewportHeight) const
    {
        if (ProjectionType == CameraProjectionType::Perspective)
        {
            return glm::perspective(PerspectiveFOV, viewportWidth / viewportHeight, NearClip, FarClip);
        }
        else
        {
            float orthoLeft = -OrthographicSize * (viewportWidth / viewportHeight) * 0.5f;
            float orthoRight = OrthographicSize * (viewportWidth / viewportHeight) * 0.5f;
            float orthoBottom = -OrthographicSize * 0.5f;
            float orthoTop = OrthographicSize * 0.5f;
            return glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, NearClip, FarClip);
        }
    }
}