#pragma once

#include <Box.h>

class Sandbox2D : public Box::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Box::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Box::Event& e) override;
private:
	Box::OrthographicCameraController m_CameraController;
	
	float m_TimeStep;

	// Temp
	Box::Ref<Box::VertexArray> m_SquareVertexArray;
	Box::Ref<Box::Shader> m_Shader;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};