#pragma once

#include "window.h"
#include "LayerStack.h"

// #include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"

namespace sparky {

	// Application class
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
		Camera* camera;
		bool resetCamera;
		int DemoIndex;
		bool WireFrameMode;
		bool z_bufffer;
		int scr_width, scr_height;
		bool mouseLookAround;
		int mouseClicksL, mouseClicksR;
		float time;
		float color_r, color_g, color_b, color_a;
	public:
		void next_demo();
		void prev_demo();
		void flip_wireframe_mode();
		void flip_z_buffer();
		void swap_demo(int i);
	public:
		// case specific variables
		bool case_8_order;
		bool case_9_multi;
		bool case_13_rotate;
		float case_13_radius, case_13_theta, case_13_phi, case_13_speed;
		int case_14_mat;
	};

	// To be defined in CLIENT
	inline Application* CreateApplication() { return new Application(); }

}