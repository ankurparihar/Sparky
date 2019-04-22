#include "Application.h"
#include "Input.h"

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

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

		// OpenGL specification
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		SPARKY_INFO("Maximum no of vertex attributes supported: {0}", nrAttributes);
		
		// Default settings
		DemoIndex = 13;
		WireFrameMode = false;
		z_bufffer = true;
		glEnable(GL_DEPTH_TEST);
		// glfwSetInputMode(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetWindowSize(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), &scr_width, &scr_height);

		// Have a camera
		camera = new Camera();
		camera->window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		mouseLookAround = false;
		time = -100.0f;
		mouseClicksL = 0;
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

		while (m_Running)
		{
			int InterDemoIndex;
			
			switch (DemoIndex)
			{
			case 1:
			{
				// =================================== Simple Window ==================================== //
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
				// =================================== Simple Triangle ==================================== //
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
				Shader shader("shaders/Getting-started/hello-triangle.vert", "shaders/Getting-started/hello-triangle.frag");
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
				// =================================== Simple Rectangle ==================================== //
				/*
				* Using 4 vertices we draw a rectangel by drawing traingles two times
				*/
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
				Shader shader("shaders/Getting-started/hello-triangle.vert", "shaders/Getting-started/hello-triangle.frag");
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
				// =================================== Time varying colors ==================================== //
				/*
				* Using uniform variable we can change color
				*/
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Time varying colors");

				GLfloat vertices[] = {
					-0.5f, -0.5f, 0.0f, // bottom-left
					 0.5f, -0.5f, 0.0f, // bottom-right
					 0.0f,  0.5f, 0.0f, // top-right

				};
				GLushort indeces[] = {
					0, 1, 2
				};

				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 3 * 3, 3), 0);
				IndexBuffer ibo(indeces, 3);
				Shader shader("shaders/Getting-started/hello-triangle.vert", "shaders/Getting-started/time_triangle.frag");
				shader.enable();
				float ourColor;
				vao.bind();
				ibo.bind();
				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();

					ourColor = (float)abs(sin(2.0f * glfwGetTime()));
					shader.setUniform4f("ourColor", vec4(0.0f, ourColor, 0.0f, 1.0f));

					// vao.bind();
					// ibo.bind();
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
					// vao.unbind();
					// ibo.unbind();

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
				vao.unbind();
				ibo.unbind();

				shader.disable();
			}
			break;
			case 5:
			{
				// =================================== Space varying colors =================================== //
				/*
				* Using uniform variable we can change color
				*/
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Spatial colors");
				
				GLfloat vertices[] = {
					// positions
					 0.5f, -0.5f, 0.0f,  // bottom right
					-0.5f, -0.5f, 0.0f,  // bottom left
					 0.0f,  0.5f, 0.0f,  // top 
				};
				GLfloat colors[] = {
					// colors
					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f
				};
				GLushort indices[] = { 0, 1, 2 };
				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 3 * 3, 3), 0);
				vao.AddBuffers(new Buffer(colors, 3 * 3, 3), 1);
				IndexBuffer ibo(indices, 3);
				Shader shader("shaders/Getting-started/space_color.vert", "shaders/Getting-started/space_color.frag");
				shader.enable();
				vao.bind();
				ibo.bind();
				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();
					glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
				vao.unbind();
				ibo.unbind();
			}
			break;
			case 6:
			{
				// =================================== Textures: Solo ==================================== //
				/*
				* Load and sample textures from image
				*/
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Texture sampling: Solo textures");

				GLfloat vertices[] = {
					 // positions
					 0.5f,  0.5f, 0.0f,    // top right
					 0.5f, -0.5f, 0.0f,    // bottom right
					-0.5f, -0.5f, 0.0f,    // bottom left
					-0.5f,  0.5f, 0.0f,    // top left
				};
				GLfloat colors[] = {
					// colors        
					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 0.0f,
				};
				GLfloat texcoords[] = {
					// texture coordinates
					1.0f, 1.0f,
					1.0f, 0.0f,
					0.0f, 0.0f,
					0.0f, 1.0f
				};
				GLushort indices[] = {
					0, 1, 3,
					1, 2, 3
				};
				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 4 * 3, 3), 0);
				vao.AddBuffers(new Buffer(colors, 4 * 3, 3), 1);
				vao.AddBuffers(new Buffer(texcoords, 4 * 2, 2), 2);
				
				IndexBuffer ibo(indices, 6);
				Shader shader("shaders/Getting-started/simple_texture.vert", "shaders/Getting-started/simple_texture.frag");
				Texture texture("res/Textures/wall.jpg");
				shader.enable();
				vao.bind();
				ibo.bind();
				texture.bind();
				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
				texture.unbind();
				vao.unbind();
				ibo.unbind();
				shader.disable();
			}
			break;
			case 7:
			{
				// =================================== Textures: Mixed ==================================== //
				/*
				* Load and sample multiple textures from image with colors
				*/
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Texture sampling: Mixed textures");

				GLfloat vertices[] = {
					// positions
					 0.5f,  0.5f, 0.0f,    // top right
					 0.5f, -0.5f, 0.0f,    // bottom right
					-0.5f, -0.5f, 0.0f,    // bottom left
					-0.5f,  0.5f, 0.0f,    // top left
				};
				GLfloat colors[] = {
					// colors        
					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 0.0f,
				};
				GLfloat texcoords[] = {
					// texture coordinates
					2.0f, 2.0f,
					2.0f, 0.0f,
					0.0f, 0.0f,
					0.0f, 2.0f
				};
				GLushort indices[] = {
					0, 1, 3,
					1, 2, 3
				};
				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 4 * 3, 3), 0);
				vao.AddBuffers(new Buffer(colors, 4 * 3, 3), 1);
				vao.AddBuffers(new Buffer(texcoords, 4 * 2, 2), 2);

				IndexBuffer ibo(indices, 6);
				Shader shader("shaders/Getting-started/Mixed_tex.vert", "shaders/Getting-started/Mixed_tex.frag");
				Texture texture2("res/Textures/wall.jpg");
				Texture texture1("res/Textures/awesomeface.png");
				shader.enable();
				vao.bind();
				ibo.bind();
				shader.setUniform1i("texture1", 0);
				shader.setUniform1i("texture2", 1);
				texture1.bind(0);
				texture2.bind(1);
				glfwSetWindowSize(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), 720, 720);
				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
				texture2.unbind();
				texture1.unbind();
				vao.unbind();
				ibo.unbind();
				shader.disable();
				glfwSetWindowSize(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), scr_width, scr_height);
			}
			break;
			case 8:
			{
				// =================================== Transformation ==================================== //
				/*
				* Use glm library to create and apply vectors and matrices
				*/
				InterDemoIndex = DemoIndex;
				case_8_order = true;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Transforms");

				GLfloat vertices[] = {
					// positions
					 0.5f,  0.5f, 0.0f,    // top right
					 0.5f, -0.5f, 0.0f,    // bottom right
					-0.5f, -0.5f, 0.0f,    // bottom left
					-0.5f,  0.5f, 0.0f,    // top left
				};
				GLfloat colors[] = {
					// colors        
					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 0.0f,
				};
				GLfloat texcoords[] = {
					// texture coordinates
					2.0f, 2.0f,
					2.0f, 0.0f,
					0.0f, 0.0f,
					0.0f, 2.0f
				};
				GLushort indices[] = {
					0, 1, 3,
					1, 2, 3
				};

				glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
				// glm::mat4 trans = glm::mat4(1.0f);
				// trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
				// trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				// trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
				
				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 4 * 3, 3), 0);
				vao.AddBuffers(new Buffer(colors, 4 * 3, 3), 1);
				vao.AddBuffers(new Buffer(texcoords, 4 * 2, 2), 2);

				IndexBuffer ibo(indices, 6);
				Shader shader("shaders/Getting-started/transform.vert", "shaders/Getting-started/transform.frag");
				Texture texture1("res/Textures/awesomeface.png");
				Texture texture2("res/Textures/wall.jpg");
				shader.enable();
				vao.bind();
				ibo.bind();
				shader.setUniform1i("texture1", 0);
				shader.setUniform1i("texture2", 1);
				texture1.bind(0);
				texture2.bind(1);
				glfwSetWindowSize(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), 720, 720);
				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();

					glm::mat4 trans = glm::mat4(1.0f);
					if (case_8_order) {
						trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
						trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
					}
					else {
						trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
						trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
					}
					shader.setUniformMat4("transform", trans);

					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}
				texture2.unbind();
				texture1.unbind();
				vao.unbind();
				ibo.unbind();
				shader.disable();
				glfwSetWindowSize(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), scr_width, scr_height);
			}
			break;
			case 9:
			{
				// =================================== Going 3D ==================================== //
				/*
				* Using model view projection for 3D projections
				*/
				InterDemoIndex = DemoIndex;
				case_9_multi = false;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Going 3D");

				// GLfloat vertices[] = {
				// 	// positions
				// 	 0.5f,  0.5f, 0.0f,    // top right
				// 	 0.5f, -0.5f, 0.0f,    // bottom right
				// 	-0.5f, -0.5f, 0.0f,    // bottom left
				// 	-0.5f,  0.5f, 0.0f,    // top left
				// };
				GLfloat vertices[] = {

					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,

					-0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f,

					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,

					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,

					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f, -0.5f,

					-0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f
				};
				GLfloat texcoords[] = {
					// texture coordinates
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,

					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,

					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,
					1.0f, 0.0f,

					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,
					1.0f, 0.0f,

					0.0f, 1.0f,
					1.0f, 1.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					0.0f, 0.0f,
					0.0f, 1.0f,

					0.0f, 1.0f,
					1.0f, 1.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					0.0f, 0.0f,
					0.0f, 1.0f
				};
				GLushort indices[] = {
					 0,  1,  2,
					 3,  4,  5,
					 6,  7,  8,
					 9, 10, 11,
					12, 13, 14,
					15, 16, 17,
					18, 19, 20,
					21, 22, 23,
					24, 25, 26,
					27, 28, 29,
					30, 31, 32,
					33, 34, 35
				};

				glm::vec3 cubePositions[] = {
					glm::vec3(0.0f,  0.0f,  0.0f),
					glm::vec3(2.0f,  5.0f, -15.0f),
					glm::vec3(-1.5f, -2.2f, -2.5f),
					glm::vec3(-3.8f, -2.0f, -12.3f),
					glm::vec3(2.4f, -0.4f, -3.5f),
					glm::vec3(-1.7f,  3.0f, -7.5f),
					glm::vec3(1.3f, -2.0f, -2.5f),
					glm::vec3(1.5f,  2.0f, -2.5f),
					glm::vec3(1.5f,  0.2f, -1.5f),
					glm::vec3(-1.3f,  1.0f, -1.5f)
				};

				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 36 * 3, 3), 0);
				vao.AddBuffers(new Buffer(texcoords, 36 * 2, 2), 1);

				IndexBuffer ibo(indices, 36);

				Shader shader("shaders/Getting-started/Going-3D.vert", "shaders/Getting-started/Going-3D.frag");
				Texture texture1("res/Textures/awesomeface.png");
				Texture texture2("res/Textures/wall.jpg");

				shader.enable();
				vao.bind();
				ibo.bind();
				shader.setUniform1i("texture1", 0);
				shader.setUniform1i("texture2", 1);
				texture1.bind(0);
				texture2.bind(1);

				// glm::mat4 model = glm::mat4(1.0f);
				// model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

				glm::mat4 view = glm::mat4(1.0f);
				view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

				glm::mat4 proj = glm::mat4(1.0f);
				proj = glm::perspective(glm::radians(45.0f), (float)scr_width / (float)scr_height, 0.1f, 100.0f);

				shader.setUniformMat4("view", view);
				shader.setUniformMat4("proj", proj);

				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();

					if (case_9_multi) {
						for (unsigned int i = 0; i < 10; ++i) {
							glm::mat4 model = glm::mat4(1.0f);
							model = glm::translate(model, cubePositions[i]);
							float angle = 2.0f * (i + 1);
							// float angle = (i % 3 == 0) ? (2.0f * (i + 1)) : 45.0f;
							model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), cubePositions[i]);
							shader.setUniformMat4("model", model);
							glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
						}
					}
					else {
						glm::mat4 model = glm::mat4(1.0f);
						model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.5f, 1.0f, 0.0f));
						shader.setUniformMat4("model", model);
						glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
					}


					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}

				texture2.unbind();
				texture1.unbind();
				ibo.unbind();
				vao.unbind();
				shader.disable();
			}
			break;
			case 10:
			{
				// =================================== Camera and Movement ==================================== //
				/*
				* Using model view projection for 3D projections
				*/
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Camera and Movement");

				GLfloat vertices[] = {

					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,

					-0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f,

					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,

					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,

					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f, -0.5f,

					-0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f
				};
				GLfloat texcoords[] = {
					// texture coordinates
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,

					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,

					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,
					1.0f, 0.0f,

					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 1.0f,
					0.0f, 0.0f,
					1.0f, 0.0f,

					0.0f, 1.0f,
					1.0f, 1.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					0.0f, 0.0f,
					0.0f, 1.0f,

					0.0f, 1.0f,
					1.0f, 1.0f,
					1.0f, 0.0f,
					1.0f, 0.0f,
					0.0f, 0.0f,
					0.0f, 1.0f
				};
				GLushort indices[] = {
					 0,  1,  2,
					 3,  4,  5,
					 6,  7,  8,
					 9, 10, 11,
					12, 13, 14,
					15, 16, 17,
					18, 19, 20,
					21, 22, 23,
					24, 25, 26,
					27, 28, 29,
					30, 31, 32,
					33, 34, 35
				};

				glm::vec3 cubePositions[] = {
					glm::vec3( 0.0f,  0.0f,  0.0f),
					glm::vec3( 2.0f,  5.0f, -15.0f),
					glm::vec3(-1.5f, -2.2f, -2.5f),
					glm::vec3(-3.8f, -2.0f, -12.3f),
					glm::vec3( 2.4f, -0.4f, -3.5f),
					glm::vec3(-1.7f,  3.0f, -7.5f),
					glm::vec3( 1.3f, -2.0f, -2.5f),
					glm::vec3( 1.5f,  2.0f, -2.5f),
					glm::vec3( 1.5f,  0.2f, -1.5f),
					glm::vec3(-1.3f,  1.0f, -1.5f)
				};

				VertexArray vao;
				vao.AddBuffers(new Buffer(vertices, 36 * 3, 3), 0);
				vao.AddBuffers(new Buffer(texcoords, 36 * 2, 2), 1);

				IndexBuffer ibo(indices, 36);

				Shader shader("shaders/Getting-started/Going-3D.vert", "shaders/Getting-started/Going-3D.frag");
				Texture texture1("res/Textures/awesomeface.png");
				Texture texture2("res/Textures/wall.jpg");

				shader.enable();
				vao.bind();
				ibo.bind();
				shader.setUniform1i("texture1", 0);
				shader.setUniform1i("texture2", 1);
				texture1.bind(0);
				texture2.bind(1);

				// glm::mat4 model = glm::mat4(1.0f);
				// model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

				// glm::mat4 view = glm::mat4(1.0f);
				// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

				glm::mat4 proj = glm::mat4(1.0f);
				proj = glm::perspective(glm::radians(45.0f), (float)scr_width / (float)scr_height, 0.1f, 100.0f);

				shader.setUniformMat4("proj", proj);

				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();
					
					// Just one line lol !!!
					shader.setUniformMat4("view", camera->view);

					for (unsigned int i = 0; i < 10; ++i) {
						glm::mat4 model = glm::mat4(1.0f);
						model = glm::translate(model, cubePositions[i]);
						float angle = 20.0f * i;
						// float angle = (i % 3 == 0) ? (2.0f * (i + 1)) : 45.0f;
						model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
						shader.setUniformMat4("model", model);
						glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
					}

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}

				texture2.unbind();
				texture1.unbind();
				ibo.unbind();
				vao.unbind();
				shader.disable();
			}
			break;
			case 11:
			{
				// =================================== 2D ligth effect ==================================== //
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
				Shader shader("shaders/Lighting/basic.vert", "shaders/Lighting/basic.frag");
				shader.enable();

				shader.setUniformMat4("pr_matrix", proj);
				// shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
				shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
				shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
				auto window = static_cast<GLFWwindow*>(s_Instance->Get().GetWindow().GetNativeWindow());

				double x, y;

				while (m_Running && DemoIndex == InterDemoIndex) {

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
			case 12:
			{
				// =================================== Colors ==================================== //
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Colors");

				// case_11_r = case_11_g = case_11_b = case_11_a = 1.0f;
				color_r = color_g = color_b = color_a = 1.0f;
				glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
				glm::vec4 lightColor = glm::vec4(color_r, color_g, color_b, color_a);
				glm::vec4 objectColor = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);

				GLfloat vertices[] = {
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f, -0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f, -0.5f,
				};
				
				GLushort indices[] = {
					0, 1, 2,
					1, 2, 3,
					4, 5, 6,
					5, 6, 7,
					0, 1, 5,
					0, 4, 5,
					2, 3, 7,
					2, 6, 7,
					2, 0, 4,
					2, 6, 4,
					1, 3, 7,
					1, 5, 7
				};

				VertexArray cubeVAO;
				IndexBuffer ibo(indices, 36);
				cubeVAO.AddBuffers(new Buffer(vertices, 8 * 3, 3), 0);

				Shader shaderColor("shaders/Lighting/1.Colors.vert", "shaders/Lighting/1.Colors.frag");
				Shader shaderLight("shaders/Lighting/1.Light.vert", "shaders/Lighting/1.Light.frag");
				
				glm::mat4 proj = glm::mat4(1.0f);
				proj = glm::perspective(glm::radians(45.0f), (float)scr_width / (float)scr_height, 0.1f, 100.0f);
				glm::mat4 model;
				
				cubeVAO.bind();
				ibo.bind();

				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();

					model = glm::mat4(1.0f);
					lightColor = glm::vec4(color_r, color_g, color_b, color_a);

					shaderColor.enable();
					shaderColor.setUniform4f("lightColor", lightColor);
					shaderColor.setUniform4f("objectColor", objectColor);
					shaderColor.setUniformMat4("model", model);
					shaderColor.setUniformMat4("view", camera->view);
					shaderColor.setUniformMat4("proj", proj);
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

					model = glm::mat4(1.0f);
					model = glm::translate(model, lightPos);
					model = glm::scale(model, glm::vec3(0.2f));
					
					shaderLight.enable();
					shaderLight.setUniform4f("lightColor", lightColor);
					shaderLight.setUniformMat4("model", model);
					shaderLight.setUniformMat4("view", camera->view);
					shaderLight.setUniformMat4("proj", proj);
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
					// shaderLight.disable();

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}

				ibo.unbind();
				cubeVAO.unbind();
				shaderLight.disable();
			}
			break;
			case 13:
			{
				// =================================== Basic 3D Lighting ==================================== //
				InterDemoIndex = DemoIndex;
				glfwSetWindowTitle(static_cast<GLFWwindow*>(m_Window->GetNativeWindow()), "Basic 3D Lighting - Ambient, Diffuse and Specular");

				color_r = color_g = color_b = color_a = 1.0f;
				glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);
				glm::vec4 lightColor = glm::vec4(color_r, color_g, color_b, color_a);
				glm::vec4 objectColor = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);

				GLfloat vertices[] = {
					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,

					-0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f,

					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,

					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,

					-0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f, -0.5f,
					 0.5f, -0.5f,  0.5f,
					 0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f,  0.5f,
					-0.5f, -0.5f, -0.5f,

					-0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f, -0.5f,
					 0.5f,  0.5f,  0.5f,
					 0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f,  0.5f,
					-0.5f,  0.5f, -0.5f
				};

				GLfloat normals[] = {
					 0.0f,  0.0f, -1.0f,
					 0.0f,  0.0f, -1.0f,
					 0.0f,  0.0f, -1.0f,
					 0.0f,  0.0f, -1.0f,
					 0.0f,  0.0f, -1.0f,
					 0.0f,  0.0f, -1.0f,
					 
					 0.0f,  0.0f, 1.0f,
					 0.0f,  0.0f, 1.0f,
					 0.0f,  0.0f, 1.0f,
					 0.0f,  0.0f, 1.0f,
					 0.0f,  0.0f, 1.0f,
					 0.0f,  0.0f, 1.0f,

					-1.0f,  0.0f,  0.0f,
					-1.0f,  0.0f,  0.0f,
					-1.0f,  0.0f,  0.0f,
					-1.0f,  0.0f,  0.0f,
					-1.0f,  0.0f,  0.0f,
					-1.0f,  0.0f,  0.0f,

					 1.0f,  0.0f,  0.0f,
					 1.0f,  0.0f,  0.0f,
					 1.0f,  0.0f,  0.0f,
					 1.0f,  0.0f,  0.0f,
					 1.0f,  0.0f,  0.0f,
					 1.0f,  0.0f,  0.0f,

					 0.0f, -1.0f,  0.0f,
					 0.0f, -1.0f,  0.0f,
					 0.0f, -1.0f,  0.0f,
					 0.0f, -1.0f,  0.0f,
					 0.0f, -1.0f,  0.0f,
					 0.0f, -1.0f,  0.0f,

					 0.0f,  1.0f,  0.0f,
					 0.0f,  1.0f,  0.0f,
					 0.0f,  1.0f,  0.0f,
					 0.0f,  1.0f,  0.0f,
					 0.0f,  1.0f,  0.0f,
					 0.0f,  1.0f,  0.0f
				};

				GLushort indices[] = {
					 0,  1,  2,
					 3,  4,  5,
					 6,  7,  8,
					 9, 10, 11,
					12, 13, 14,
					15, 16, 17,
					18, 19, 20,
					21, 22, 23,
					24, 25, 26,
					27, 28, 29,
					30, 31, 32,
					33, 34, 35
				};
				
				VertexArray cubeVAO;
				cubeVAO.AddBuffers(new Buffer(vertices, 36 * 3, 3), 0);
				cubeVAO.AddBuffers(new Buffer(normals,  36 * 3, 3), 1);
				IndexBuffer ibo(indices, 36);

				Shader shaderColor("shaders/Lighting/2.Colors.vert", "shaders/Lighting/2.Colors.frag");
				Shader shaderLight("shaders/Lighting/2.Light.vert", "shaders/Lighting/2.Light.frag");

				glm::mat4 proj = glm::mat4(1.0f);
				proj = glm::perspective(glm::radians(45.0f), (float)scr_width / (float)scr_height, 0.1f, 100.0f);
				glm::mat4 model;

				cubeVAO.bind();
				ibo.bind();
				case_13_rotate = true;// false;
				case_13_radius = 0.729f; // 2.0f;
				case_13_phi = 65.0f;// 0.0f;
				case_13_theta = 0.0f;
				float theta;
				case_13_speed = 15.0f;// 10.0f;
				float lastTime, deltaTime;
				lastTime = (float)glfwGetTime();
				float x, y, z;
				while (m_Running && DemoIndex == InterDemoIndex) {
					clear();

					model = glm::mat4(1.0f);
					lightColor = glm::vec4(color_r, color_g, color_b, color_a);

					shaderColor.enable();
					shaderColor.setUniform3f("viewPos", camera->cameraPos);
					shaderColor.setUniform3f("lightPos", lightPos);
					shaderColor.setUniform4f("lightColor", lightColor);
					shaderColor.setUniform4f("objectColor", objectColor);
					shaderColor.setUniformMat4("model", model);
					shaderColor.setUniformMat4("view", camera->view);
					shaderColor.setUniformMat4("proj", proj);
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

					// model = glm::mat4(1.0f);
					
					if (case_13_rotate) {
						deltaTime = (float)glfwGetTime() - lastTime;
						case_13_theta += deltaTime * case_13_speed * 10;
						case_13_theta = (case_13_theta > 180.0f) ? -180.0f : case_13_theta;
						lastTime += deltaTime;
						// flash
						// deltaTime = (float)glfwGetTime() - lastTime;
						// case_13_theta += deltaTime * case_13_speed;
						// case_13_theta = (float)((int)case_13_theta % 360 - 180);
						// std::cout << case_13_theta << std::endl;
						// lastTime += deltaTime;
					}

					theta = (float)(((int)(case_13_theta + 180) % 360) - 180);
					x = glm::cos(glm::radians(case_13_phi)) * glm::sin(glm::radians(theta));
					y = glm::sin(glm::radians(case_13_phi));
					z = glm::cos(glm::radians(case_13_phi)) * glm::cos(glm::radians(theta));
					lightPos = case_13_radius * glm::vec3(x, y, z);
					
					model = glm::translate(model, lightPos);
					model = glm::scale(model, glm::vec3(0.1f));

					shaderLight.enable();
					shaderLight.setUniform4f("lightColor", lightColor);
					shaderLight.setUniformMat4("model", model);
					shaderLight.setUniformMat4("view", camera->view);
					shaderLight.setUniformMat4("proj", proj);
					glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
					// shaderLight.disable();

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate();

					m_Window->OnUpdate();
				}

				ibo.unbind();
				cubeVAO.unbind();
				shaderLight.disable();
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

	void Application::next_demo() {
		glClearColor(0, 0, 0, 1);
		camera->resetCamera();
		DemoIndex++;
	}
	void Application::prev_demo() {
		glClearColor(0, 0, 0, 1);
		camera->resetCamera();
		DemoIndex--;
	}
	void Application::flip_wireframe_mode() {
		// Flip wireframe mode
		WireFrameMode = !WireFrameMode;
		if (WireFrameMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	void Application::flip_z_buffer() {
		// enable/disable z-buffer
		z_bufffer = !z_bufffer;
		if (z_bufffer) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
	}
	void Application::swap_demo(int i)
	{
		glClearColor(0, 0, 0, 1);
		camera->resetCamera();
		DemoIndex = i;
	}

}