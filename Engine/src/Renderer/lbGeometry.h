/**
 * @file lbGeometry.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief lbGeometry用来表示一个mesh的基础几何数据，里面包括了Position Color Normal Uv Tangent Bitangent等等的Attribute
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbAttribute.h"
#include "Math/lbBox.h"
#include "Math/lbSphere.h"

namespace Lambix
{
    class lbGeometry : public std::enable_shared_from_this<lbGeometry>
    {

    public:
        lbGeometry();
        virtual ~lbGeometry();

        using lbAttributeMap = std::unordered_map<std::string, lbAttributef::Ptr>;
        using Ptr = std::shared_ptr<lbGeometry>;
        static Ptr Create()
        {
            return std::make_shared<lbGeometry>();
        }

        void SetAttribute(const std::string &name, lbAttributef::Ptr attribute) noexcept;

        lbAttributef::Ptr GetAttribute(const std::string &name) noexcept;

        void SetIndex(const lbAttributei::Ptr &index) noexcept { mIndexAttribute = index; }

        void deleteAttribute(const std::string &name) noexcept;

        bool hasAttribute(const std::string &name) noexcept;

        const lbAttributeMap &GetAttributes() const noexcept { return mAttributes; }

        lbUUID GetID() const noexcept { return mID; }

        auto GetIndex() const noexcept { return mIndexAttribute; }

        void computeBoundingBox() noexcept;

        void computeBoundingSphere() noexcept;

        lbSphere::Ptr GetBoundingSphere() const noexcept { return mBoundingSphere; }
        lbBox::Ptr GetBoundingBox() const noexcept { return mBoundingBox; }

        uint32_t GetLastFrame() const { return mLastFrame; }
        void SetLastFrame(uint32_t frame) { mLastFrame = frame; }

    protected:
        lbUUID mID{0};                   // 全局ID
        uint32_t mLastFrame{0xFFFFFFFF}; // 上一次更新的帧数

        lbAttributeMap mAttributes{};               // 按照名称-值的方式存放了所有本Mesh的Attributes们
        lbAttributei::Ptr mIndexAttribute{nullptr}; // index的Attribute单独存放，并没有加到map里面

        lbBox::Ptr mBoundingBox{nullptr};       // 包围盒
        lbSphere::Ptr mBoundingSphere{nullptr}; // 包围球
    };
} // namespace Lambix
