#pragma once
#include <glm/ext.hpp>
#include <iostream>

class Projectile
{
	public:
		Projectile(double timestep);
		glm::vec3 getPosition();
		glm::vec3 getDirection();
		glm::vec3 getVelocity();
		void update();
		
	private:
		glm::vec3 position, direction, velocity, acceleration, gravity, forceDrag(), accleration;
		double mass;
		float timeStp;
};