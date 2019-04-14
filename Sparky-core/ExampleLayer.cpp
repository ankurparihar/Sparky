#include "ExampleLayer.h"
#include "Application.h"

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
}

void ExampleLayer::OnUpdate()
{
	// SPARKY_INFO("ExampleLayer::Update");
	if (sparky::Input::IsKeyPressed(SP_KEY_TAB))
		SPARKY_TRACE("Tab key is pressed (poll)!");
}

void ExampleLayer::OnEvent(sparky::Event& event)
{
	// SPARKY_TRACE("{0}", event);
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
			// sparky::Application::s_Instance->next_demo();
			
		}
		break;
		case SP_KEY_P:
		{
			SPARKY_TRACE("'P' key is pressed (event)!");
			SPARKY_INFO("Showing prev demo");
			// sparky::Application::s_Instance->prev_demo();
		}
		break;
		default:
			break;
		}			
		// SPARKY_TRACE("{0}", (char)e.GetKeyCode());
	}
}