#include "Matrix.h"
#include <math.h>


Matrix::Matrix() {};
Matrix::~Matrix() {};

int Matrix::width() {
	return 4;
}

int Matrix::height() {
	return 4;
}

Matrix::Matrix(float[4][1])
{
}

Matrix::Matrix(float[4][4])
{
}

//Matrix Matrix::rotationX(float theta) {
//	Matrix xRot = { 1.0f,0.0f,0.0f,0.0f,
//				0.0f,(float)cos(theta),(float)-sin(theta),0.0f,
//				0.0f,(float)sin(theta),(float)cos(theta),0.0f,
//				0.0f,0.0f,0.0f,1.0f};
//
//	Matrix result = matmult(xRot, Matrix());
//}
//
//Matrix Matrix::rotationY(float theta) {
//	Matrix yRot = { cos(theta),	0,			sin(theta), 0,
//		0,			1,			0,			0,
//		-sin(theta),0,			cos(theta),	0,
//		0,			0,			0,			1 };
//
//	Matrix result = matmult(yRot, Matrix());
//}
//
//Matrix Matrix::rotationZ(float theta) {
//	Matrix zRot = { cos(theta),	-sin(theta),0,		0,
//		sin(theta),	cos(theta),	0,		0,
//		0,			0,			1,		0,
//		0,			0,			0,		1 };
//
//	Matrix result = matmult(zRot, Matrix());
//}
//
//Matrix matmult(Matrix &A, Matrix B) {
//	//check that the matrices are compatible to multiply
//	Matrix	result;
//	if (A.width != B.height) {
//		return 0;
//	}
//	else {
//		//matrix multiply the matrix A and B
//
//		for (int i = 0; i < A.width; i++) {
//			for (int k = 0; k < B.width; k++) {
//				for (int j = 0; j < A.height; j++) {
//					result[i][k] += A[i][j] * B[j][k];
//				}
//			}
//		}
//	}
//	//copy resulting matrix back into matrix A
//	for (int i = 0; i < A.width; i++) {
//		for (int k = 0; k < A.height; k++) {
//			A[i][k] = result[i][k];
//		}
//	}
//	return A;
//}