#pragma once

#include <GLM/glm.hpp>

class Ball {
public:
	Ball();
	~Ball();


	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	int ballRadius = 1.0;
	float h = 2.0f;						//Initial height of ball
	float g = -9.81;
	float x = 1.0f;						//Initial horizontal position of ball
	float ux = 1.0f;					//Initial horizontal velocity of ball
	float u = 0.0f;						//Initial vertical velocity of ball
	float m = 1.00;						//Mass of ball
	float mu = 0.01;					//Coefficient of static friction
	float Ff = m*g*mu;					//frictional force on the ball as it hits surface


	double mass;
	double radius;
private:


};
