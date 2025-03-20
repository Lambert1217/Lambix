/**
 * @file lbDriverBindingState.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Core/lbCore.h"
#include "Renderer/Interfaces/lbVertexArray.h"
#include "lbDriverAttribute.h"
#include "Renderer/lbGeometry.h"

namespace Lambix
{
    class lbDriverBindingStates;
    class lbDriverBindingState
    {
        friend class lbDriverBindingStates;

    public:
        lbDriverBindingState();
        ~lbDriverBindingState();

        using Ptr = std::shared_ptr<lbDriverBindingState>;
        static Ptr Create()
        {
            return std::make_shared<lbDriverBindingState>();
        }

    private:
        // VAO
        lbVertexArray::Ptr mVertexArray;
        // 跟cache校验有关
        // 存储了attribute的名字字符串作为key，attribute对象的id做为value
        std::unordered_map<std::string, lbUUID> mAttributes{};

        // 记录了对应的geometry的indexAttribute的id
        lbUUID mIndex{0};

        // 记录了总共有多少个Attribute
        uint32_t mAttributesNum{0};
    };

    class lbDriverBindingStates
    {
    public:
        lbDriverBindingStates(const lbDriverAttributes::Ptr &attributes);
        ~lbDriverBindingStates();

        using lbGeometryKeyMap = std::unordered_map<lbUUID, lbDriverBindingState::Ptr>;

        using Ptr = std::shared_ptr<lbDriverBindingStates>;
        static Ptr Create(const lbDriverAttributes::Ptr &attributes)
        {
            return std::make_shared<lbDriverBindingStates>(attributes);
        }

        /**
         * @brief
         *
         * @param geometry
         * @param index EBO
         */
        void setup(const lbGeometry::Ptr &geometry, const lbAttributei::Ptr &index);

        /**
         * @brief 先寻找geometry是否有对应的lbDriverBindingState 也就是VAO, 如果没有就会创建一个
         *
         * @param geometry
         * @return lbDriverBindingState::Ptr
         */
        lbDriverBindingState::Ptr GetBindingState(const lbGeometry::Ptr &geometry);

        /**
         * @brief 检查当前的vao是否需要重新设置一次与各个vbo之间的挂钩关系
         *          需要重新挂钩的情况：
         *          1 geometry里面的attribute数量发生改变(增多或者减少）
         *          2 geometry里面的key所对应的attribute发生了变化，即调用了setAttribute,由于同样的key更换了新的attribute
         * @param geometry
         * @param index
         * @return true
         * @return false
         */
        bool NeedsUpdate(const lbGeometry::Ptr &geometry, const lbAttributei::Ptr &index);

        /**
         * @brief 如果数据更新了，将数据更新到mCurrentBindingState
         *
         * @param geometry
         * @param index
         */
        void SaveCache(const lbGeometry::Ptr &geometry, const lbAttributei::Ptr &index);

        /**
         * @brief 向VAO灌入数据，仅VBO
         *
         * @param geometry
         */
        void setupVertexAttributes(const lbGeometry::Ptr &geometry);

        /**
         * @brief 根据lbGeometry的id删除对应的lbDriverBindingState
         *
         * @param id  lbGeometry的id
         */
        void ReleaseStateOfGeometry(lbUUID id);

    private:
        lbDriverAttributes::Ptr mAttributes{nullptr};
        lbDriverBindingState::Ptr mCurrentBindingState{nullptr}; // cache
        lbGeometryKeyMap mBindingStates{};
    };
} // namespace Lambix
