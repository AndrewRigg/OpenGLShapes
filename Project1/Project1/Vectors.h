#pragma once

#include <math.h>

class vector3 {

public:
	vector3();
	~vector3();
	vector3(float x, float y, float z);

	int equivalence(vector3 vec);

	vector3 addition(vector3 vec);
	vector3 subtraction(vector3 vec);
	vector3 multiplication(vector3 vec);
	vector3 division(vector3 vec);
	vector3 additionScalar(float scalar);
	vector3 subtractionScalar(float scalar);
	vector3 multiplicationScalar(float scalar);
	vector3 divisionScalar(float scalar);
	vector3 cross_product(vector3 vec);
	float dot_product(vector3 vec);
	float length();
	vector3 normalise();

	float x;
	float y;
	float z;
};