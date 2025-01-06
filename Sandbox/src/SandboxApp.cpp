#include<Box.h>
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Box::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Box::VertexArray::Create());

		// vertices[3dCords, verticesAmount]
		// vertices index is import. It will render strictly by it

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Box::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Box::VertexBuffer::Create(vertices, sizeof(vertices)));
		Box::BufferLayout layout = {
			{ Box::ShaderDataType::Float3, "a_Position"},
			{ Box::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<Box::IndexBuffer> indexBuffer;
		unsigned int indices[3] = { 0, 1, 2 };
		indexBuffer.reset(Box::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//
		m_SquareVertexArray.reset(Box::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
		};

		std::shared_ptr<Box::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Box::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->SetLayout({
			{ Box::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Box::IndexBuffer> squareIndexBuffer;
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

		m_Shader.reset(new Box::Shader(vertexSource, fragmentSource));

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

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color; 
			}
		)";

		m_FlatColorShader.reset(new Box::Shader(flatColorVertexSource, flatColorFragmentSource));
	}

	void OnUpdate(Box::TimeStep ts) override
	{
		/*BOX_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMiliSeconds());*/
		m_TimeStep = ts;

		// Camera Controls
		if (Box::Input::IsKeyPressed(BOX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		else if (Box::Input::IsKeyPressed(BOX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * ts;

		if (Box::Input::IsKeyPressed(BOX_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * ts;
		else if (Box::Input::IsKeyPressed(BOX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * ts;

		if (Box::Input::IsKeyPressed(BOX_KEY_Q))
			m_Rotation -= m_CameraRotationSpeed * ts;
		else if (Box::Input::IsKeyPressed(BOX_KEY_E))
			m_Rotation += m_CameraRotationSpeed * ts;

		// Seting the background color
		Box::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Box::RenderCommand::Clear();

		m_Camera.SetRotation(m_Rotation);
		m_Camera.SetPosition(m_CameraPosition);

		Box::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		// Seting the color to test the shader
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;

				if (x % 2 == 0)
					m_FlatColorShader->UploadUniformFloat4("u_Color", redColor);
				else
					m_FlatColorShader->UploadUniformFloat4("u_Color", blueColor);

				Box::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		Box::Renderer::Submit(m_Shader, m_VertexArray);

		Box::Renderer::EndScene();

		if(m_Toogle)
			m_Rotation += m_CameraRotationSpeed * 100;
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Debug Info");

		ImGui::Text("Delta Time: %.3fs (%.3fms)", m_TimeStep, m_TimeStep*1000.0f);

		ImGui::End();
	}

	void OnEvent(Box::Event& event) override
	{
		if (event.GetEventType() == Box::EventType::KeyPressed)
		{
			Box::KeyPressedEvent& e = (Box::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BOX_KEY_P)
			{
				if (m_Toogle)
					m_Toogle = false;
				else
					m_Toogle = true;
			}
		}
	}

private:
	std::shared_ptr<Box::Shader> m_Shader;
	std::shared_ptr<Box::VertexArray> m_VertexArray;

	std::shared_ptr<Box::Shader> m_FlatColorShader;
	std::shared_ptr<Box::VertexArray> m_SquareVertexArray;

	Box::OrthographicCamera m_Camera;
	
	glm::vec3 m_CameraPosition;
	float m_Rotation = 0.0f;

	float m_CameraSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;

	float m_TimeStep;

	bool m_Toogle = false;
};

class Sandbox : public Box::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Box::Application* Box::CreateApplication()
{
	return new Sandbox();
}