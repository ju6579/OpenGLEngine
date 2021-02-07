#include "WindowHandler.h"

#include <iostream>

#pragma region Window Handler Implementation
WindowHandler::WindowHandler(const char* title)
{
	this->_windowTitle = title;
	_currentWindow = NULL;
}

void WindowHandler::Init()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		ReportFatalError("Failed to Initialize Open GL, Please Check Environment.");
	}

	// Setup GL Properties for Window
#ifdef _WIN32 || _WIN64
	SetGLFWWindowProperties();
#endif

	// Create Window for Rendering
	this->_currentWindow = glfwCreateWindow(1024, 768, _windowTitle, NULL, NULL);
	if (_currentWindow == NULL) {
		ReportFatalError("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");
	}
	glfwMakeContextCurrent(_currentWindow);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) 
	{
		ReportFatalError("Failed to initialize GLEW\n");
	}
	glfwSetInputMode(_currentWindow, GLFW_STICKY_KEYS, GL_TRUE);
}
void WindowHandler::Start()
{
	RunLoadCallbacks();

	do {
		RunUpdateCallbacks();
	}
	while (glfwGetKey(_currentWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(_currentWindow) == 0);

	RunEndCallbacks();
}
#pragma endregion


#pragma region Local Function
void WindowHandler::SetGLFWWindowProperties()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void WindowHandler::ReportFatalError(const char* errorMessage)
{
	fprintf(stderr, errorMessage);
	glfwTerminate();
	exit(-1);
}

#pragma region Lifecycle Handle Method
void WindowHandler::RunLoadCallbacks()
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}
void WindowHandler::RunUpdateCallbacks()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(_currentWindow);
	glfwPollEvents();
}
void WindowHandler::RunEndCallbacks()
{
	glfwTerminate();
}
#pragma endregion

#pragma endregion