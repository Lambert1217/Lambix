/**
 ***************************************************************
 * @file            : lbOpenGLBackend.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Backend/OpenGL/lbOpenGLBackend.h"
#include "glad/glad.h"
#include "lbOpenGLBackend.h"

namespace Lambix
{
	// OpenGL枚举转换辅助函数
	namespace
	{
		GLenum ConvertFrontFace(FrontFace face)
		{
			switch (face)
			{
			case FrontFace::Clockwise:
				return GL_CW;
			case FrontFace::CounterClockwise:
				return GL_CCW;
			default:
				return GL_CCW;
			}
		}

		GLenum ConvertPolygonMode(PolygonMode mode)
		{
			switch (mode)
			{
			case PolygonMode::Fill:
				return GL_FILL;
			case PolygonMode::Line:
				return GL_LINE;
			case PolygonMode::Point:
				return GL_POINT;
			default:
				return GL_FILL;
			}
		}

		GLenum ConvertBlendFactor(BlendFactor factor)
		{
			switch (factor)
			{
			case BlendFactor::Zero:
				return GL_ZERO;
			case BlendFactor::One:
				return GL_ONE;
			case BlendFactor::SrcColor:
				return GL_SRC_COLOR;
			case BlendFactor::OneMinusSrcColor:
				return GL_ONE_MINUS_SRC_COLOR;
			case BlendFactor::DstColor:
				return GL_DST_COLOR;
			case BlendFactor::OneMinusDstColor:
				return GL_ONE_MINUS_DST_COLOR;
			case BlendFactor::SrcAlpha:
				return GL_SRC_ALPHA;
			case BlendFactor::OneMinusSrcAlpha:
				return GL_ONE_MINUS_SRC_ALPHA;
			default:
				return GL_SRC_ALPHA;
			}
		}

		GLenum ConvertDepthFunc(DepthFunc func)
		{
			switch (func)
			{
			case DepthFunc::Never:
				return GL_NEVER;
			case DepthFunc::Less:
				return GL_LESS;
			case DepthFunc::Equal:
				return GL_EQUAL;
			case DepthFunc::LessEqual:
				return GL_LEQUAL;
			case DepthFunc::Greater:
				return GL_GREATER;
			case DepthFunc::NotEqual:
				return GL_NOTEQUAL;
			case DepthFunc::Always:
				return GL_ALWAYS;
			default:
				return GL_LESS;
			}
		}

		GLenum ConvertCullFace(CullFace face)
		{
			switch (face)
			{
			case CullFace::Front:
				return GL_FRONT;
			case CullFace::Back:
				return GL_BACK;
			case CullFace::FrontAndBack:
				return GL_FRONT_AND_BACK;
			default:
				return GL_BACK;
			}
		}

		GLenum ConvertDrawMode(DrawMode mode)
		{
			switch (mode)
			{
			case DrawMode::Points:
				return GL_POINTS;
			case DrawMode::Lines:
				return GL_LINES;
			case DrawMode::LineStrip:
				return GL_LINE_STRIP;
			case DrawMode::LineLoop:
				return GL_LINE_LOOP;
			case DrawMode::Triangles:
				return GL_TRIANGLES;
			case DrawMode::TriangleStrip:
				return GL_TRIANGLE_STRIP;
			case DrawMode::TriangleFan:
				return GL_TRIANGLE_FAN;
			default:
				return GL_TRIANGLES;
			}
		}
	}

	void lbOpenGLBackend::Init()
	{
		// 初始化默认状态
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
	}

	void lbOpenGLBackend::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void lbOpenGLBackend::SetClearColor(const glm::vec4 &color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void lbOpenGLBackend::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	// Depth State
	void lbOpenGLBackend::SetDepthTest(bool flag)
	{
		flag ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void lbOpenGLBackend::SetDepthWrite(bool flag)
	{
		glDepthMask(flag ? GL_TRUE : GL_FALSE);
	}

	void lbOpenGLBackend::SetDepthFunc(DepthFunc func)
	{
		glDepthFunc(ConvertDepthFunc(func));
	}

	// Blend State
	void lbOpenGLBackend::SetBlend(bool flag)
	{
		flag ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
	}

	void lbOpenGLBackend::SetBlendFunc(BlendFactor src, BlendFactor dst)
	{
		glBlendFunc(ConvertBlendFactor(src), ConvertBlendFactor(dst));
	}

	// Cull Face
	void lbOpenGLBackend::SetCullFace(bool flag)
	{
		flag ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}

	void lbOpenGLBackend::SetCullFace(CullFace face)
	{
		glCullFace(ConvertCullFace(face));
	}

	void lbOpenGLBackend::SetFrontFace(FrontFace face)
	{
		glFrontFace(ConvertFrontFace(face));
	}

	// Polygon Mode
	void lbOpenGLBackend::SetPolygonMode(PolygonMode mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, ConvertPolygonMode(mode));
	}

	// Render State
	void lbOpenGLBackend::SetRenderState(const RenderState &state)
	{
		// Depth
		SetDepthTest(state.depthTest);
		SetDepthFunc(state.depthFunc);
		SetDepthWrite(state.depthWrite);

		// Blend
		SetBlend(state.blendEnable);
		SetBlendFunc(state.srcFactor, state.dstFactor);

		// Cull Face
		SetCullFace(state.cullEnable);
		SetCullFace(state.cullFace);
		SetFrontFace(state.frontFace);

		// Polygon Mode
		SetPolygonMode(state.polygonMode);
	}

	// Draw
	void lbOpenGLBackend::DrawIndexed(DrawMode DrawMode, uint32_t count)
	{
		glDrawElements(ConvertDrawMode(DrawMode), count, GL_UNSIGNED_INT, nullptr);
	}
	void lbOpenGLBackend::DrawArray(DrawMode DrawMode, uint32_t count)
	{
		glDrawArrays(ConvertDrawMode(DrawMode), 0, count);
	}
}
