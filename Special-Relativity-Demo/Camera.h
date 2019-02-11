#pragma once
#include <glm/ext.hpp>
#include <iostream>

class Camera

{
public:

	Camera(double timestep_);
	void cameraTranslate();
	void cameraRotate();
	void cameraSetSpeed(double yoffset);
	void setVel(int coord, double val);
	void setAngVel(double cursx, double cursy);
	void update();

	float speed;
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 vel;
	glm::vec3 angVel;
	glm::vec3 coordVel;

private:


	float rotSpeed;
	double defCursX, defCursY, defScroll, acceleration, timestep;
};