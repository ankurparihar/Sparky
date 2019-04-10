#pragma once

#include "window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace sparky {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Sparky_Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	inline Application* CreateApplication() { return new Application(); }

}