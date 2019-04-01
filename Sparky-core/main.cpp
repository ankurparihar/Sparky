#include "window.h"
#include "maths.h"

int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky", 800, 600);

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vec3 vector1(1.0f, 2.0f, 3.0f);
	// vec3 vector2(0.4f, 2.1f, 3.6f);
	// vec3 vector3 = vector2 + vector1;
	// vector2 += 5;
	// std::cout << (vector3 / 2) << std::endl << (vector2 != vec3(5.4f, 7.1f, 8.5f))<< std::endl;

	// double mx, my;
	while (!window.closed()) {
		window.clear();
		// std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;
		// std::cout << window.isKeyPressed(GLFW_KEY_A) << std::endl;
		// std::cout << window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) << std::endl;
		//if (window.isKeyPressed(GLFW_KEY_A)) {
		//	window.getMousePosition(mx, my);
		//	std::cout << mx << ", " << my << std::endl;
		//}
#if 1
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif
		window.update();
	}
	return 0;
}