#pragma once

#include "Box/Layer.h"
#include "Box/Events/ApplicationEvent.h"
#include "Box/Events/KeyEvent.h"
#include "Box/Events/MouseEvent.h"

namespace Box
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}