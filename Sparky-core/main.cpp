#include "Application.h"
#include "Shader.h"
#include "ExampleLayer.h"
#include "ImGuiLayer.h"

int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Log::Init();
	SPARKY_CORE_WARN("Initialized logging.");
	SPARKY_INFO("Hello {0}", "Sparky!");

	auto app = sparky::CreateApplication();
	app->PushLayer(new ExampleLayer());
	app->PushLayer(new ImGuiLayer());
	app->Run();
	delete app;

	return 0;
}