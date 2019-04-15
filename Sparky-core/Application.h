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
		inline void quitApplication() { m_Running = false; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Sparky_Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	public:
		static Application* s_Instance;
		int DemoIndex;
		bool WireFrameMode;
	public:
		void next_demo();
		void prev_demo();
		void flip_wireframe_mode();
		void swap_demo(int i);
	};

	// To be defined in CLIENT
	inline Application* CreateApplication() { return new Application(); }

}