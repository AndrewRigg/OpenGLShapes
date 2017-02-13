#include <iostream>

#include "Boids.h"
#include "Vectors.h"

using namespace std;

const double pi = 3.1415926535897;
int no_neighbours = 100;
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

bool Boid::alive() {
	return lifeTime > 0;
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

void Boid::alignmentCohesionSeparation(Boid boids[]) {
	int neighbours = 0;
	align = vector3(0, 0, 0);
	cohes = vector3(0, 0, 0);
	separ = vector3(0, 0, 0);
	for (int i = 0; i < no_neighbours; i++) {
		if (boids[i] != *this) {
			if (boids[i].distance(*this) <= neighbourhood) {
				align += boids[i].velocity;
				cohes += boids[i].position;
				separ += boids[i].position - position;
				neighbours++;
			}
		}
	}
	if (neighbours > 0) {
		cohes /= neighbours;
		cohes -= position;
		cohes = cohes.normalize();
		separ /= neighbours;
		separ *= -1;
		separ = separ.normalize();
		align = align.normalize();
	}
}

void Boid::updatePhysics(float deltaTime)
{
	float depth = 1.0*abs(position.z);
		float edgeX1 = depth*0.6;
		float edgeX2 = depth*0.7;
		float edgeY1 = depth*0.3;
		float edgeY2 = depth*0.45;
		float edgeZ1 = -2.0;
		float edgeZ2 = -35;
		float wrapAroundX = edgeX1 + edgeX2;
		float wrapAroundY = edgeY1 + edgeY2;
		float wrapAroundZ = abs(edgeZ2 - edgeZ1);

		position.x += velocity.x*deltaTime;
		position.y += velocity.y*deltaTime;
		position.z += velocity.z*deltaTime;
		
		if (position.x < -edgeX1) {
			position.x += wrapAroundX;
		}
		if (position.x > edgeX2) {
			position.x -= wrapAroundX;
		}

		if (position.y < -edgeY1) {
			position.y += wrapAroundY;
		}
		if (position.y > edgeY2) {
			position.y -= wrapAroundY;
		}

		if (position.z < edgeZ1) {
			position.z += wrapAroundZ;
		}
		if (position.z > edgeZ2) {
			position.z -= wrapAroundZ;
		}
}

//vector3 Boid::direction(vector3 previous[]) {
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
//	return vector3(roll/10, pitch/10, yaw/10);
//}

vector3 Boid::direction() {
	//return the value of orientation around the x, y and z axis respectively in radians
	float roll, pitch, yaw;

	roll = atan2(velocity.z, velocity.y);
	//roll = 0;
	pitch = atan2(velocity.x, velocity.z);
	//pitch = 0;
	yaw = atan2(velocity.y, velocity.x);
	//yaw = 0;
	return vector3(roll, pitch, yaw);
}

;