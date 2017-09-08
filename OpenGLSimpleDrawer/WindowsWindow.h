#pragma once
#include "Export.h"
#include "Window.h"
#include "glew.h"
#include "glfw3.h"



namespace WindowsWindow
{
	API extern GLFWwindow* window;
	API int Init(GLuint width, GLuint height);	
	API void StartRendering();
};
API void window_size_callback(GLFWwindow* window, int width, int height);
API void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
API void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);