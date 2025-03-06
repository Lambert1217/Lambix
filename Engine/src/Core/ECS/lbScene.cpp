#include "Core/ECS/lbScene.h"
#include "Core/ECS/lbEntity.h"
#include "Core/Renderer/lbRendererCommand.h"
#include "Core/ECS/System/lbLightSystem.h"

namespace Lambix
{
    lbScene::lbScene()
    {
        // 创建主摄像机实体
        {
            m_PrimaryCameraEntity = CreateEntity("Primary Camera");
            auto &cameraComp = m_PrimaryCameraEntity->AddComponent<lbCameraComponent>();
            // cameraComp.ProjectionType = CameraProjectionType::Orthographic;
            m_PrimaryCameraEntity->GetComponent<lbTransformComponent>().SetLocalPosition({0, 0, 10});
        }
        // 光照系统
        {
            m_LightSystem = std::make_shared<lbLightSystem>(this);
            m_LightSystem->Init();
        }
    }
    std::shared_ptr<lbEntity> lbScene::CreateEntity(const std::string &name)
    {
        return CreateEntityWithUUID(name, GenUUID());
    }

    std::shared_ptr<lbEntity> lbScene::CreateEntityWithUUID(const std::string &name, lbUUID uuid)
    {
        std::shared_ptr<lbEntity> entity = std::make_shared<lbEntity>(m_Registry.create(), this);
        // ID组件
        {
            entity->AddComponent<lbIdentityComponent>(uuid, name);
        }
        // 变换组件
        {
            auto &transformComp = entity->AddComponent<lbTransformComponent>();
            transformComp.LinkToEntity(entity);
        }
        // 标志组件
        {
            auto &FlagComponent = entity->AddComponent<lbFlagComponent>();
            FlagComponent.SetRenderable(false);
        }
        m_EntityMap[*entity] = entity;
        return entity;
    }

    void lbScene::DestroyEntity(std::shared_ptr<lbEntity> entity)
    {
        if (!entity || !m_EntityMap.count(*entity))
            return;

        // 递归销毁子实体
        if (auto *childrenComp = m_Registry.try_get<lbChildrenComponent>(*entity))
        {
            auto children = childrenComp->m_Children; // 复制列表避免迭代时修改
            for (auto childHandle : children)
            {
                if (auto it = m_EntityMap.find(childHandle); it != m_EntityMap.end())
                {
                    DestroyEntity(it->second);
                }
            }
        }

        // 处理父节点关系
        if (auto *parentComp = m_Registry.try_get<lbParentComponent>(*entity))
        {
            if (auto parentIt = m_EntityMap.find(parentComp->m_Parent);
                parentIt != m_EntityMap.end())
            {
                auto &parentChildren = parentIt->second->GetComponent<lbChildrenComponent>();
                parentChildren.m_Children.erase(
                    std::remove(parentChildren.m_Children.begin(),
                                parentChildren.m_Children.end(),
                                *entity),
                    parentChildren.m_Children.end());
            }
        }

        // 清理注册表
        m_Registry.destroy(*entity);
        m_EntityMap.erase(*entity);
    }

    void lbScene::OnUpdate(lbTimestep ts)
    {
        // 光照系统更新
        m_LightSystem->OnUpdate(ts);
        // 实体渲染逻辑
        auto view = m_Registry.view<lbTransformComponent, lbMeshRendererComponent, lbFlagComponent>();
        view.each([this](auto entity, lbTransformComponent &trans, lbMeshRendererComponent &meshRenderer, lbFlagComponent &flags)
                  { DrawEntity(trans, meshRenderer, flags); });
    }

    void lbScene::SetViewportSize(float width, float height)
    {
        viewportWidth = width;
        viewportHeight = height;
    }

    void lbScene::DrawEntity(lbTransformComponent &trans, lbMeshRendererComponent &meshRenderer, lbFlagComponent &flags)
    {
        if (!flags.IsRenderable())
            return;
        meshRenderer.material->Bind();
        meshRenderer.material->UpdateUniforms();
        auto &ModelMatrix = trans.GetWorldMatrix();
        auto MVP = m_PrimaryCameraEntity->GetComponent<lbCameraComponent>().GetProjection(viewportWidth, viewportHeight) * glm::inverse(m_PrimaryCameraEntity->GetComponent<lbTransformComponent>().GetWorldMatrix()) * ModelMatrix;
        meshRenderer.material->GetShaderProgram()->UploadUniformMat4("u_ModelViewProjection", MVP);
        meshRenderer.material->GetShaderProgram()->UploadUniformMat4("u_ModelMatrix", ModelMatrix);
        auto vao = meshRenderer.geometry->GetVertexArray();
        vao->Bind();
        lbRendererCommand::DrawIndexed(DrawMode::Triangles, vao);
        meshRenderer.material->Unbind();
    }
}