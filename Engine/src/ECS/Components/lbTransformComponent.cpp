#include "lbTransformComponent.h"
#include "ECS/lbEntity.h"

namespace Lambix
{
    lbTransformComponent::lbTransformComponent()
    {
        m_Transform.BindDirtyCallback([this]()
                                      { SetDirty(); });
    }

    void lbTransformComponent::OnUpdate(lbTimestep ts)
    {
        // 不脏直接返回
        if (!m_Transform.IsDirty())
            return;
        // 若为脏，则更新世界矩阵
        auto parent = m_Entity.lock()->GetParent();
        if (!parent)
        {
            // 没有父实体，默认参数更新
            m_Transform.UpdateWorldMatrix();
        }
        else
        {
            // 若有父实体，先去更新父实体，并用父实体的世界矩阵更新该实体的世界矩阵
            auto &parentTrans = parent->GetComponent<lbTransformComponent>();
            parentTrans.OnUpdate(ts);
            m_Transform.UpdateWorldMatrix(parentTrans.m_Transform.GetWorldMatrix());
        }
    }
    void lbTransformComponent::SetDirty()
    {
        // 更新子实体
        auto children = m_Entity.lock()->GetChildren();
        for (auto child : children)
        {
            child->GetComponent<lbTransformComponent>().m_Transform.SetDirty();
        }
    }
}
