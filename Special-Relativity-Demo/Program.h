#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include "Maths.h"
#include "Camera.h"
#include "EventHandler.h"
#include "Shader.h"
#include "Projectile.h"



class Program

{
public:
	Program(int w, int h);
	int mainLoop();

	static void framebuffer_size_callback(GLFWwindow* window, int w, int h);
	static void key_callback(GLFWwindow* window, int button, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	Camera camera;
	EventHandler eventHandler;
	GLFWwindow* window;
	int width, height;
	double timestep;
	
};