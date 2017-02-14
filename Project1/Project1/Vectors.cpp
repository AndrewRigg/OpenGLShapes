#include "Vectors.h"
#include <GLM/glm.hpp>

vector3::vector3() {};
vector3::~vector3() {};
vector3::vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
};

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

vector3 vector3::operator+=(const vector3 &vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

vector3 vector3::operator-=(const vector3 &vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

vector3 vector3::operator*=(const vector3 &vec) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

vector3 vector3::operator/=(const vector3 &vec) {
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
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
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}

vector3 vector3::operator-=(float scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
}

vector3 vector3::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

vector3 vector3::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
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

vector3 vector3::normalize() {
	return vector3(x / length(), y / length(), z / length());
}

glm::vec3 vector3::toVec3() {
	return glm::vec3(x, y, z);
}

;


