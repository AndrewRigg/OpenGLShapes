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
#include "Vectors.h"

using namespace std;

const double pi = 3.1415926535897;

Ball::Ball() {};
Ball::~Ball() {};


glm::vec3 Ball::Momentum() {
	return glm::vec3(velocity.x*mass, velocity.y*mass, velocity.z*mass);
}

glm::vec3 Ball::GravitationalForce() {
	return glm::vec3(0.0, mass*g, 0.0f);
}

glm::vec3 Ball::Friction() {
	return glm::vec3(0, mass*g*mu, 0);
}

glm::vec3 Ball::TotalForce() {
	return glm::vec3(GravitationalForce()+Friction()+action);
}

float Ball::KineticEnergy() {
	return (0.5*mass*(pow(velocity.x, 2.0) + pow(velocity.y, 2.0) + pow(velocity.z, 2.0)));
}

float Ball::PotentialEnergy() {
	return(mass*g*position.y);
}

float Ball::volume() {
	return 4 / 3 * pi * pow(radius, 3.0);
}

void Ball::setMass(float m) {
	mass = m;
}

float Ball::getMass() {
	return mass;
}

bool Ball::alive() {
	return lifeTime > 0;
}

void Ball::setAction(glm::vec3 appliedAction) {
	action = appliedAction;
}

glm::vec3 Ball::getAction() {
	return action;
}

void Ball::setRadius(float newRadius) {
	radius = newRadius;
}

float Ball::getRadius() {
	return radius;
}


void Ball::updatePhysics(float deltaTime)
{
	lifeTime--;


	/*if (position.y - radius <= 0) {
		velocity.x *= 0.995;
		velocity.z *= 0.995;
		rate *= 0.99;
	}*/

		position.x += velocity.x*deltaTime;
		position.y += velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		velocity.y += g*deltaTime;
		position.z += velocity.z*deltaTime;

	if (position.x + velocity.x*deltaTime <= -5.0 + radius || position.x + velocity.x*deltaTime >= 5.0 - radius) {
		if (mass > 0) {
			velocity.x = -velocity.x;
			lifeTime = 0;
			if (position.x <= -5.0 + radius) {
				velocity.x -= 0.2;
			}
			if (position.x >= 5.0 - radius) {
				velocity.x += 0.2;
			}
		}
	}

		

	if (position.y + velocity.y*deltaTime <= -3.0 + radius || position.y + velocity.y*deltaTime >= 10.0 - radius) {
		if (mass > 0) {
			velocity.y = -velocity.y;
			lifeTime = 0;
			position.y += velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
			velocity.y += g*deltaTime - 1;
			//Not sure if the following works
			angular_velocity.x += 0.01;
			angular_velocity.y += 0.01;
			angular_velocity.z += 0.01;
			//rate *= 0.999;
		}
	}

	if (position.z + velocity.z*deltaTime <= -20.0 + radius || position.z + velocity.z*deltaTime >= -5.0 - radius) {
		if (mass > 0) {
			velocity.z = -velocity.z;
			lifeTime = 0;
			if (position.z <= -20.0 + radius) {
				velocity.z -= 0.2;
			}
			if (position.z >= -5.0 - radius) {
				velocity.z += 0.2;
			}
		}
	}
}


//Own versions
/*
vector3 Ball::Momentum() {
return vector3(velocity.x*mass, velocity.y*mass, velocity.z*mass);
}

vector3 Ball::GravitationalForce() {
return vector3(0.0, mass*g, 0.0f);
}

vector3 Ball::Friction() {
return vector3(0, mass*g*mu, 0);
}

vector3 Ball::TotalForce() {
return vector3(GravitationalForce()+Friction()+action);
}

float Ball::KineticEnergy() {
return (0.5*mass*(pow(velocity.x, 2.0) + pow(velocity.y, 2.0) + pow(velocity.z, 2.0)));
}

float Ball::PotentialEnergy() {
return(mass*g*position.y);
}

float Ball::volume() {
return 4 / 3 * pi * pow(radius, 3.0);
}

void Ball::setMass(float m) {
mass = m;
}

float Ball::getMass() {
return mass;
}

void Ball::setAlive(bool isAlive) {
alive = isAlive;
}

bool Ball::getAlive() {
return alive;
}

void Ball::setAction(vector3 appliedAction) {
action = appliedAction;
}

vector3 Ball::getAction() {
return action;
}

void Ball::setRadius(float newRadius) {
radius = newRadius;
}

float Ball::getRadius() {
return radius;
}

*/

;