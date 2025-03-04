#include "Core/Math/lbBox.h"
#include "Core/Renderer/lbBuffer.h"
#include "Core/Base/lbLog.h"

namespace Lambix
{
    lbBox::Ptr lbBox::Create()
    {
        return std::make_shared<lbBox>();
    }

    bool lbBox::isEmpty()
    {
        return (m_Min.x > m_Max.x || m_Min.y > m_Max.y || m_Min.y > m_Max.y);
    }

    glm::vec3 lbBox::GetCenter()
    {
        if (isEmpty())
        {
            return glm::vec3(0.0f);
        }
        return (m_Min + m_Max) / 2.0f;
    }

    void lbBox::setFromBuffer(const std::shared_ptr<lbVertexBuffer> &buffer)
    {
        auto element = buffer->GetElement();
        if (element.Type != lbShaderDataType::Float3)
        {
            LOG_ERROR("Buffer element type is not Float3!");
            return;
        }
        int count = buffer->GetDataSize() / element.Size;
        float *data = (float *)buffer->GetData();

        for (int i = 0; i < count; ++i)
        {
            float x = data[i * 3];
            float y = data[i * 3 + 1];
            float z = data[i * 3 + 2];

            if (x < m_Min.x)
                m_Min.x = x;
            if (y < m_Min.y)
                m_Min.y = y;
            if (z < m_Min.z)
                m_Min.z = z;
            if (x > m_Max.x)
                m_Max.x = x;
            if (y > m_Max.y)
                m_Max.y = y;
            if (z > m_Max.z)
                m_Max.z = z;
        }
    }
}