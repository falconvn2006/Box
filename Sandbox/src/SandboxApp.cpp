#include<Box.h>
#include <Box/Core/Entrypoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Box::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController((1280.0f / 720.0f), true)
	{
		m_VertexArray = Box::VertexArray::Create();

		// vertices[3dCords, verticesAmount]
		// vertices index is import. It will render strictly by it
		// Vertices of the triangle
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Box::Ref<Box::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Box::VertexBuffer::Create(vertices, sizeof(vertices)));
		Box::BufferLayout layout = {
			{ Box::ShaderDataType::Float3, "a_Position"},
			{ Box::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Box::Ref<Box::IndexBuffer> indexBuffer;
		unsigned int indices[3] = { 0, 1, 2 };
		indexBuffer.reset(Box::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//
		m_SquareVertexArray = Box::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Box::Ref<Box::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Box::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->SetLayout({
			{ Box::ShaderDataType::Float3, "a_Position" },
			{ Box::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Box::Ref<Box::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Box::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0); 
				color = v_Color;
			}
		)";

		m_Shader = Box::Shader::Create("VertexColorTriangle", vertexSource, fragmentSource);

		std::string flatColorVertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0); 
			}
		)";

		m_FlatColorShader = Box::Shader::Create("FlatColorVertexShader", flatColorVertexSource, flatColorFragmentSource);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/texture.glsl");

		m_Texture = Box::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoTexture = Box::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Box::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Box::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Box::TimeStep ts) override
	{
		m_CameraController.OnUpdate(ts);

		/*BOX_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMiliSeconds());*/
		m_TimeStep = ts;

		// Seting the background color
		Box::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Box::RenderCommand::Clear();

		Box::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;

				if (y % 2 != 0 && x % 2 == 0)
				{
					std::dynamic_pointer_cast<Box::OpenGLShader>(m_FlatColorShader)->Bind();
					std::dynamic_pointer_cast<Box::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor2);
				}
				else
				{
					std::dynamic_pointer_cast<Box::OpenGLShader>(m_FlatColorShader)->Bind();
					std::dynamic_pointer_cast<Box::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
				}

				Box::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("texture");

		m_Texture->Bind();
		Box::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoTexture->Bind();
		Box::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle rendering
		/*Box::Renderer::Submit(m_Shader, m_VertexArray);*/

		Box::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Debug Info");

		ImGui::Text("Delta Time: %.3fs (%.3fms)", m_TimeStep, m_TimeStep*1000.0f);

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Box::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	Box::ShaderLibrary m_ShaderLibrary;

	Box::Ref<Box::Shader> m_Shader;
	Box::Ref<Box::VertexArray> m_VertexArray;

	Box::Ref<Box::Shader> m_FlatColorShader;
	Box::Ref<Box::VertexArray> m_SquareVertexArray;

	Box::Ref<Box::Texture2D> m_Texture, m_ChernoTexture;

	Box::OrthographicCameraController m_CameraController;

	float m_TimeStep;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_SquareColor2 = { 0.2f, 0.5f, 0.8f };
};

class Sandbox : public Box::Application
{
public:
	Sandbox()
	{
		/*PushLayer(new ExampleLayer());*/
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Box::Application* Box::CreateApplication()
{
	return new Sandbox();
}