#pragma once

#include "RenderCommand.h"

namespace Box
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		// Get the current API at the runtime
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	};
}