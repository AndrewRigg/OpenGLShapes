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

bool Boid::operator!=(Boid rhs) {
	return (position != rhs.position || velocity != rhs.velocity);
}

float Boid::distance(Boid boid) {
	return sqrt(pow(boid.position.x, 2.0) + pow(boid.position.y, 2.0) + pow(boid.position.z, 2.0));
}

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

glm::vec3 Boid::alignment(Boid boids []) {
	//keep the boids going in the same direction
	//initialise a new vector which will calculate our new direction
	glm::vec3 alignment = glm::vec3(0.0f, 0.0f, 0.0f);
	//initialise a count variable to keep track of the number of neighbours
	int neighbours = 0;
	for (int i = 0; i < 10; i++) {
		if (boids[i] != *this) {
			if (boids[i].distance(*this) <= neighbourhood) {
				alignment.x += boids[i].velocity.x;
				alignment.y += boids[i].velocity.y;
				alignment.z += boids[i].velocity.z;
				neighbours++;
			}
		}
	}
	if (neighbours > 0) {
		//divide each component by number of neighbours
		alignment.x = alignment.x / neighbours;
		alignment.y = alignment.y / neighbours;
		alignment.z = alignment.z / neighbours;

		//normalise this vector
		alignment = glm::normalize(alignment);
	}
	//direct boid to centre of mass:
	return alignment;
}

glm::vec3 Boid::cohesion(Boid boids[]) {
	//keep the boids together in a group
	//initialise a new vector which will calculate our new direction
	glm::vec3 cohesion = glm::vec3(0.0f, 0.0f, 0.0f);
	//initialise a count variable to keep track of the number of neighbours
	int neighbours = 0;
	for (int i = 0; i < 10; i++) {
		if (boids[i] != *this) {
			if (boids[i].distance(*this) <= neighbourhood) {
				cohesion.x += boids[i].position.x;
				cohesion.y += boids[i].position.y;
				cohesion.z += boids[i].position.z;
				neighbours++;
			}
		}
	}
	if (neighbours > 0) {
		//divide each component by number of neighbours
		cohesion.x = cohesion.x / neighbours;
		cohesion.y = cohesion.y / neighbours;
		cohesion.z = cohesion.z / neighbours;

		//subtract from the cohesion vector the current position of the boid
		cohesion.x -= position.x;
		cohesion.y -= position.y;
		cohesion.z -= position.z;

		//normalise this vector
		cohesion = glm::normalize(cohesion);
	}
	//direct boid to centre of mass:
	return cohesion;
}

glm::vec3 Boid::separation(Boid boids[]) {
	//keep the boids separate from each other
	//initialise a new vector which will calculate our new direction
	glm::vec3 separation = glm::vec3(0.0f, 0.0f, 0.0f);
	//initialise a count variable to keep track of the number of neighbours
	int neighbours = 0;
	for (int i = 0; i < 10; i++) {
		if (boids[i] != *this) {
			if (boids[i].distance(*this) <= neighbourhood) {
				separation.x += boids[i].position.x - position.x;
				separation.y += boids[i].position.y - position.y;
				separation.z += boids[i].position.z - position.z;
				neighbours++;
			}
		}
	}
	if (neighbours > 0) {
		//divide each component by number of neighbours
		separation.x = separation.x / neighbours;
		separation.y = separation.y / neighbours;
		separation.z = separation.z / neighbours;

		separation.x *= -1;
		separation.y *= -1;
		separation.z *= -1;

		//normalise this vector
		separation = glm::normalize(separation);
	}
	//direct boid to centre of mass:
	return separation;
}



void Boid::updatePhysics(float deltaTime)
{

	lifeTime--;
	float screenWidth = 4;
	/*
	if (position.x > screenWidth) {
		position.x = -screenWidth;
	}
	if (position.x < -screenWidth) {
		position.x = screenWidth;
	}
	if (position.y > screenWidth) {
		position.y = -screenWidth;
	}
	if (position.y < screenWidth) {
		position.y = screenWidth;
	}
	if (position.z > screenWidth) {
		position.z = -screenWidth;
	}
	if (position.z < screenWidth) {
		position.z = screenWidth;
	}

	
	if (position.y - radius <= 0) {
		velocity.x *= 0.995;
		velocity.z *= 0.995;
		rate *= 0.99;
	}*/

	//if (position.x + velocity.x*deltaTime >= -3.0 + radius && position.x + velocity.x*deltaTime <= 3.0 - radius) {
		position.x += velocity.x*deltaTime;
	//}
	if (position.x + velocity.x*deltaTime <= -3.0 + radius || position.x + velocity.x*deltaTime >= 3.0 - radius) {
		//velocity.x = -velocity.x;
		if (position.x <= -3.0 + radius) {
			//velocity.x -= 0.2;
			position.x = +3.0;
		}
		if (position.x >= 3.0 - radius) {
			//velocity.x += 0.2;
			position.x = -3.0;
		}
	}

	//if (position.y + velocity.y*deltaTime >= -3.0 + radius && position.y + velocity.y*deltaTime <= 3.0 - radius) {
		//position.y += velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		velocity.y += g*deltaTime;
		
	//}
	if (position.y + velocity.y*deltaTime <= -3.0 + radius || position.y + velocity.y*deltaTime >= 3.0 - radius) {
		//velocity.y = -velocity.y;
		//position.y += velocity.y*deltaTime - 0.5*g*pow(deltaTime, 2.0);
		//velocity.y += g*deltaTime - 1;
		if (position.y <= -3.0 + radius) {
			position.y = +3.0;
		}
		if (position.y >= 3.0 - radius) {
			position.y = -3.0;
		}
	}

	//if (position.z + velocity.z*deltaTime >= -10.0 + radius && position.z + velocity.z*deltaTime <= -3.0 - radius) {
		position.z += velocity.z*deltaTime;
	//}
	if (position.z + velocity.z*deltaTime <= -10.0 + radius || position.z + velocity.z*deltaTime >= -3.0 - radius) {
		//velocity.z = -velocity.z;
		if (position.z <= -10.0 + radius) {
			//velocity.z -= 0.2;
			position.z = -3.0;
		}
		if (position.z >= -3.0 - radius) {
			//velocity.z += 0.2;
			position.z = -10.0;
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