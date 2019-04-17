#pragma once

#include "window.h"
// #include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace sparky {

	// Camera class
	class Camera
	{
	public:
		Camera();
		~Camera();
	private:
		float lastFrame;
		float currFrame;
		glm::vec3 front;
	public:
		GLFWwindow* window;
		bool lookaroundEnabled;
		float sense_move;    // camera movement speed
		float sense_look;    // camera rotation speed
		float yaw, pitch;    // 3D orientation of camera
		float lastX, lastY;  // last mouse coordinates
		glm::mat4 view;
		glm::vec3 cameraPos, cameraFront, cameraUp;
		glm::mat4 getView();
		void resetCamera();
		void updateCamera();
		void updateYawPitch(float yaw_i, float pitch_i);
	};
}