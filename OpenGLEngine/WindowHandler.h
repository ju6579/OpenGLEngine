#pragma once

#include <glew.h>
#include <glfw3.h>

class WindowHandler {
public:
	WindowHandler(const char* title);
	void Init();
	void Start();

private:
	void SetGLFWWindowProperties();
	void ReportFatalError(const char* errorMessage);

	void RunLoadCallbacks();
	void RunUpdateCallbacks();
	void RunEndCallbacks();

	GLFWwindow* _currentWindow;
	const char* _windowTitle;
};