#pragma once

#include "window.h"
#include "LayerStack.h"

namespace sparky {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void clear() const;
		void update();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Sparky_Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Sparky_Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	inline Application* CreateApplication() { return new Application(); }

}