#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController((1280.0f / 720.0f), true)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVertexArray = Box::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Box::Ref<Box::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer.reset(Box::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVertexBuffer->SetLayout({
		{ Box::ShaderDataType::Float3, "a_Position" },
		});
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

	unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Box::Ref<Box::IndexBuffer> squareIndexBuffer;
	squareIndexBuffer.reset(Box::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

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

	m_Shader = Box::Shader::Create("FlatColorVertexShader", flatColorVertexSource, flatColorFragmentSource);
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Box::TimeStep ts)
{
	// Update camera controller
	m_CameraController.OnUpdate(ts);

	// Render
	m_TimeStep = ts;

	// Seting the background color
	Box::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Box::RenderCommand::Clear();

	Box::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Box::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Box::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Box::Renderer::Submit(m_Shader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Box::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Debug Info");

	ImGui::Text("Delta Time: %.3fs (%.3fms)", m_TimeStep, m_TimeStep * 1000.0f);

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Box::Event& e)
{
	m_CameraController.OnEvent(e);
}
