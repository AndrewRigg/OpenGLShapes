#include <math.h>
#include "Vectors.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

vector3::vector3() {};
vector3::~vector3() {}
vector3::vector3(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
	}
;

bool vector3::operator==(vector3 vec) {
	return(x == vec.x && y == vec.y && z == vec.z);
}

bool vector3::operator!=(vector3 vec) {
	return(x != vec.x || y != vec.y || z != vec.z);
}

vector3 vector3::operator+(vector3 vec) {
	return vector3(x + vec.x, y + vec.y, z + vec.z);
}

vector3 vector3::operator-(vector3 vec) {
	return vector3(x - vec.x, y - vec.y, z - vec.z);
}

vector3 vector3::operator*(vector3 vec) {
	return vector3(x * vec.x, y * vec.y, z * vec.z);
}

vector3 vector3::operator/(vector3 vec) {
	return vector3(x / vec.x, y / vec.y, z / vec.z);
}

vector3 vector3::operator+=(vector3 vec) {
	return vector3(x + vec.x, y + vec.y, z + vec.z);
}

vector3 vector3::operator-=(vector3 vec) {
	return vector3(x - vec.x, y - vec.y, z - vec.z);
}

vector3 vector3::operator*=(vector3 vec) {
	return vector3(x*vec.x, y*vec.y, z*vec.z);
}

vector3 vector3::operator/=(vector3 vec) {
	return vector3(x / vec.x, y / vec.y, z / vec.z);
}

vector3 vector3::operator+(float scalar) {
	return vector3(x + scalar, y + scalar, z + scalar);
}

vector3 vector3::operator-(float scalar) {
	return vector3(x - scalar, y - scalar, z - scalar);
}

vector3 vector3::operator*(float scalar) {
	return vector3(x * scalar, y * scalar, z * scalar);
}

vector3 vector3::operator/(float scalar) {
	return vector3(x / scalar, y / scalar, z / scalar);
}

vector3 vector3::operator+=(float scalar) {
	return vector3(x + scalar, y + scalar, z + scalar);
}

vector3 vector3::operator-=(float scalar) {
	return vector3(x - scalar, y - scalar, z - scalar);
}

vector3 vector3::operator*=(float scalar) {
	return vector3(x*scalar, y*scalar, z*scalar);
}

vector3 vector3::operator/=(float scalar) {
	return vector3(x / scalar, y / scalar, z / scalar);
}

vector3 vector3::cross(vector3 vec) {
	return vector3(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

float vector3::dot(vector3 vec) {
	return (x*vec.x + y*vec.y + z*vec.z);
}

float vector3::length() {
	return (sqrt(x*x + y*y + z*z));
}

vector3 vector3::normalise() {
	return vector3(x / length(), y / length(), z / length());
}

glm::vec3 vector3::toVec3() {
	return glm::vec3(x, y, z);
}

;


