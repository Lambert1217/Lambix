#include "lbProject.h"
#include "Log/lbLog.h"

// TODO: 移除
#include "lbEngine.h"

namespace Lambix
{
    lbProject::lbProject(const lbProjectSpecification &spec)
    {
        Init(spec);
    }

    void lbProject::Init(const lbProjectSpecification &spec)
    {
        mSpec = spec;
        mAssetManager = lbAssetManager::Create(mSpec.mPath / mSpec.mAssetPath);
        // TODO: 实现项目启动场景后修改, 目前仅默认生成一个场景
        mActiveScene = lbScene::Create();
        auto m_Scene = mActiveScene;
        // 光源创建
        {
            // 点光源
            {
                auto pointLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
                auto &ic = pointLight->GetComponent<lbIdentityComponent>();
                ic.m_Name = "pointLight1";
                auto &tc = pointLight->GetComponent<lbTransformComponent>();
                tc.m_Transform.Translate({5.0f, 5.0f, 5.0f});
                tc.m_Transform.Scale(0.3f);
                auto &lc = pointLight->AddComponent<lbLightComponent>();
                lc.Create<lbPointLight>(glm::vec2(0.001f, 10.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
            }
            {
                auto pointLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
                auto &ic = pointLight->GetComponent<lbIdentityComponent>();
                ic.m_Name = "pointLight2";
                auto &tc = pointLight->GetComponent<lbTransformComponent>();
                tc.m_Transform.Translate({-5.0f, 5.0f, 5.0f});
                tc.m_Transform.Scale(0.3f);
                auto &lc = pointLight->AddComponent<lbLightComponent>();
                lc.Create<lbPointLight>(glm::vec2(0.001f, 10.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
            }
            // 方向光
            {
                auto directionLight = m_Scene->CreateEntity("directionLight1");
                auto &lc = directionLight->AddComponent<lbLightComponent>();
                lc.Create<lbDirectionalLight>(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.3f), 0.2f);
            }
            {
                auto directionLight = m_Scene->CreateEntity("directionLight2");
                auto &lc = directionLight->AddComponent<lbLightComponent>();
                lc.Create<lbDirectionalLight>(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.2f);
            }
            // 聚光灯
            {
                auto spotLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
                auto &ic = spotLight->GetComponent<lbIdentityComponent>();
                ic.m_Name = "spotLight1";
                auto &tc = spotLight->GetComponent<lbTransformComponent>();
                tc.m_Transform.Translate({0.0f, 5.0f, 0.0f});
                tc.m_Transform.Scale({0.2f, 0.2f, 0.5f});
                tc.m_Transform.LookAt({-5.0f, 0.0f, -5.0f});
                auto &lc = spotLight->AddComponent<lbLightComponent>();
                lc.Create<lbSpotLight>(glm::vec2(0.001f, 50.0f), glm::vec2(0.01f, 10.0f), glm::vec3(0.0f, 0.0f, 1.0f), 2.0f);
            }
            {
                auto spotLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
                auto &ic = spotLight->GetComponent<lbIdentityComponent>();
                ic.m_Name = "spotLight2";
                auto &tc = spotLight->GetComponent<lbTransformComponent>();
                tc.m_Transform.Translate({0.0f, 10.0f, 0.0f});
                tc.m_Transform.Scale({0.2f, 0.2f, 0.5f});
                tc.m_Transform.LookAt({5.0f, 0.0f, -5.0f});
                auto &lc = spotLight->AddComponent<lbLightComponent>();
                lc.Create<lbSpotLight>(glm::vec2(0.001f, 50.0f), glm::vec2(0.01f, 30.0f), glm::vec3(1.0f, 1.0f, 0.0f), 2.0f);
            }
        }
        // 创建实体
        {
            PROFILE_SCOPE("ModelLoad");
            // 平面
            auto plane = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/plane.obj")));
            auto &tc_p = plane->GetComponent<lbTransformComponent>();
            tc_p.m_Transform.Translate({0.0f, -1.5f, 0.0f});
            // 立方体
            auto cube = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/cube.obj")));
            auto &tc_c = cube->GetComponent<lbTransformComponent>();
            tc_c.m_Transform.Translate({2.0f, 0.0f, 0.0f});
            tc_c.m_Transform.Scale(2);
            // 球体
            auto sphere = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
            auto &tc_s = sphere->GetComponent<lbTransformComponent>();
            tc_s.m_Transform.Translate({-2.0f, 0.0f, 0.0f});
            tc_s.m_Transform.Scale(2);
            if (sphere->HasComponent<lbMeshRendererComponent>())
            {
                auto &rc = sphere->GetComponent<lbMeshRendererComponent>();
                rc.mesh->mMaterial->SetDiffuseMap(lbTextureLoader::CreateSolidColor(0x888888ff));
            }
        }
    }

    bool lbProject::Serialize()
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Project" << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "Name" << YAML::Value << mSpec.mName;
        out << YAML::Key << "Path" << YAML::Value << mSpec.mPath.string();
        out << YAML::Key << "AssetPath" << YAML::Value << mSpec.mAssetPath.string();
        out << YAML::EndMap;
        out << YAML::EndMap;

        auto outPath = mSpec.mPath / (mSpec.mName + ".lproj");
        std::ofstream file(outPath);
        file << out.c_str();
        return true;
    }

    bool lbProject::Deserialize(const std::filesystem::path &path)
    {
        YAML::Node projectNode = YAML::LoadFile(path.string())["Project"];
        lbProjectSpecification spec;
        spec.mName = projectNode["Name"].as<std::string>();
        spec.mPath = projectNode["Path"].as<std::string>();
        spec.mAssetPath = projectNode["AssetPath"].as<std::string>();
        Init(spec);
        return true;
    }
} // namespace Lambix
