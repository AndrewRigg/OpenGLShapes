#pragma once

#include <GLM/glm.hpp>
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
	vector3 operator+=(const vector3 &vec);
	vector3 operator-=(const vector3 &vec);
	vector3 operator*=(const vector3 &vec);
	vector3 operator/=(const vector3 &vec);
	vector3 operator+(float scalar);
	vector3 operator-(float scalar);
	vector3 operator*(float scalar);
	vector3 operator/(float scalar);
	vector3 operator+=(float scalar);
	vector3 operator-=(float scalar);
	vector3 operator*=(float scalar);
	vector3 operator/=(float scalar);
	vector3 cross(vector3 vec);
	vector3 normalize();
	float dot(vector3 vec);
	float length();
	glm::vec3 toVec3();
	float x;
	float y;
	float z;
};