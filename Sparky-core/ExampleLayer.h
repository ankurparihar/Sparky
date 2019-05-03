#pragma once

#include "Application.h"

class ExampleLayer : public sparky::Layer
{
public:
	ExampleLayer();
	~ExampleLayer() {}

	void OnUpdate();
	void OnEvent(sparky::Event& event);
};