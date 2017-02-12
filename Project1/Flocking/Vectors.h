#pragma once

#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

class vector3 {

public:
	vector3();
	~vector3();
	vector3(float x, float y, float z);

	bool operator==(vector3 vec);
	bool operator!=(vector3 vec);
	vector3 operator+(vector3 vec);
	vector3 operator-(vector3 vec);
	vector3 operator*(vector3 vec);
	vector3 operator/(vector3 vec);
	vector3 operator+=(vector3 vec);
	vector3 operator-=(vector3 vec);
	vector3 operator*=(vector3 vec);
	vector3 operator/=(vector3 vec);
	vector3 operator+(float scalar);
	vector3 operator-(float scalar);
	vector3 operator*(float scalar);
	vector3 operator/(float scalar);
	vector3 operator+=(float scalar);
	vector3 operator-=(float scalar);
	vector3 operator*=(float scalar);
	vector3 operator/=(float scalar);
	vector3 cross(vector3 vec);
	vector3 normalise();
	float dot(vector3 vec);
	float length();
	glm::vec3 toVec3();
	float x;
	float y;
	float z;
};