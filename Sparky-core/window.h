#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Events/Event.h"

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

namespace sparky {
	namespace graphics {
		class Window {
		private:
			friend struct GLFWwindow;
			const char* m_Title;
			int m_Width, m_Height;
			GLFWwindow* m_Window;
			bool m_Closed;
			bool m_Keys[MAX_KEYS];
			bool m_Buttons[MAX_BUTTONS];
			double mx, my;
		public:
			bool* options;
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void clear() const;
			void update();

			friend void window_resize(GLFWwindow* window, int width, int height);

			inline int getWidth() const { return m_Width; };
			inline int getHeight() const { return m_Height; };

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;
		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Sparky Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Sparky_Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Sparky_Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Sparky_Window* Create(const WindowProps& props = WindowProps());
	};

}