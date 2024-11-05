#include "boxpch.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "RenderCommand.h"

namespace Box
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}