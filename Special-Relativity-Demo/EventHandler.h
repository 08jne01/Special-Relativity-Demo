#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include "Camera.h"

class EventHandler

{
public:

	EventHandler(Camera& cam);
	void keyHandler(int action, int button);
	void mouseHandler(double xpos, double ypos);
	void mouseButtonHandler(int action, int button);
	void scrollHandler(double yoffset);
	void update();

	double arrowUp, arrowRight;

private:
	Camera& camera;
	double speed;
	int arrowPressedUp, arrowPressedRight;
};