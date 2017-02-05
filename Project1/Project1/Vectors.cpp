#include <math.h>
#include "Vectors.h"

vector3::vector3() {};
vector3::~vector3() {}
vector3::vector3(float x, float y, float z){
	}
;

int vector3::equivalence(vector3 vec) {
	return(x == vec.x && y == vec.y && z == vec.z);
}

vector3 vector3::addition(vector3 vec) {
	return vector3(x + vec.x, y + vec.y, z + vec.z);
}

vector3 vector3::subtraction(vector3 vec) {
	return vector3(x - vec.x, y - vec.y, z - vec.z);
}

vector3 vector3::multiplication(vector3 vec) {
	return vector3(x * vec.x, y * vec.y, z * vec.z);
}

vector3 vector3::division(vector3 vec) {
	return vector3(x / vec.x, y / vec.y, z / vec.z);
}

vector3 vector3::additionScalar(float scalar) {
	return vector3(x + scalar, y + scalar, z + scalar);
}

vector3 vector3::subtractionScalar(float scalar) {
	return vector3(x - scalar, y - scalar, z - scalar);
}

vector3 vector3::multiplicationScalar(float scalar) {
	return vector3(x * scalar, y * scalar, z * scalar);
}

vector3 vector3::divisionScalar(float scalar) {
	return vector3(x / scalar, y / scalar, z / scalar);
}

vector3 vector3::cross_product(vector3 vec) {
	return vector3(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

float vector3::dot_product(vector3 vec) {
	return (x*vec.x + y*vec.y + z*vec.z);
}

float vector3::length() {
	//Try to not use sqrt here
	return (sqrt(x*x + y*y + z*z));
}

vector3 vector3::normalise() {
	return vector3(x / length(), y / length(), z / length());
}

;


