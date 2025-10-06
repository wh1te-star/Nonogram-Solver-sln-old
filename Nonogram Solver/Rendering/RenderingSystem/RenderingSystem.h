#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

class RenderingSystem {
private:
	GLFWwindow* window;
	ImGuiIO* io;

	static void glfw_error_callback(int error, const char* description);

public:
	RenderingSystem();
	int initialize();
	void renderingLoop();
	void finalize();
};


#endif
