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

void Ball::setAlive(bool isAlive) {
	alive = isAlive;
}

bool Ball::getAlive() {
	return alive;
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