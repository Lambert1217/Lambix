/**
 ***************************************************************
 * @file            : lbBuffer.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Core/Renderer/lbBuffer.h"
#include "Core/Base/lbLog.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLBuffer.h"
#endif

namespace Lambix
{

	std::shared_ptr<lbVertexBuffer> lbVertexBuffer::Create(void *data, uint32_t size, const lbBufferElement &element)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLVertexBuffer>(data, size, element);
#endif
	}

	std::shared_ptr<lbIndexBuffer> lbIndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLIndexBuffer>(indices, count);
#endif
	}

	uint32_t ShaderDataTypeSize(lbShaderDataType type)
	{
		switch (type)
		{
		case lbShaderDataType::Float:
			return 4;
		case lbShaderDataType::Float2:
			return 4 * 2;
		case lbShaderDataType::Float3:
			return 4 * 3;
		case lbShaderDataType::Float4:
			return 4 * 4;
		case lbShaderDataType::Mat3:
			return 4 * 3 * 3;
		case lbShaderDataType::Mat4:
			return 4 * 4 * 4;
		case lbShaderDataType::Int:
			return 4;
		case lbShaderDataType::Int2:
			return 4 * 2;
		case lbShaderDataType::Int3:
			return 4 * 3;
		case lbShaderDataType::Int4:
			return 4 * 4;
		case lbShaderDataType::Bool:
			return 1;
		case lbShaderDataType::None:
			break;
		}

		LOG_ASSERT(false, "Unknown lbShaderDataType!");
		return 0;
	}

	lbBufferElement::lbBufferElement(const std::string &name, lbShaderDataType type, uint32_t index, bool normalized)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Normalized(normalized), Index(index)
	{
	}

	uint32_t lbBufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case lbShaderDataType::Float:
			return 1;
		case lbShaderDataType::Float2:
			return 2;
		case lbShaderDataType::Float3:
			return 3;
		case lbShaderDataType::Float4:
			return 4;
		case lbShaderDataType::Mat3:
			return 3 * 3;
		case lbShaderDataType::Mat4:
			return 4 * 4;
		case lbShaderDataType::Int:
			return 1;
		case lbShaderDataType::Int2:
			return 2;
		case lbShaderDataType::Int3:
			return 3;
		case lbShaderDataType::Int4:
			return 4;
		case lbShaderDataType::Bool:
			return 1;
		case lbShaderDataType::None:
			break;
		}

		LOG_ASSERT(false, "Unknown lbShaderDataType!");
		return 0;
	}
} // Lambix