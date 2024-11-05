#include<Box.h>
#include "imgui/imgui.h"

class ExampleLayer : public Box::Layer
{
public:
	ExampleLayer() 
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), Layer("Example")
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
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f,
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

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * vec4(a_Position, 1.0);
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

		std::string blueVertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ProjectionView;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ProjectionView * vec4(a_Position, 1.0);
			}
		)";

		std::string blueFragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0); 
			}
		)";

		m_BlueShader.reset(new Box::Shader(blueVertexSource, blueFragmentSource));
	}

	void OnUpdate() override
	{
		if (Box::Input::IsKeyPressed(BOX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed;
		else if (Box::Input::IsKeyPressed(BOX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed;

		if (Box::Input::IsKeyPressed(BOX_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed;
		else if (Box::Input::IsKeyPressed(BOX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed;

		if (Box::Input::IsKeyPressed(BOX_KEY_R))
			m_Rotation -= m_CameraRotationSpeed;
		else if (Box::Input::IsKeyPressed(BOX_KEY_E))
			m_Rotation += m_CameraRotationSpeed;

		Box::RenderCommand::SetClearColor({ 0.55, 0.197, 0.175, 1 });
		Box::RenderCommand::Clear();

		m_Camera.SetRotation(m_Rotation);
		m_Camera.SetPosition(m_CameraPosition);

		Box::Renderer::BeginScene(m_Camera);

		Box::Renderer::Submit(m_BlueShader, m_SquareVertexArray);
		Box::Renderer::Submit(m_Shader, m_VertexArray);

		Box::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		
	}

	void OnEvent(Box::Event& event) override
	{
	}

private:
	std::shared_ptr<Box::Shader> m_Shader;
	std::shared_ptr<Box::VertexArray> m_VertexArray;

	std::shared_ptr<Box::Shader> m_BlueShader;
	std::shared_ptr<Box::VertexArray> m_SquareVertexArray;

	Box::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_Rotation = 0.0f;
	float m_CameraSpeed = 0.1f;
	float m_CameraRotationSpeed = 0.2f;
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