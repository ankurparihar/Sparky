#include "window.h"

int main() {
	using namespace sparky;
	using namespace graphics;

	Window window("Sparky", 800, 600);

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	double mx, my;
	while (!window.closed()) {
		// std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;
		window.clear();
		// std::cout << window.isKeyPressed(GLFW_KEY_A) << std::endl;
		// std::cout << window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) << std::endl;
		if (window.isKeyPressed(GLFW_KEY_A)) {
			window.getMousePosition(mx, my);
			std::cout << mx << ", " << my << std::endl;
		}
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