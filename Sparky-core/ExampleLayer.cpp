#include "ExampleLayer.h"

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
		if (e.GetKeyCode() == SP_KEY_TAB)
			SPARKY_TRACE("Tab key is pressed (event)!");
		SPARKY_TRACE("{0}", (char)e.GetKeyCode());
	}
}