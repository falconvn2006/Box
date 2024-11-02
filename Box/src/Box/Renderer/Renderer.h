#pragma once

namespace Box
{
	enum RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		// Get the current API at the runtime
		inline static RendererAPI GetAPI() { return s_RendererAPI; };

		// TODO: Maybe implement a SetAPI function
	private:
		static RendererAPI s_RendererAPI;
	};
}