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
int no_neighbours = 10;
Boid::Boid() {};
Boid::~Boid() {};

bool Boid::operator!=(Boid rhs) {
	return (position != rhs.position || velocity != rhs.velocity);
}

float Boid::speed() {
	return sqrt(pow(velocity.x, 2) + pow(velocity.y,2) + pow(velocity.z, 2));
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
	for (int i = 0; i < no_neighbours; i++) {
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
	for (int i = 0; i < no_neighbours; i++) {
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
	for (int i = 0; i < no_neighbours; i++) {
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
	float zSpread = 1.0*abs(position.z);
		float edgeXY = zSpread*0.8;
		float edgeZNear = -2.0;
		float edgeZFar = -35;
		float wrapAround = 2*edgeXY;
		float wrapAroundZ = abs(edgeZFar - edgeZNear);

		position.x += velocity.x*deltaTime;
		position.y += velocity.y*deltaTime;
		position.z += velocity.z*deltaTime;
		
		if (position.x <= -edgeXY + radius) {
			position.x += wrapAround;
		}
		if (position.x >= edgeXY - radius) {
			position.x -= wrapAround;
		}

		if (position.y <= -edgeXY + radius) {
			position.y += wrapAround;
		}
		if (position.y >= edgeXY - radius) {
			position.y -= wrapAround;
		}

		if (position.z <= edgeZFar + radius) {
			position.z += wrapAroundZ;
		}
		if (position.z >= edgeZNear - radius) {
			position.z -= wrapAroundZ;
		}
}

//glm::vec3 Boid::direction(glm::vec3 previous[]) {
//	//return the value of orientation around the x, y and z axis respectively in radians
//	float roll, pitch, yaw;
//
//	roll = atan2(velocity.z, velocity.y);
//	//roll = 0;
//	pitch = atan2(velocity.x, velocity.z);
//	//pitch = 0;
//	yaw = atan2(velocity.y, velocity.x);
//	//yaw = 0;
//	for (int i = 0; i < 10; i++) {
//		roll += previous[i].x;
//		pitch += previous[i].y;
//		yaw += previous[i].z;
//	}
//	return glm::vec3(roll/10, pitch/10, yaw/10);
//}

glm::vec3 Boid::direction() {
	//return the value of orientation around the x, y and z axis respectively in radians
	float roll, pitch, yaw;

	//roll = atan2(velocity.z, velocity.y);
	roll = 0;
	//pitch = atan2(velocity.x, velocity.z);
	pitch = 0;
	yaw = atan2(velocity.y, velocity.x);
	//yaw = 0;
	return glm::vec3(roll, pitch, yaw);
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