#include "window.h"

namespace sparky {
	namespace graphics {

		// bool Window::m_Keys[MAX_KEYS];
		// bool Window::m_Buttons[MAX_BUTTONS];
		// double Window::mx, Window::my;

		void window_resize(GLFWwindow* window, int width, int height);

		Window::Window(const char *title, int width, int height) {
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!init()) {
				glfwTerminate();
			}
			for (int i = 0; i < MAX_KEYS; ++i) {
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; ++i) {
				m_Buttons[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::init() {
			/* Initialize the library */
			if (!glfwInit()) {
				std::cout << "Failed to initialize glfw!" << std::endl;
				return false;
			}
			
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			/* Create a windowed mode window and its OpenGL context */
			if (!m_Window) {
				glfwTerminate();
				std::cout << "Failed to create window!" << std::endl;
				return false;
			}

			/* Make the window's context current */
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_pos_callback);

			// if (glewInit() != GLEW_OK) {
			// 	std::cout << "Could not initialize GLEW!" << std::endl;
			// 	return false;
			// }

			std::cout << glGetString(GL_VERSION) << std::endl;

			return true;
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwPollEvents();
			// glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			// glViewport(0, 0, m_Width, m_Height);
			glfwSwapBuffers(m_Window);
		}

		void window_resize(GLFWwindow* window, int width, int height){
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			glfwGetFramebufferSize(window, &win->m_Width, &win->m_Height);
			glViewport(0, 0, width, height);
		}

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = (action != GLFW_RELEASE);
		}

		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Buttons[button] = (action != GLFW_RELEASE);
		}

		static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

		bool Window::isKeyPressed(unsigned int keycode) const {
			if (keycode >= MAX_KEYS) {
				return false;
			}
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const {
			if (button >= MAX_BUTTONS) {
				return false;
			}
			return m_Buttons[button];
		}
		void Window::getMousePosition(double& x, double& y) const {
			x = mx;
			y = my;
		}
	}
}