// #include "window.h"
#include "Application.h"
#include "maths.h"
#include "Shader.h"

#include "Events/ApplicationEvent.h"

#include "buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "LayerData.h"

#define INACTIVE_BLOCK 0

int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Log::Init();
	SPARKY_CORE_WARN("Initialized logging.");
	SPARKY_INFO("Hello {0}", "Sparky!");

	auto app = sparky::CreateApplication();
	app->PushLayer(new ExampleLayer());
	app->Run();
	delete app;

	Window window("Sparky", 1280, 720);

	// glClearColor(0.2f, 0.3f, 0.8f, 1.0f);


	WindowResizeEvent e(1280, 720);
	if (e.IsInCategory(EventCategoryApplication)) {
		SPARKY_TRACE(e);
	}
	if (e.IsInCategory(EventCategoryInput)) {
		SPARKY_TRACE(e);
	}

#if INACTIVE_BLOCK
	GLfloat vertices[] = {
		// -0.5f, -0.5f, 0.0f,
		// -0.5f,  0.5f, 0.0f,
		//  0.5f,  0.5f, 0.0f,
		//  0.5f,  0.5f, 0.0f,
		//  0.5f, -0.5f, 0.0f,
		// -0.5f, -0.5f, 0.0f
		 0, 0, 0,
		 8, 0, 0,
		 0, 3, 0,
		 0, 3, 0,
		 8, 3, 0,
		 8, 0, 0
		//  4, 3, 0,
		// 12, 3, 0,
		//  4, 6, 0,
		//  4, 6, 0,
		// 12, 3, 0,
		// 12, 6, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
#else
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

	VertexArray vao;
	VertexArray sprite1, sprite2, sprite3;
	Buffer *vbo = new Buffer(vertices, 4 * 3, 3);
	IndexBuffer ibo(indeces, 6);

	// vao.AddBuffers(vbo, 0);
	sprite1.AddBuffers(new Buffer(vertices,  4 * 3, 3), 0);
	sprite1.AddBuffers(new Buffer(colors[0], 4 * 4, 4), 1);
	sprite2.AddBuffers(new Buffer(vertices,  4 * 3, 3), 0);
	sprite2.AddBuffers(new Buffer(colors[1], 4 * 4, 4), 1);
	sprite3.AddBuffers(new Buffer(vertices,  4 * 3, 3), 0);
	sprite3.AddBuffers(new Buffer(colors[2], 4 * 4, 4), 1);

#endif

	// mat4 ortho = mat4::Transpose(mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	glm::mat4 proj = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4("pr_matrix", proj);
	// shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	while (!window.closed()) {
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));
		#if INACTIVE_BLOCK
		glDrawArrays(GL_TRIANGLES, 0, 6);
		#else
		// vao.bind();
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

		// vao.unbind();
		#endif
		window.update();
	}
	return 0;
}