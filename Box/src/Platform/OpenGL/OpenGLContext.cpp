#include "boxpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Box
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		BOX_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}
	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BOX_CORE_ASSERT(status, "Failed to initialize Glad!");

		BOX_CORE_INFO("OpenGL Info: {0} | Renderer : {1} | Version : {2}", (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}