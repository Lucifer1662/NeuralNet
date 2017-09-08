#include "glew.h"
#include "glfw3.h"
#include "WindowsWindow.h"
#include "Input.h"
#include "EngineTime.h"


API GLFWwindow* WindowsWindow::window;

int WindowsWindow::Init(GLuint width, GLuint height)
{
	if (!glfwInit())
	{
		//fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	Window::width = width;
	Window::height = height;
	window = glfwCreateWindow(width, height, "Lukes Game", NULL, NULL);
	glViewport(0, 0, width, height);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		//fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	} 
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	
	//---------Audio--------------
	/*ALCdevice* alcDevice = alcOpenDevice(NULL);
	if(alcDevice){
		ALCcontext* alcContext = alcCreateContext(alcDevice, NULL);
		if (!alcContext)
			std::cout << "Sound context Fail" << std::endl;
		else
			alcMakeContextCurrent(alcContext);
	}
	else
		std::cout << "No sound Device" << std::endl;
		*/
	
	glfwSetWindowSizeCallback(window, window_size_callback);

	Window::Setup();
	return 0;
}

void WindowsWindow::StartRendering() {
	do {
		EngineTime::Start();
		glfwSwapBuffers(window);
		glfwPollEvents();
		Window::Render();
		EngineTime::Finish();

		//	elapsed = Time::deltaTime;
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}


void window_size_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	glViewport(0, 0, width, height);
	Window::windowChangedEvent.Call(width,height);

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		Input::keyDown[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		Input::keyDown[key] = false;
	}
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double xold = xpos;
	static double yold = ypos;

	Input::mousePosition.x = xpos;
	Input::mousePosition.y = ypos;

	Input::mouseMovement.x = xpos - xold;
	Input::mouseMovement.y = ypos - yold;

	xold = xpos;
	yold = ypos;
}



