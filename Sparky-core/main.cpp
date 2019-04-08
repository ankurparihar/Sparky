#include "window.h"
#include "maths.h"
#include "Shader.h"

int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky", 960, 540);

	// glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

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

	mat4 ortho = mat4::Transpose(mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	while (!window.closed()) {
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}
	return 0;
}