#include "ECS/lbScene.h"
#include "ECS/lbEntity.h"
#include "Renderer/lbRendererCommand.h"
#include "ECS/System/lbLightSystem.h"
#include "ECS/System/lbTransformSystem.h"
#include "ECS/System/lbCameraSystem.h"
#include "ECS/System/lbRendererSystem.h"
#include "lbScene.h"
#include "Core/lbApplication.h"

namespace Lambix
{
    lbScene::lbScene() : m_SystemManager(std::make_unique<lbSystemManager>())
    {
        Init();
    }
    lbScene::~lbScene()
    {
        lbEventDispatcher::Get()->removeEventListener<lbScene>("ViewportResize", this, &lbScene::OnViewportResize);
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
        // Tag组件
        {
            entity->AddComponent<lbTagComponent>();
        }
        // 父子组件
        {
            entity->AddComponent<lbParentComponent>();
            entity->AddComponent<lbChildrenComponent>();
        }
        // 变换组件
        {
            auto &transformComp = entity->AddComponent<lbTransformComponent>();
        }
        // 标志组件
        {
            auto &FlagComponent = entity->AddComponent<lbFlagComponent>();
            FlagComponent.SetRenderable(false);
        }
        m_EntityMap[entity->GetHandle()] = entity;
        return entity;
    }

    std::shared_ptr<lbEntity> lbScene::CreateEntityFromModel(const lbModel::Ptr &model)
    {
        auto rootName = model->GetRoot()->name;
        auto rootEntity = CreateEntityFromModelHelper(model->GetRoot(), model->GetMeshes());
        if (rootName != rootEntity->GetName())
        {
            auto &ic = rootEntity->GetComponent<lbIdentityComponent>();
            ic.m_Name = rootName;
        }
        return rootEntity;
    }

    void lbScene::DestroyEntity(std::shared_ptr<lbEntity> entity)
    {
        if (!entity || !m_EntityMap.count(entity->GetHandle()))
            return;

        // 递归销毁子实体
        if (auto *childrenComp = m_Registry.try_get<lbChildrenComponent>(entity->GetHandle()))
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
        if (auto *parentComp = m_Registry.try_get<lbParentComponent>(entity->GetHandle()))
        {
            if (auto parentIt = m_EntityMap.find(parentComp->m_Parent); parentIt != m_EntityMap.end())
            {
                auto &parentChildren = parentIt->second->GetComponent<lbChildrenComponent>();
                parentChildren.m_Children.erase(
                    std::remove(parentChildren.m_Children.begin(),
                                parentChildren.m_Children.end(),
                                entity->GetHandle()),
                    parentChildren.m_Children.end());
            }
        }

        // 清理注册表
        m_Registry.destroy(entity->GetHandle());
        m_EntityMap.erase(entity->GetHandle());
    }

    void lbScene::Init()
    {
        // 事件监听注册
        lbEventDispatcher::Get()->addEventListener<lbScene>("ViewportResize", this, &lbScene::OnViewportResize);
        // 场景帧缓冲创建
        lbFrameBufferSpecification spec;
        mSceneFrameBufferData.width = spec.width = lbApplication::GetInstance().GetAppSetting().WindowWidth;
        mSceneFrameBufferData.height = spec.height = lbApplication::GetInstance().GetAppSetting().WindowHeight;
        mSceneFrameBufferData.needUpdate = false;
        m_FrameBuffer = lbFrameBuffer::Create(spec);
        // 创建各个系统
        // 变换系统 用于更新实体的TransformComponent  优先级 1
        auto transformSystem = m_SystemManager->CreateSystem<lbTransformSystem>(this);
        transformSystem->Init();
        // 摄像机系统，用于管理摄像机， 优先级 2
        auto cameraSystem = m_SystemManager->CreateSystem<lbCameraSystem>(this);
        cameraSystem->Init();
        // 光源系统 用于更新实体的LightComponent，收集光源上传到UBO  优先级 3
        auto lightSystem = m_SystemManager->CreateSystem<lbLightSystem>(this);
        lightSystem->Init();
        // 渲染系统
        auto rendererSystem = m_SystemManager->CreateSystem<lbRendererSystem>(this);
        rendererSystem->Init();
    }

    void lbScene::OnUpdate(lbTimestep ts)
    {
        // 更新帧缓冲大小
        if (mSceneFrameBufferData.needUpdate)
        {
            m_FrameBuffer->Resize(mSceneFrameBufferData.width, mSceneFrameBufferData.height);
            mSceneFrameBufferData.needUpdate = false;
        }
        // 各个系统更新
        m_SystemManager->OnUpdate(ts);
    }

    std::shared_ptr<lbEntity> lbScene::GetEntity(entt::entity handle) const
    {
        if (handle == entt::null)
            return nullptr;
        if (auto it = m_EntityMap.find(handle); it != m_EntityMap.end())
        {
            return it->second;
        }
        return nullptr;
    }
    std::shared_ptr<lbEntity> lbScene::GetPrimaryCameraEntity() const
    {
        return static_cast<lbCameraSystem *>(GetSystem("CameraSystem"))->GetPrimaryCameraEntity();
    }

    std::shared_ptr<lbEntity> lbScene::CreateEntityFromModelHelper(const lbModelNode::Ptr &parentNode, const std::vector<lbMesh::Ptr> &meshes)
    {
        // 如果节点的mesh加子节点的数目不超过1
        if ((parentNode->meshIndices.size() + parentNode->children.size()) <= 1)
        {
            // 如果有子节点
            if (!parentNode->children.empty())
            {
                auto childNode = parentNode->children.front();
                // 递归处理子节点
                auto childNodeEntity = CreateEntityFromModelHelper(childNode, meshes);
                // 如果子节点生成了实体，更新其transform
                if (childNodeEntity)
                {
                    auto &transComp = childNodeEntity->GetComponent<lbTransformComponent>();
                    transComp.m_Transform.SetFromMatrix(parentNode->mTransformMatrix * transComp.m_Transform.GetWorldMatrix());
                }
                return childNodeEntity;
            }
            // 如果有mesh
            else if (!parentNode->meshIndices.empty())
            {
                auto index = parentNode->meshIndices.front();
                auto meshName = meshes[index]->name;
                if (meshName.empty() || meshName == "defaultobject")
                {
                    meshName = "Entity";
                }
                auto meshEntity = CreateEntity(meshName);
                auto &meshRendererComp = meshEntity->AddComponent<lbMeshRendererComponent>();
                meshRendererComp.mesh = meshes[index];
                // 设置transform
                auto &transComp = meshEntity->GetComponent<lbTransformComponent>();
                transComp.m_Transform.SetFromMatrix(parentNode->mTransformMatrix);
                return meshEntity;
            }
            // 没有mesh和子节点，不创建实体
            else
            {
                return nullptr;
            }
        }
        else
        {
            std::string nodeName = parentNode->name;
            if (nodeName.empty() || nodeName == "defaultobject")
            {
                nodeName = "Entity";
            }
            // 创建实体并设置名称和变换
            auto parentNodeEntity = CreateEntity(nodeName);
            auto &transComp = parentNodeEntity->GetComponent<lbTransformComponent>();
            transComp.m_Transform.SetFromMatrix(parentNode->mTransformMatrix);

            // 递归处理子节点
            for (const auto &childNode : parentNode->children)
            {
                auto childNodeEntity = CreateEntityFromModelHelper(childNode, meshes);
                if (childNodeEntity)
                {
                    // 设置父实体
                    childNodeEntity->SetParent(parentNodeEntity);
                }
            }

            // 处理当前节点的meshes
            for (auto index : parentNode->meshIndices)
            {
                auto meshName = meshes[index]->name;
                if (meshName.empty() || meshName == "defaultobject")
                {
                    meshName = "Entity";
                }
                auto meshEntity = CreateEntity(meshName);
                // 设置渲染组件
                auto &meshRendererComp = meshEntity->AddComponent<lbMeshRendererComponent>();
                meshRendererComp.mesh = meshes[index];
                // 设置父实体
                meshEntity->SetParent(parentNodeEntity);
            }

            return parentNodeEntity;
        }
    }

    void lbScene::OnViewportResize(const lbEvent::Ptr &event)
    {
        float *size = static_cast<float *>(event->m_UserData);
        mSceneFrameBufferData.width = (uint32_t)size[0];
        mSceneFrameBufferData.height = (uint32_t)size[1];
        mSceneFrameBufferData.needUpdate = true;
    }
}