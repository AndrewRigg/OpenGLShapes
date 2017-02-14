#pragma once


class Matrix {

public:
	Matrix();
	~Matrix();

	int width();
	int height();
	Matrix(float[4][1]);
	Matrix(float[4][4]);

	Matrix rotationX(float theta);
	Matrix rotationY(float theta);
	Matrix rotationZ(float theta);

	float mat4x1[4][1];
	float mat4x4[4][4];
	float cols4[4];
	float cols1[1];
	float rows[4];

};