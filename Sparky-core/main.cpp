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

	mat4 matrix1(
		10, 16,  6,  4,
		 0,  3,  6,  6,
		 2,  7,  3, 16,
		15,  7,  5,  8
	);
	mat4 matrix2(
		13,  0,  2, 10,
		 0, 11,  7, 13,
		 2, 15, 13, 17,
		 2, 18, 15,  1
	);
	// matrix1.transpose();
	// std::cout << matrix1 << std::endl;
	// std::cout << tan(toRadian(45)) << std::endl;
	// matrix1 /= 10;
	// std::cout << matrix1 << std::endl;
	// mat4 matrix3 = matrix1 * matrix2;
	// matrix1 *= matrix2;
	// std::cout << matrix2[5] << std::endl;
	// matrix2[5] = 50;
	// matrix2[5] -= 50;
	// std::cout << mat4::mat4(matrix1) << std::endl;
	// std::cout << mat4::indentity() << std::endl;
	// std::cout << mat4::scale(vec3(5, 3, 2)) << std::endl;
	// std::cout << mat4::translation(vec3(2, 3, 4)) << std::endl;
	// std::cout << mat4::rotation(30, vec3(0, 0, 1)) * mat4::indentity() << std::endl;
	// std::cout << (&matrix2[5])[0] << " " << (&matrix2[5])[1] << std::endl;
	// std::cout << (matrix1 == matrix3) << std::endl;
	//mat4 matrix3 = mat4::Transpose(mat4::glMultiply(matrix1, matrix2));
	// mat4 matrix4 = mat4::Transpose(matrix1) * mat4::Transpose(matrix2);
	// std::cout << (matrix3 == matrix4) << std::endl;
	// std::cout << mat4::Transpose(matrix1) * mat4::Transpose(matrix2) << std::endl;
	// mat4 mat_ortho = mat4::orthographic(-1, 1, -1, 1, -1, 1);
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