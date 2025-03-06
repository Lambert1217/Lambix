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
#include "Renderer/lbShader.h"
#include "Renderer/lbTexture.h"
#include "Core/lbCore.h"

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
        void SetShaderProgram(const std::shared_ptr<lbShaderProgram> &program) { m_shaderProgram = program; }
        std::shared_ptr<lbShaderProgram> GetShaderProgram() const { return m_shaderProgram; }

        RenderState &GetRenderState() { return m_renderState; }
        const RenderState &GetRenderState() const { return m_renderState; }

        // 纹理插槽
        void SetDiffuseMap(const std::shared_ptr<lbTexture> &texture) { m_diffuseMap = texture; }
        void SetNormalMap(const std::shared_ptr<lbTexture> &texture) { m_normalMap = texture; }
        void SetSpecularMap(const std::shared_ptr<lbTexture> &texture) { m_specularMap = texture; }

        // 虚函数接口
        virtual void UpdateUniforms() const = 0;
        virtual std::string GetMaterialType() const = 0;

    protected:
        std::shared_ptr<lbShaderProgram> m_shaderProgram;
        RenderState m_renderState;

        // 基础纹理
        std::shared_ptr<lbTexture> m_diffuseMap{nullptr};
        std::shared_ptr<lbTexture> m_normalMap{nullptr};
        std::shared_ptr<lbTexture> m_specularMap{nullptr};
    };

}
