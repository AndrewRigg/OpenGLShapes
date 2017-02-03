#pragma once

#include <GLM/glm.hpp>

class Ball {
public:
	Ball();
	~Ball();

	float mass;
	float radius;
	float mu = 0.01;	
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 Momentum(glm::vec3 velocity, float mass);
	float KineticEnergy(glm::vec3 velocity, float mass);//Coefficient of static friction
	float Friction(float mass, float g, float mu);		//Frictional force on the ball as it hits surface
	void setMass(float mass);
	float getMass();

private:


};
