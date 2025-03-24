#include "lbDriverBackground.h"
#include "Log/lbLog.h"
#include "Renderer/Material/lbCubeMaterial.h"
#include "Utils/lbFileUtils.h"
#include "Resource/lbTextureLoader.h"
#include "Renderer/lbRendererCommand.h"

namespace Lambix
{
    lbDriverBackground::lbDriverBackground(lbScene *scene) : mScene(scene)
    {
        LOG_ASSERT(mScene, "mScene is nullptr");
        mSkybox = mScene->CreateEntity("Skybox");
        auto &rc = mSkybox->AddComponent<lbMeshRendererComponent>();
        rc.mesh = lbMesh::Create();
        // Geometry
        std::vector<float> skyboxVertices = {
            // positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f};
        rc.mesh->mGeometry = lbGeometry::Create();
        rc.mesh->mGeometry->SetAttribute("a_Position", lbAttributef::Create(skyboxVertices, 3));
        // Material
        rc.mesh->mMaterial = lbCubeMaterial::Create();
        std::array<std::filesystem::path, 6> skyboxTexturePath = {
            ASSETS("Textures/skybox/right.jpg"),
            ASSETS("Textures/skybox/left.jpg"),
            ASSETS("Textures/skybox/top.jpg"),
            ASSETS("Textures/skybox/bottom.jpg"),
            ASSETS("Textures/skybox/front.jpg"),
            ASSETS("Textures/skybox/back.jpg")};
        rc.mesh->mMaterial->SetCubeMap(lbTextureLoader::LoadCubeMap(skyboxTexturePath));
    }

    lbDriverBackground::~lbDriverBackground()
    {
        if (mSkybox && mScene)
        {
            mScene->DestroyEntity(mSkybox);
        }
    }

    void lbDriverBackground::OnUpdate(lbTimestep ts)
    {
        // 设置天空盒的position跟随主摄像机
        auto &cameraT = mScene->GetPrimaryCameraEntity()->GetComponent<lbTransformComponent>();
        auto &tc = mSkybox->GetComponent<lbTransformComponent>();
        tc.m_Transform.SetPosition(cameraT.m_Transform.GetPosition());
        tc.OnUpdate(ts);
        // 清理
        lbRendererCommand::SetClearColor(mClearColor);
        lbRendererCommand::Clear();
        // 第一个渲染天空盒子
        auto &rc = mSkybox->GetComponent<lbMeshRendererComponent>();
        rc.OnUpdate(ts);
    }

} // namespace Lambix
