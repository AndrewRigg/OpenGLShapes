#include <GLM/glm.hpp>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "Boids.h"
#include "graphics.h"
#include "shapes.h"
#include "Physics.h"
#include "Vectors.h"

using namespace std;

const double pi = 3.1415926535897;

Boid::Boid() {};
Boid::~Boid() {};


glm::vec3 Boid::Momentum() {
	return glm::vec3(velocity.x*mass, velocity.y*mass, velocity.z*mass);
}

glm::vec3 Boid::GravitationalForce() {
	return glm::vec3(0.0, mass*g, 0.0f);
}

glm::vec3 Boid::Friction() {
	return glm::vec3(0, mass*g*mu, 0);
}

glm::vec3 Boid::TotalForce() {
	return glm::vec3(GravitationalForce()+Friction()+action);
}

float Boid::KineticEnergy() {
	return (0.5*mass*(pow(velocity.x, 2.0) + pow(velocity.y, 2.0) + pow(velocity.z, 2.0)));
}

float Boid::PotentialEnergy() {
	return(mass*g*position.y);
}

float Boid::volume() {
	return 4 / 3 * pi * pow(radius, 3.0);
}

void Boid::setMass(float m) {
	mass = m;
}

float Boid::getMass() {
	return mass;
}

bool Boid::alive() {
	return lifeTime > 0;
}

void Boid::setAction(glm::vec3 appliedAction) {
	action = appliedAction;
}

glm::vec3 Boid::getAction() {
	return action;
}

void Boid::setRadius(float newRadius) {
	radius = newRadius;
}

float Boid::getRadius() {
	return radius;
}


//3 Boid behaviours

void Boid::neighbours(vector <Boid> boids) {


	for (Boid boid : boids) {
		float diff_x = position.x - boid.position.x;
		float diff_y = position.y - boid.position.y;
		float diff_z = position.z - boid.position.z;

		if (diff_x <= neighbourhood && diff_y <= neighbourhood && diff_z <= neighbourhood) {
			neighbouring_boids.push_back(boid);
		}
	}	
}

void Boid::cohesion() {
	//keep the boids together in a group
	glm::vec3 centre_of_mass = glm::vec3(0.0f,0.0f,0.0f);
	for (Boid boid : neighbouring_boids) {
		centre_of_mass += boid.position;
	}
	centre_of_mass = centre_of_mass.operator/=(neighbouring_boids.size());

}

void Boid::separation() {
	//keep the boids separate from each other

}

void Boid::alignment() {
	//keep the boids going in the same direction
}

void Boid::updatePhysics(float deltaTime)
{


	lifeTime--;

	if (position.y - radius <= 0) {
		velocity.x *= 0.995;
		velocity.z *= 0.995;
		rate *= 0.99;
	}

	if (position.x + velocity.x*deltaTime >= -4.0 + radius && position.x + velocity.x*deltaTime <= 4.0 - radius) {
		position.x += velocity.x*deltaTime;
	}
	if (position.x + velocity.x*deltaTime <= -4.0 + radius || position.x + velocity.x*deltaTime >= 4.0 - radius) {
		velocity.x = -velocity.x;
		if (position.x <= -3.0 + radius) {
			velocity.x -= 0.2;
		}
		if (position.x >= 3.0 - radius) {
			velocity.x += 0.2;
		}
	}

	if (position.y + velocity.y*deltaTime >= -4.0 + radius && position.y + velocity.y*deltaTime <= 4.0 - radius) {
		position.y += velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		velocity.y += g*deltaTime;
	}
	if (position.y + velocity.y*deltaTime <= -4.0 + radius || position.y + velocity.y*deltaTime >= 4.0 - radius) {
		velocity.y = -velocity.y;
		position.y += velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		velocity.y += g*deltaTime - 1;
		//Not sure if the following works
		angular_velocity.x += 0.01;
		angular_velocity.y += 0.01;
		angular_velocity.z += 0.01;
		//rate *= 0.999;
	}

	if (position.z + velocity.z*deltaTime >= -10.0 + radius && position.z + velocity.z*deltaTime <= -3.0 - radius) {
		position.z += velocity.z*deltaTime;
	}
	if (position.z + velocity.z*deltaTime <= -10.0 + radius || position.z + velocity.z*deltaTime >= -3.0 - radius) {
		velocity.z = -velocity.z;
		if (position.z <= -10.0 + radius) {
			velocity.z -= 0.2;
		}
		if (position.z >= -3.0 - radius) {
			velocity.z += 0.2;
		}
	}
}


//Own versions
/*
vector3 Boid::Momentum() {
return vector3(velocity.x*mass, velocity.y*mass, velocity.z*mass);
}

vector3 Boid::GravitationalForce() {
return vector3(0.0, mass*g, 0.0f);
}

vector3 Boid::Friction() {
return vector3(0, mass*g*mu, 0);
}

vector3 Boid::TotalForce() {
return vector3(GravitationalForce()+Friction()+action);
}

float Boid::KineticEnergy() {
return (0.5*mass*(pow(velocity.x, 2.0) + pow(velocity.y, 2.0) + pow(velocity.z, 2.0)));
}

float Boid::PotentialEnergy() {
return(mass*g*position.y);
}

float Boid::volume() {
return 4 / 3 * pi * pow(radius, 3.0);
}

void Boid::setMass(float m) {
mass = m;
}

float Boid::getMass() {
return mass;
}

void Boid::setAlive(bool isAlive) {
alive = isAlive;
}

bool Boid::getAlive() {
return alive;
}

void Boid::setAction(vector3 appliedAction) {
action = appliedAction;
}

vector3 Boid::getAction() {
return action;
}

void Boid::setRadius(float newRadius) {
radius = newRadius;
}

float Boid::getRadius() {
return radius;
}

*/

;