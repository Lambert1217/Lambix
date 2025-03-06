#include "Renderer/Geometry/lbCubeGeometry.h"

namespace Lambix
{
    lbCubeGeometry::Ptr lbCubeGeometry::Create(float size)
    {
        return std::make_shared<lbCubeGeometry>(size);
    }

    lbCubeGeometry::lbCubeGeometry(float size)
    {
        GenerateVertexData(size);
        ComputeBoundingSphere();
    }

    void lbCubeGeometry::GenerateVertexData(float size)
    {
        const float half = size * 0.5f;

        // 分离的顶点属性数组
        std::vector<glm::vec3> positions(24);
        std::vector<glm::vec3> normals(24);
        std::vector<glm::vec2> texCoords(24);
        std::vector<glm::vec3> tangents(24);

        // 前面 (Z+)
        positions[0] = {half, half, half};
        normals[0] = {0, 0, 1};
        texCoords[0] = {1, 1};
        positions[1] = {-half, half, half};
        normals[1] = {0, 0, 1};
        texCoords[1] = {0, 1};
        positions[2] = {-half, -half, half};
        normals[2] = {0, 0, 1};
        texCoords[2] = {0, 0};
        positions[3] = {half, -half, half};
        normals[3] = {0, 0, 1};
        texCoords[3] = {1, 0};
        for (int i = 0; i < 4; ++i)
        {
            tangents[i] = glm::vec3(1.0f, 0.0f, 0.0f);
        }

        // 后面 (Z-)
        positions[4] = {half, half, -half};
        normals[4] = {0, 0, -1};
        texCoords[4] = {0, 1};
        positions[5] = {half, -half, -half};
        normals[5] = {0, 0, -1};
        texCoords[5] = {0, 0};
        positions[6] = {-half, -half, -half};
        normals[6] = {0, 0, -1};
        texCoords[6] = {1, 0};
        positions[7] = {-half, half, -half};
        normals[7] = {0, 0, -1};
        texCoords[7] = {1, 1};
        for (int i = 4; i < 8; ++i)
        {
            tangents[i] = glm::vec3(-1.0f, 0.0f, 0.0f);
        }

        // 左面 (X-)
        positions[8] = {-half, half, half};
        normals[8] = {-1, 0, 0};
        texCoords[8] = {1, 1};
        positions[9] = {-half, half, -half};
        normals[9] = {-1, 0, 0};
        texCoords[9] = {0, 1};
        positions[10] = {-half, -half, -half};
        normals[10] = {-1, 0, 0};
        texCoords[10] = {0, 0};
        positions[11] = {-half, -half, half};
        normals[11] = {-1, 0, 0};
        texCoords[11] = {1, 0};
        for (int i = 8; i < 12; ++i)
        {
            tangents[i] = glm::vec3(0.0f, 0.0f, 1.0f);
        }

        // 右面 (X+)
        positions[12] = {half, half, half};
        normals[12] = {1, 0, 0};
        texCoords[12] = {0, 1};
        positions[13] = {half, -half, half};
        normals[13] = {1, 0, 0};
        texCoords[13] = {0, 0};
        positions[14] = {half, -half, -half};
        normals[14] = {1, 0, 0};
        texCoords[14] = {1, 0};
        positions[15] = {half, half, -half};
        normals[15] = {1, 0, 0};
        texCoords[15] = {1, 1};
        for (int i = 12; i < 16; ++i)
        {
            tangents[i] = glm::vec3(0.0f, 0.0f, -1.0f);
        }

        // 顶面 (Y+)
        positions[16] = {-half, half, half};
        normals[16] = {0, 1, 0};
        texCoords[16] = {0, 1};
        positions[17] = {half, half, half};
        normals[17] = {0, 1, 0};
        texCoords[17] = {1, 1};
        positions[18] = {half, half, -half};
        normals[18] = {0, 1, 0};
        texCoords[18] = {1, 0};
        positions[19] = {-half, half, -half};
        normals[19] = {0, 1, 0};
        texCoords[19] = {0, 0};
        for (int i = 16; i < 20; ++i)
        {
            tangents[i] = glm::vec3(1.0f, 0.0f, 0.0f);
        }

        // 底面 (Y-)
        positions[20] = {-half, -half, half};
        normals[20] = {0, -1, 0};
        texCoords[20] = {1, 0};
        positions[21] = {-half, -half, -half};
        normals[21] = {0, -1, 0};
        texCoords[21] = {1, 1};
        positions[22] = {half, -half, -half};
        normals[22] = {0, -1, 0};
        texCoords[22] = {0, 1};
        positions[23] = {half, -half, half};
        normals[23] = {0, -1, 0};
        texCoords[23] = {0, 0};
        for (int i = 20; i < 24; ++i)
        {
            tangents[i] = glm::vec3(1.0f, 0.0f, 0.0f);
        }

        // 创建分离的属性缓冲区
        auto posBuffer = lbVertexBuffer::Create(
            positions.data(),
            positions.size() * sizeof(glm::vec3),
            lbBufferElement("a_Position", lbShaderDataType::Float3, 0));

        auto normalBuffer = lbVertexBuffer::Create(
            normals.data(),
            normals.size() * sizeof(glm::vec3),
            lbBufferElement("a_Normal", lbShaderDataType::Float3, 1));

        auto texBuffer = lbVertexBuffer::Create(
            texCoords.data(),
            texCoords.size() * sizeof(glm::vec2),
            lbBufferElement("a_TexCoord", lbShaderDataType::Float2, 2));
        // 创建切线缓冲区
        auto tangentBuffer = lbVertexBuffer::Create(
            tangents.data(),
            tangents.size() * sizeof(glm::vec3),
            lbBufferElement("a_Tangent", lbShaderDataType::Float3, 3));

        // 设置顶点属性
        SetAttribute("a_Position", posBuffer);
        SetAttribute("a_Normal", normalBuffer);
        SetAttribute("a_TexCoord", texBuffer);
        SetAttribute("a_Tangent", tangentBuffer);

        // 索引数据（保持不变）
        uint32_t indices[] = {
            0, 1, 2, 0, 2, 3,       // Front
            4, 5, 6, 4, 6, 7,       // Back
            8, 9, 10, 8, 10, 11,    // Left
            12, 13, 14, 12, 14, 15, // Right
            16, 17, 18, 16, 18, 19, // Top
            20, 21, 22, 20, 22, 23  // Bottom
        };

        auto indexBuffer = lbIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        SetIndexBuffer(indexBuffer);
    }

}