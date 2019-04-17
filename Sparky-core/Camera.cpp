#include "Camera.h"

namespace sparky {

	// Camera class
	Camera::Camera() {
		resetCamera();
	}
	Camera::~Camera() {
	}
	glm::mat4 Camera::getView() {
		return view;
	}
	void Camera::resetCamera() {
		sense_move = 2.5f;
		sense_look = 0.2f;
		lastX = lastY = 0.0f;
		yaw = pitch = 0.0f;
		lastFrame = (float)glfwGetTime();
		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		lookaroundEnabled = false;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
	void Camera::updateCamera() {

		currFrame = (float)glfwGetTime();
		float deltaTime = currFrame - lastFrame;
		lastFrame = currFrame;
		if (deltaTime > 0.03f) {
			currFrame = (float)glfwGetTime();
			deltaTime = currFrame - lastFrame;
			lastFrame = currFrame;
		}
		// std::cout << deltaTime << std::endl;

		float cameraSpeed = sense_move * deltaTime; // adjust accordingly

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
	
	void Camera::updateYawPitch(float yawDiff, float pitchDiff) {
		yaw += yawDiff * sense_look;
		// yaw = (yaw > 75.0f) ? 75.0f : yaw;
		// yaw = (yaw < -75.0f) ? -75.0f : yaw;
		pitch += pitchDiff * sense_look;
		pitch = (pitch > 75.0f) ? 75.0f : pitch;
		pitch = (pitch < -75.0f) ? -75.0f : pitch;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw - 90.0f));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw - 90.0f));
		cameraFront = glm::normalize(front);
	}
}