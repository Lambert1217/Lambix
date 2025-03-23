#include "lbModelLoader.h"
#include "Log/lbLog.h"
#include "Renderer/Material/lbBasicMaterial.h"
#include "Resource/lbTextureLoader.h"

namespace Lambix
{
    lbModel::Ptr lbModelLoader::LoadFromFile(const std::filesystem::path &path)
    {
        lbModel::Ptr model = lbModel::Create();

        // 所有的材质，顺序与aiScene中的mMaterials一致
        std::vector<lbMaterial::Ptr> materials;
        // 所有的网格
        auto &meshes = model->m_Meshes;

        // 开始读取
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            LOG_ERROR("model read fail! {}", path.string());
            return nullptr;
        }

        // 模型读取的path一般是这样的：assets/models/superMan/man.fbx
        // 取出来根路径：assets/models/superMan/
        std::filesystem::path rootPath = path.parent_path();

        // 处理材质
        processMaterial(scene, rootPath, materials);

        // 创建根节点
        auto rootNode = lbModelNode::Create();
        model->m_RootNode = rootNode;

        // 递归处理节点
        processNode(scene->mRootNode, scene, rootNode, materials, meshes);

        return model;
    }

    void lbModelLoader::processMaterial(const aiScene *scene, const std::filesystem::path &rootPath, std::vector<lbMaterial::Ptr> &materials)
    {
        // 循环解析每一个材质
        for (uint32_t id = 0; id < scene->mNumMaterials; ++id)
        {
            lbMaterial::Ptr material = nullptr;

            aiMaterial *aimaterial = scene->mMaterials[id];

            // 获取当前的Material是什么类型
            aiShadingMode shadingMode{aiShadingMode::aiShadingMode_Flat};
            aimaterial->Get(AI_MATKEY_SHADING_MODEL, shadingMode);

            // TODO: 拓展更多材质类型
            switch (shadingMode)
            {
            case aiShadingMode::aiShadingMode_Flat:
                material = lbBasicMaterial::Create();
                break;
            default:
                material = lbBasicMaterial::Create();
                break;
            }

            // 为材质读取贴图
            material->SetDiffuseMap(processTexture2D(aiTextureType_DIFFUSE, scene, aimaterial, rootPath));
            material->SetNormalMap(processTexture2D(aiTextureType_NORMALS, scene, aimaterial, rootPath));
            material->SetSpecularMap(processTexture2D(aiTextureType_SPECULAR, scene, aimaterial, rootPath));

            materials.push_back(material);
        }
    }

    lbTexture2D::Ptr lbModelLoader::processTexture2D(const aiTextureType &type, const aiScene *scene, const aiMaterial *material, const std::filesystem::path &rootPath)
    {
        // 拿到材质相对路径
        aiString aiPath;
        material->Get(AI_MATKEY_TEXTURE(type, 0), aiPath);

        if (!aiPath.length)
        {
            return nullptr;
        }

        // 有的模型会将纹理打包在模型内部
        const aiTexture *assimpTexture = scene->GetEmbeddedTexture(aiPath.C_Str());
        if (assimpTexture)
        {
            // 如果确实图片打包在了模型内部，则上述代码获取到的aiTexture里面就含有了图片数据
            unsigned char *dataIn = reinterpret_cast<unsigned char *>(assimpTexture->pcData);
            uint32_t width = assimpTexture->mWidth;
            uint32_t height = assimpTexture->mHeight;
            uint32_t size = height ? width * height : width;

            return lbTextureLoader::LoadFromMemory(dataIn, size);
        }
        else
        {
            std::filesystem::path fullPath = rootPath / std::filesystem::path(aiPath.C_Str());
            return lbTextureLoader::LoadFromFile(fullPath);
        }
    }

    void lbModelLoader::processNode(const aiNode *node, const aiScene *scene,
                                    const lbModelNode::Ptr &parentNode, std::vector<lbMaterial::Ptr> &materials, std::vector<lbMesh::Ptr> &meshes)
    {
        // 设置节点名称
        parentNode->name = node->mName.C_Str();
        // 设置节点的变换
        parentNode->mTransformMatrix = ToGLMMat4(node->mTransformation);

        // 处理当前节点的网格
        for (uint32_t i = 0; i < node->mNumMeshes; ++i)
        {
            // 对于当前node的第i个Mesh，取出来其MeshID（node->mMeshes[i]），用这个MeshID向Scene里面索引aiMesh，拿到具体数据
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            auto newMesh = processMesh(mesh, scene, materials);
            meshes.push_back(newMesh);
            parentNode->meshIndices.push_back(meshes.size() - 1);
        }

        // 递归处理子节点
        for (uint32_t i = 0; i < node->mNumChildren; ++i)
        {
            auto childNode = lbModelNode::Create();
            parentNode->children.push_back(childNode);
            processNode(node->mChildren[i], scene, childNode, materials, meshes);
        }
    }

    lbMesh::Ptr lbModelLoader::processMesh(const aiMesh *mesh, const aiScene *scene, std::vector<lbMaterial::Ptr> &materials)
    {
        auto newMesh = lbMesh::Create();
        auto geometry = lbGeometry::Create();
        newMesh->mGeometry = geometry;
        newMesh->name = mesh->mName.C_Str();

        // geometry数据传入
        // 一个Mesh所需要的所有attributes
        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> tangents;
        std::vector<float> bitangents;

        std::vector<std::vector<float>> uvs;   // 每一个元素都是第i个channel的纹理坐标数据
        std::vector<uint32_t> numUVComponents; // 每一个元素都是第i个channel的itemSize

        std::vector<uint32_t> indices;

        // 按照顶点来遍历的
        for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
        {
            positions.push_back(mesh->mVertices[i].x);
            positions.push_back(mesh->mVertices[i].y);
            positions.push_back(mesh->mVertices[i].z);

            normals.push_back(mesh->mNormals[i].x);
            normals.push_back(mesh->mNormals[i].y);
            normals.push_back(mesh->mNormals[i].z);

            if (mesh->mTangents->Length())
            {
                tangents.push_back(mesh->mTangents[i].x);
                tangents.push_back(mesh->mTangents[i].y);
                tangents.push_back(mesh->mTangents[i].z);
            }

            if (mesh->mBitangents->Length())
            {
                bitangents.push_back(mesh->mBitangents[i].x);
                bitangents.push_back(mesh->mBitangents[i].y);
                bitangents.push_back(mesh->mBitangents[i].z);
            }

            // may have multi-textures, u is the number
            // 1 一个模型可能其中的mesh会有多个贴图，贴图可能会有相同功能，比如DiffuseMap可能有多张，那么颜色就会混合
            // 也有可能是不同功能，比如NormalMap SpecularMap DiffuseMap。
            //  2 既然有多张贴图可能，同一个顶点采样不同的纹理，可能会有不同的uv坐标
            //  3 纹理坐标会有不同类型，如果采样二位图片，就是简单的二位uv，如果采样环境贴图uvw（str）
            //
            //  总结：对于同一个Mesh，读取其某个顶点的uv
            //  1 会有多套uv，分布在不同的Channel
            //  2 读取纹理坐标的时候，要判断是uv还是uvw
            //

            // GetNumUVChannels:获取当前Mesh有多少套纹理坐标
            // 将不同的Channel的纹理坐标存在了不同的vector<float>里面
            for (uint32_t u = 0; u < mesh->GetNumUVChannels(); ++u)
            {
                if (u >= uvs.size())
                {
                    uvs.push_back(std::vector<float>());
                }
                std::vector<float> &uvComponents = uvs[u];

                // 查看对于当前这个Channel其纹理坐标是uv还是uvw
                // mNumUVComponents 存储了当前第u个Channel所对应的这一套纹理坐标itemSize
                uint32_t numComponents = mesh->mNumUVComponents[u];

                // uv  or  uvw 存下来的原因，是如果将当前的纹理坐标作为attribute传入geometry，在构建
                // attribute的时候，就需要知道itemSize
                if (u >= numUVComponents.size())
                {
                    numUVComponents.push_back(numComponents);
                }

                // 按照numComponents进行遍历读取，要么循环2次即uv，要么循环3次即uvw
                for (uint32_t c = 0; c < numComponents; c++)
                {
                    // mTextureCoords存储着所有的纹理坐标数据
                    // u代表着第u个channel
                    // i代表了读取第i个顶点的数据
                    // c代表了第c个纹理坐标数据
                    uvComponents.push_back(mesh->mTextureCoords[u][i][c]);
                }
            }
        }

        // 读取当前Mesh的Index数据
        // 在aimesh里面，每一个三角形都是一个Face，遍历所有的Face，将其index取出保存
        for (uint32_t f = 0; f < mesh->mNumFaces; f++)
        {
            const aiFace &face = mesh->mFaces[f];

            for (uint32_t id = 0; id < face.mNumIndices; id++)
            {
                // 推入每一个Face的每一个顶点的ID
                indices.push_back(face.mIndices[id]);
            }
        }

        // 设置属性
        geometry->SetAttribute("a_Position", lbAttributef::Create(positions, 3));
        geometry->SetAttribute("a_Normal", lbAttributef::Create(normals, 3));

        // TBN
        if (tangents.size())
        {
            geometry->SetAttribute("a_Tangent", lbAttributef::Create(tangents, 3));
        }

        if (bitangents.size())
        {
            geometry->SetAttribute("a_Bitangent", lbAttributef::Create(bitangents, 3));
        }

        // geometry里面是key-value，key就是attribute的名字，value就是attribute对象
        // 主diffuseMap的uv仍然叫做uv
        // 从第二套纹理坐标开始，都叫做uv1 uv2.....
        std::string uvName;

        // TODO: 实现多套UV
        // 循环每一套纹理坐标
        for (uint32_t uvId = 0; uvId < uvs.size(); ++uvId)
        {
            uvName = "a_UV";
            if (uvId)
            {
                uvName += std::to_string(uvId);
            }

            // uvName : uv  uv1  uv2 uv3....。目前的引擎系统仅支持uv，还没有扩展多套uv的情况
            // 取出uvs[uvId]：第uvId套uv数据vector<float>
            // numUVComponents[uvId]：第uvId套uv的itemSize，可能是2 可能是3
            geometry->SetAttribute(uvName, lbAttributef::Create(uvs[uvId], numUVComponents[uvId]));
        }

        // 设置Index
        geometry->SetIndex(lbAttributei::Create(indices, 1));

        // 纹理设置
        if (mesh->mMaterialIndex >= 0)
        {
            newMesh->mMaterial = materials[mesh->mMaterialIndex];
        }

        return newMesh;
    }

    glm::mat4 lbModelLoader::ToGLMMat4(const aiMatrix4x4 &value)
    {
        glm::mat4 to;
        // the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
        to[0][0] = value.a1;
        to[1][0] = value.a2;
        to[2][0] = value.a3;
        to[3][0] = value.a4;
        to[0][1] = value.b1;
        to[1][1] = value.b2;
        to[2][1] = value.b3;
        to[3][1] = value.b4;
        to[0][2] = value.c1;
        to[1][2] = value.c2;
        to[2][2] = value.c3;
        to[3][2] = value.c4;
        to[0][3] = value.d1;
        to[1][3] = value.d2;
        to[2][3] = value.d3;
        to[3][3] = value.d4;

        return to;
    }

} // namespace Lambix
