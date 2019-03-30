#include "window.h"

namespace sparky {
	namespace graphics {

		void windowResize(GLFWwindow* window, int width, int height);

		Window::Window(const char *title, int width, int height) {
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!init()) {
				glfwTerminate();
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
			glfwSetWindowSizeCallback(m_Window, windowResize);

			return true;
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {
			glfwPollEvents();
			// glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			// glViewport(0, 0, m_Width, m_Height);
			glfwSwapBuffers(m_Window);
		}

		void windowResize(GLFWwindow* window, int width, int height){
			glViewport(0, 0, width, height);
		}

	}
}