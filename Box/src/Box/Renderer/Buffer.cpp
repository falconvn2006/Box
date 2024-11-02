#include "boxpch.h"
#include "Buffer.h"

#include "Box/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Box
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		BOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		BOX_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		BOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		BOX_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}
}