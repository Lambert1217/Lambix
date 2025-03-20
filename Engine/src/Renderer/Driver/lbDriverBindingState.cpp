#include "lbDriverBindingState.h"

namespace Lambix
{
    lbDriverBindingState::lbDriverBindingState()
    {
        mVertexArray = lbVertexArray::Create();
    }

    lbDriverBindingState::~lbDriverBindingState()
    {
    }

    lbDriverBindingStates::lbDriverBindingStates(const lbDriverAttributes::Ptr &attributes)
    {
        mAttributes = attributes;
    }

    lbDriverBindingStates::~lbDriverBindingStates()
    {
    }

    void lbDriverBindingStates::setup(const lbGeometry::Ptr &geometry, const lbAttributei::Ptr &index)
    {
        bool updateBufferLayout = false;

        // 先寻找对应lbDriverBindingState, 没有则生成
        auto state = GetBindingState(geometry);
        // 设置为当前lbDriverBindingState，并且绑定vao
        if (mCurrentBindingState != state)
        {
            mCurrentBindingState = state;
            mCurrentBindingState->mVertexArray->Bind();
        }

        updateBufferLayout = NeedsUpdate(geometry, index);
        if (updateBufferLayout)
        {
            SaveCache(geometry, index);
        }

        // 处理EBO
        if (index != nullptr)
        {
            mAttributes->OnUpdate(index, lbBufferType::IndexBuffer);
        }

        // 重新挂钩
        if (updateBufferLayout)
        {
            setupVertexAttributes(geometry);

            // 如果有index 则需要进行ebo的绑定
            if (index != nullptr)
            {
                // 从DriverAttributes里面拿出来indexAttribute对应的DriverAttribute
                auto bkIndex = mAttributes->Get(index);
                // EBO 绑定
                if (bkIndex != nullptr)
                {
                    bkIndex->GetBuffer()->Bind();
                }
            }
        }
    }

    lbDriverBindingState::Ptr lbDriverBindingStates::GetBindingState(const lbGeometry::Ptr &geometry)
    {
        lbDriverBindingState::Ptr state = nullptr;

        auto gKeyIter = mBindingStates.find(geometry->GetID());
        if (gKeyIter == mBindingStates.end())
        {
            gKeyIter = mBindingStates.insert(std::make_pair(geometry->GetID(), lbDriverBindingState::Create())).first;
        }

        state = gKeyIter->second;

        return state;
    }

    bool lbDriverBindingStates::NeedsUpdate(const lbGeometry::Ptr &geometry, const lbAttributei::Ptr &index)
    {
        // id->名字，value->attribute id
        auto cachedAttributes = mCurrentBindingState->mAttributes;

        // id->名字，value->attribute对象
        auto geometryAttributes = geometry->GetAttributes();

        uint32_t attributesNum = 0;
        for (const auto &iter : geometryAttributes)
        {
            auto key = iter.first;
            auto geometryAttribute = iter.second;

            // 从缓存里面寻找，但凡有一个attribute没找到，说明就不一样了
            auto cachedIter = cachedAttributes.find(key);
            if (cachedIter == cachedAttributes.end())
            {
                return true;
            }

            // 从缓存当中，确实找到了这个attribute，那么就得对比id是否一致了
            // 从而确定，同样名字的attribute是否是同一个
            auto cachedAttribute = cachedIter->second;
            if (cachedAttribute != geometryAttribute->GetID())
            {
                return true;
            }

            attributesNum++;
        }

        // 举例：如果旧的geometry有3个属性，新的geometry去掉了一个，就剩下2个了
        if (mCurrentBindingState->mAttributesNum != attributesNum)
        {
            return true;
        }

        // indexAttribute 如果不同，仍然需要重新挂钩
        if (index != nullptr && mCurrentBindingState->mIndex != index->GetID())
        {
            return true;
        }

        // 如果上述结果都一致，那么就说明本geometry并没有变化，则返回不需要重新挂勾
        return false;
    }

    void lbDriverBindingStates::SaveCache(const lbGeometry::Ptr &geometry, const lbAttributei::Ptr &index)
    {
        // 首先清空掉bindingState里面的attributes （Map）
        auto &cachedAttributes = mCurrentBindingState->mAttributes;
        cachedAttributes.clear();

        auto attributes = geometry->GetAttributes();
        uint32_t attributesNum = 0;

        // 遍历geometry的每一个attribute
        for (const auto &iter : attributes)
        {
            auto attribute = iter.second;

            // 插入key-attributeName，value-attributeID
            cachedAttributes.insert(std::make_pair(iter.first, attribute->GetID()));
            attributesNum++;
        }

        mCurrentBindingState->mAttributesNum = attributesNum;

        if (index != nullptr)
        {
            mCurrentBindingState->mIndex = index->GetID();
        }
    }

    void lbDriverBindingStates::setupVertexAttributes(const lbGeometry::Ptr &geometry)
    {
        const auto &geometryAttributes = geometry->GetAttributes();

        for (const auto &iter : geometryAttributes)
        {
            auto name = iter.first;
            auto attribute = iter.second;
            auto dAttribute = mAttributes->Get(attribute);

            // itemSize本attribute有多少个数字，比如position就是3个数字
            auto itemSize = attribute->GetItemSize();

            // 每个单独的数据的类型
            auto dataType = attribute->GetDataType();

            auto bindingIter = LOCATION_MAP.find(name);
            if (bindingIter == LOCATION_MAP.end())
            {
                LOG_WARN("{} not find in LOCATION_MAP", name);
                continue;
            }

            uint32_t binding = bindingIter->second;

            dAttribute->GetBuffer()->Bind();
            mCurrentBindingState->mVertexArray->lbVertexAttribPointer(binding, itemSize, dataType, false, itemSize * GetSize(dataType), (void *)0);
        }
    }

    void lbDriverBindingStates::ReleaseStateOfGeometry(lbUUID id)
    {
        auto iter = mBindingStates.find(id);
        if (iter != mBindingStates.end())
        {
            mBindingStates.erase(iter);
        }
    }
} // namespace Lambix
