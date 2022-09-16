#include "bph.h"
#include "WindowsWindow.h"


namespace Box 
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) 
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() 
	{
		Shutdown();
	}

	void error_callback(int error, const char* msg) 
	{
		std::string s;
		s = " [" + std::to_string(error) + "] " + msg + '\n';
		BOX_CORE_ERROR(s);
	}

	void WindowsWindow::Init(const WindowProps& props) 
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		BOX_CORE_INFO("Creating window {0} ({1} x {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) 
		{
			// TODO: glfw terminate on system shutdown

			glfwSetErrorCallback(error_callback);
			
			int success = glfwInit();

			//BOX_CORE_INFO(success);
			BOX_CORE_ASSERT(success, "Could not initialize GLFW!")

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		if (m_Window == NULL) 
		{
			BOX_CORE_INFO("NULL");
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);
	}

	void WindowsWindow::Shutdown() 
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() 
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVsync(bool enabled) 
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.Vsync = enabled;
	}

	bool WindowsWindow::IsVsync() const 
	{
		return m_Data.Vsync;
	}
}