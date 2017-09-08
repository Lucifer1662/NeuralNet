#include "Window.h"
#include "Platform.h"
#include "Engine.h"

API const char* Window::applicationDirectory;
unsigned int Window::width;
unsigned int Window::height;
Event<void, int, int> Window::windowChangedEvent;

void Window::Setup() {
	//glFrontFace(GL_CW);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	Engine::Setup();
}

void Window::Render() {
//	static GLfloat t = 0;
//	t += 0.01f;
//	if (t > 1)
//		t = 0;
//	glClearColor(t, 0, 0, 1);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	Engine::Render();	
}

void Window::Terminate() {
	Engine::Terminate();
}





