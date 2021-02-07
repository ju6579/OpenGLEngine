#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 
#include <iostream>

#include "WindowHandler.h"

#pragma region Local Function
static void GLErrorCallback(int errorCode, const char* errorDescription)
{
	fprintf(stderr, "Error Code (%d): %s", errorCode, errorDescription);
}
#pragma endregion

int main()
{
	glfwSetErrorCallback(GLErrorCallback);

	WindowHandler* glWindow = new WindowHandler("Test");

	glWindow->Init();
	glWindow->Start();

	return 0;
}