#pragma once

#include <imgui/imgui.h>
#include "platform/OpenGL/imgui_impl_opengl3.h"
#include "Application.h"

namespace sparky {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
	};

}