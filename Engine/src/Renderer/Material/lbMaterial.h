/**
 * @file lbMaterial.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "Renderer/Interfaces/lbShader.h"
#include "Renderer/Interfaces/lbTexture.h"
#include "Core/lbCore.h"
#include "glm/glm.hpp"

namespace Lambix
{
    class lbMaterial
    {
    public:
        using Ptr = std::shared_ptr<lbMaterial>;

        virtual ~lbMaterial() = default;

        // 状态管理
        virtual void Bind();
        virtual void Unbind();

        // Shader管理
        void SetShaderProgram(const lbShaderProgram::Ptr &program) { m_shaderProgram = program; }
        std::shared_ptr<lbShaderProgram> GetShaderProgram() const { return m_shaderProgram; }

        // 渲染状态
        RenderState &GetRenderState() { return m_renderState; }
        const RenderState &GetRenderState() const { return m_renderState; }

        // 纹理插槽
        void SetDiffuseMap(const lbTexture2D::Ptr &texture) { m_diffuseMap = texture; }
        void SetNormalMap(const lbTexture2D::Ptr &texture) { m_normalMap = texture; }
        void SetSpecularMap(const lbTexture2D::Ptr &texture) { m_specularMap = texture; }

        // 虚函数接口
        virtual void UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const;
        virtual std::string GetMaterialType() const = 0;

    protected:
        lbShaderProgram::Ptr m_shaderProgram;
        RenderState m_renderState;

        // 基础纹理
        lbTexture2D::Ptr m_diffuseMap{nullptr};
        lbTexture2D::Ptr m_normalMap{nullptr};
        lbTexture2D::Ptr m_specularMap{nullptr};
    };

}
