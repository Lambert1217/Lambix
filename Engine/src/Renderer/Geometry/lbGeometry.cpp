#include "Renderer/Geometry/lbGeometry.h"
#include "Log/lbLog.h"

namespace Lambix
{
    // 构造函数实现
    lbGeometry::lbGeometry()
    {
        m_vertexArray = lbVertexArray::Create();
    }

    // 析构函数实现
    lbGeometry::~lbGeometry()
    {
    }

    // 设置属性
    void lbGeometry::SetAttribute(const std::string &name, const std::shared_ptr<lbVertexBuffer> &buffer)
    {
        m_attributes[name] = buffer;
        m_vertexArray->AddVertexBuffer(buffer);
    }

    // 获取属性
    std::shared_ptr<lbVertexBuffer> lbGeometry::GetAttribute(const std::string &name) const
    {
        auto it = m_attributes.find(name);
        return (it != m_attributes.end()) ? it->second : nullptr;
    }

    // 设置索引缓冲区
    void lbGeometry::SetIndexBuffer(const std::shared_ptr<lbIndexBuffer> &indexBuffer)
    {
        m_vertexArray->SetIndexBuffer(indexBuffer);
    }

    // 计算包围盒
    void lbGeometry::ComputeBoundingBox()
    {
        auto posBuffer = GetAttribute("a_Position");
        if (!posBuffer)
        {
            LOG_ERROR("No a_Position buffer found!");
            return;
        }

        if (!m_boundingBox)
        {
            m_boundingBox = lbBox::Create();
        }

        m_boundingBox->setFromBuffer(posBuffer);

        // LOG_TRACE("m_boundingBox: ({}, {}, {}) -- ({}, {}, {})", m_boundingBox->m_Min.x, m_boundingBox->m_Min.y, m_boundingBox->m_Min.z,
        //           m_boundingBox->m_Max.x, m_boundingBox->m_Max.y, m_boundingBox->m_Max.z);
    }

    // 计算包围球
    void lbGeometry::ComputeBoundingSphere()
    {
        ComputeBoundingBox();
        if (m_boundingSphere == nullptr)
        {
            m_boundingSphere = lbSphere::Create(glm::vec3(0.0f), 0.0f);
        }
        // 共用中心
        m_boundingSphere->m_Center = m_boundingBox->GetCenter();

        auto posBuffer = GetAttribute("a_Position");
        uint32_t count = posBuffer->GetDataSize() / posBuffer->GetElement().Size;
        float *position = (float *)posBuffer->GetData();
        // 找到距离当前球心最大距离的点
        float maxRadiusSq = 0;
        for (uint32_t i = 0; i < count; ++i)
        {
            // 把每个顶点的xyz装成一个point
            glm::vec3 point = glm::vec3(position[3 * i], position[3 * i + 1], position[3 * i + 2]);

            // 计算point到center的距离
            glm::vec3 radiusVector = m_boundingSphere->m_Center - point;

            // 原本应该对比每一个点到center的距离，找到最大。但是计算向量长度，必须经过开方这个运算
            // 为了性能考虑，直接记录其平方，最后得到最大值，再开二次方
            maxRadiusSq = std::max(glm::dot(radiusVector, radiusVector), maxRadiusSq);
        }

        // 开方求取radius
        m_boundingSphere->m_Radius = std::sqrt(maxRadiusSq);

        // LOG_TRACE("m_boundingSphere: ({}, {}) {}", m_boundingSphere->m_Center.x, m_boundingSphere->m_Center.y, m_boundingSphere->m_Radius);
    }
}