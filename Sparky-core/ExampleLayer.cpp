#include "ExampleLayer.h"
#include "Application.h"

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
}

void ExampleLayer::OnUpdate()
{
	sparky::Application* app_Instance = sparky::Application::s_Instance;
	// SPARKY_INFO("ExampleLayer::Update");
	if (sparky::Input::IsKeyPressed(SP_KEY_TAB))
		SPARKY_TRACE("Tab key is pressed (poll)!");
		app_Instance->camera->updateCamera();
	if (sparky::Input::IsKeyPressed(SP_KEY_W) || sparky::Input::IsKeyPressed(SP_KEY_A) || sparky::Input::IsKeyPressed(SP_KEY_S) || sparky::Input::IsKeyPressed(SP_KEY_D)) {
	}
}

void ExampleLayer::OnEvent(sparky::Event& event)
{
	// SPARKY_TRACE("{0}", event);
	sparky::Application* app_Instance = sparky::Application::s_Instance;

	if (event.GetEventType() == sparky::EventType::KeyPressed)
	{
		sparky::KeyPressedEvent& e = (sparky::KeyPressedEvent&)event;
		int keycode = e.GetKeyCode();
		switch (keycode)
		{
		case SP_KEY_TAB:
		{
			SPARKY_TRACE("Tab key is pressed (event)!");
		}
		break;
		case SP_KEY_N:
		{
			SPARKY_TRACE("'N' key is pressed (event)!");
			SPARKY_INFO("Showing next demo");
			app_Instance->next_demo();
			
		}
		break;
		case SP_KEY_P:
		{
			SPARKY_TRACE("'P' key is pressed (event)!");
			SPARKY_INFO("Showing prev demo");
			app_Instance->prev_demo();
		}
		break;
		case SP_KEY_L:
		{
			SPARKY_TRACE("'L' key is pressed (event)!");
			if (app_Instance->mouseLookAround) {
				glfwSetInputMode(static_cast<GLFWwindow*>(app_Instance->GetWindow().GetNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				app_Instance->camera->lookaroundEnabled = false;
				SPARKY_INFO("Look around disabled");
			}
			else {
				glfwSetInputMode(static_cast<GLFWwindow*>(app_Instance->GetWindow().GetNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				app_Instance->camera->lookaroundEnabled = true;
				SPARKY_INFO("Look around enabled");
			}
			app_Instance->mouseLookAround = !app_Instance->mouseLookAround;
		}
		break;
		default:
			break;
		}
		// SPARKY_TRACE("{0}", (char)e.GetKeyCode());
	}
	if (event.GetEventType() == sparky::EventType::MouseMoved) {
		if (app_Instance->mouseLookAround) {
			// SPARKY_TRACE("Move mouse (event)");
			sparky::MouseMovedEvent& e = (sparky::MouseMovedEvent&)event;
			float x = e.GetX();
			float y = e.GetY();
			float yawdiff = x - app_Instance->camera->lastX;
			float pitdiff = app_Instance->camera->lastY - y; // reverse due to coordinates
			if (yawdiff > -40.0f && yawdiff < 40.0f && pitdiff > -40.0f && pitdiff < 40.0f) {
				app_Instance->camera->updateYawPitch(yawdiff, pitdiff);
			}
			app_Instance->camera->lastX = x;
			app_Instance->camera->lastY = y;
		}
	}
}