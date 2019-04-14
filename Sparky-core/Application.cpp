#include "Application.h"
#include "Input.h"

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include "glm/gtc/matrix_transform.hpp"

#include "ExampleLayer.h"
#include "ImGuiLayer.h"

// #include "Events/ApplicationEvent.h"

namespace sparky {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SPARKY_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Sparky_Window>(Sparky_Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Application::update() {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << error << std::endl;
		}

		glfwPollEvents();
		// glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		// glViewport(0, 0, m_Width, m_Height);
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()));
	}

	void Application::Run()
	{
		using namespace graphics;
		using namespace maths;

		int DemoIndex = 3;
		int InterDemoIndex = DemoIndex;
		bool WireFrameMode = true;

		while (m_Running)
		{
			// wireframe mode
			if (WireFrameMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			switch (DemoIndex)
			{
			case 1:
			{
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Hello window");

				while (m_Running && DemoIndex == InterDemoIndex) {

					glClearColor(1, 0, 1, 1);
					glClear(GL_COLOR_BUFFER_BIT);

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
			}
			break;
			case 2:
			{
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Hello Triangle");

				float vertices[] = {
					-0.5f, -0.5f, 0.0f,
					 0.5f, -0.5f, 0.0f,
					 0.0f,  0.5f, 0.0f
				};

				unsigned int vbo, vao;
				glGenVertexArrays(1, &vao);
				glGenBuffers(1, &vbo);
				// Bind vertex array object first
				glBindVertexArray(vao);
				// then bind the set of vertex buffers
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				// speicify buffer data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				// then set the vertex attributes pointers
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// unbind array and buffers
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				// 2. use our shader program when we want to render an object
				Shader shader("shaders/hello-triangle.vert", "shaders/hello-triangle.frag");
				shader.enable();

				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();

					glBindVertexArray(vao);
					glDrawArrays(GL_TRIANGLES, 0, 3);

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}

				glDeleteVertexArrays(1, &vao);
				glDeleteBuffers(1, &vbo);

				shader.disable();
			}
			break;
			case 3:
			{
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Hello Rectangle");

				GLfloat vertices[] = {
					-0.5f, -0.5f, 0.0f, // bottom-left
					 0.5f, -0.5f, 0.0f, // bottom-right
					 0.5f,  0.5f, 0.0f, // top-right
					-0.5f,  0.5f, 0.0f  // top-left

				};
				GLushort indeces[] = {
					0, 1, 2,
					2, 3, 0
				};

				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 4 * 3, 3), 0);
				IndexBuffer ibo(indeces, 6);
				Shader shader("shaders/hello-triangle.vert", "shaders/hello-triangle.frag");
				shader.enable();

				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();
					
					vao.bind();
					ibo.bind();
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
					vao.unbind();
					ibo.unbind();

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
				
				shader.disable();
			}
			break;
			case 4:
			{
				InterDemoIndex = DemoIndex;

				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Simple 2D light effect");
				// Window window("Sparky", 1280, 720);

				GLfloat vertices[] = {
					0, 0, 0,
					0, 3, 0,
					8, 3, 0,
					8, 0, 0
				};

				GLushort indeces[] = {
					0, 1, 2,
					2, 3, 0
				};

				GLfloat colors[][16] = {
					{
						// Red
						0.8f, 0.2f, 0.3f, 1.0f,
						0.8f, 0.2f, 0.3f, 1.0f,
						0.8f, 0.2f, 0.3f, 1.0f,
						0.8f, 0.2f, 0.3f, 1.0f,
					},
					{
						// Green
						0.3f, 0.8f, 0.2f, 1.0f,
						0.3f, 0.8f, 0.2f, 1.0f,
						0.3f, 0.8f, 0.2f, 1.0f,
						0.3f, 0.8f, 0.2f, 1.0f,
					},
					{
						// Blue
						0.2f, 0.3f, 0.8f, 1.0f,
						0.2f, 0.3f, 0.8f, 1.0f,
						0.2f, 0.3f, 0.8f, 1.0f,
						0.2f, 0.3f, 0.8f, 1.0f
					}
				};

				// VertexArray vao;
				VertexArray sprite1, sprite2, sprite3;
				Buffer *vbo = new Buffer(vertices, 4 * 3, 3);
				IndexBuffer ibo(indeces, 6);

				// vao.AddBuffers(vbo, 0);
				sprite1.AddBuffers(new Buffer(vertices, 4 * 3, 3), 0);
				sprite1.AddBuffers(new Buffer(colors[0], 4 * 4, 4), 1);
				sprite2.AddBuffers(new Buffer(vertices, 4 * 3, 3), 0);
				sprite2.AddBuffers(new Buffer(colors[1], 4 * 4, 4), 1);
				sprite3.AddBuffers(new Buffer(vertices, 4 * 3, 3), 0);
				sprite3.AddBuffers(new Buffer(colors[2], 4 * 4, 4), 1);
				
				// mat4 ortho = mat4::Transpose(mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
				glm::mat4 proj = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
				Shader shader("shaders/basic.vert", "shaders/basic.frag");
				shader.enable();

				shader.setUniformMat4("pr_matrix", proj);
				// shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
				shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
				shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
				auto window = static_cast<GLFWwindow*>(s_Instance->Get().GetWindow().GetNativeWindow());
				
				double x, y;

				while (m_Running && DemoIndex==InterDemoIndex) {
					
					clear();
					
					glfwGetCursorPos(window, &x, &y);

					shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

					sprite1.bind();
					ibo.bind();
					shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
					ibo.unbind();
					sprite1.unbind();

					sprite2.bind();
					ibo.bind();
					shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
					ibo.unbind();
					sprite2.unbind();

					sprite3.bind();
					ibo.bind();
					shader.setUniformMat4("ml_matrix", mat4::translation(vec3(8, 6, 0)));
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
					ibo.unbind();
					sprite3.unbind();

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
				shader.disable();
			}
			break;
			default:
				m_Running = false;
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}