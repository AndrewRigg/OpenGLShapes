#include <GLM/glm.hpp>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "Ball.h"
#include "graphics.h"
#include "shapes.h"
#include "Physics.h"

using namespace std;

Ball::Ball() {};
Ball::~Ball() {}

glm::vec3 Ball::Momentum(glm::vec3 velocity, float mass) {
	return glm::vec3(velocity.x*mass, velocity.y*mass, velocity.z*mass);
}

float Ball::Friction(float mass, float g, float mu) {
	return (mass*g*mu);
}

float Ball::KineticEnergy(glm::vec3 velocity, float mass) {
	return (0.5*mass*pow(velocity.x, 2.0) + 0.5*mass*pow(velocity.y, 2.0) + 0.5*mass*pow(velocity.z, 2.0));
}

void Ball::setMass(float m) {
	mass = m;
}

float Ball::getMass() {
	return mass;
}

;