#include "ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
}

void ExampleLayer::OnUpdate()
{
	SPARKY_INFO("ExampleLayer::Update");
}

void ExampleLayer::OnEvent(sparky::Event& event)
{
	SPARKY_TRACE("{0}", event);
}