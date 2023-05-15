#include "Affine.h"

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 A;
	A.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
	            m1.m[0][3] * m2.m[3][0];
	A.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
	            m1.m[1][3] * m2.m[3][0];
	A.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
	            m1.m[2][3] * m2.m[3][0];
	A.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
	            m1.m[3][3] * m2.m[3][0];

	A.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
	            m1.m[0][3] * m2.m[3][1];
	A.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
	            m1.m[1][3] * m2.m[3][1];
	A.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
	            m1.m[2][3] * m2.m[3][1];
	A.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
	            m1.m[3][3] * m2.m[3][1];

	A.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
	            m1.m[0][3] * m2.m[3][2];
	A.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
	            m1.m[1][3] * m2.m[3][2];
	A.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
	            m1.m[2][3] * m2.m[3][2];
	A.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
	            m1.m[3][3] * m2.m[3][2];

	A.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
	            m1.m[0][3] * m2.m[3][3];
	A.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
	            m1.m[1][3] * m2.m[3][3];
	A.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
	            m1.m[2][3] * m2.m[3][3];
	A.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
	            m1.m[3][3] * m2.m[3][3];

	return A;
}

Matrix4x4 MakeRotateXMatrix(float theta) {
	Matrix4x4 A;

	A.m[0][0] = 1.0f;
	A.m[0][1] = 0.0f;
	A.m[0][2] = 0.0f;
	A.m[0][3] = 0.0f;

	A.m[1][0] = 0.0f;
	A.m[1][1] = std::cos(theta);
	A.m[1][2] = std::sin(theta);
	A.m[1][3] = 0.0f;

	A.m[2][0] = 0.0f;
	A.m[2][1] = -std::sin(theta);
	A.m[2][2] = std::cos(theta);
	A.m[2][3] = 0.0f;

	A.m[3][0] = 0.0f;
	A.m[3][1] = 0.0f;
	A.m[3][2] = 0.0f;
	A.m[3][3] = 1.0f;

	return A;
}
Matrix4x4 MakeRotateYMatrix(float theta) {
	Matrix4x4 A;

	A.m[0][0] = std::cos(theta);
	A.m[0][1] = 0.0f;
	A.m[0][2] = -std::sin(theta);
	A.m[0][3] = 0.0f;

	A.m[1][0] = 0.0f;
	A.m[1][1] = 1.0f;
	A.m[1][2] = 0.0f;
	A.m[1][3] = 0.0f;

	A.m[2][0] = std::sin(theta);
	A.m[2][1] = 0.0f;
	A.m[2][2] = std::cos(theta);
	A.m[2][3] = 0.0f;

	A.m[3][0] = 0.0f;
	A.m[3][1] = 0.0f;
	A.m[3][2] = 0.0f;
	A.m[3][3] = 1.0f;

	return A;
}
Matrix4x4 MakeRotateZMatrix(float theta) {
	Matrix4x4 A;

	A.m[0][0] = std::cos(theta);
	A.m[0][1] = -std::sin(theta);
	A.m[0][2] = 0.0f;
	A.m[0][3] = 0.0f;

	A.m[1][0] = std::sin(theta);
	A.m[1][1] = std::cos(theta);
	A.m[1][2] = 0.0f;
	A.m[1][3] = 0.0f;

	A.m[2][0] = 0.0f;
	A.m[2][1] = 0.0f;
	A.m[2][2] = 1.0f;
	A.m[2][3] = 0.0f;

	A.m[3][0] = 0.0f;
	A.m[3][1] = 0.0f;
	A.m[3][2] = 0.0f;
	A.m[3][3] = 1.0f;

	return A;
}

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{

	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};

	return result;
}



Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, Vector3& translate) {
	Matrix4x4 A;

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rot.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rot.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rot.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	A.m[0][0] = scale.x * rotateXYZMatrix.m[0][0];
	A.m[0][1] = scale.x * rotateXYZMatrix.m[0][1];
	A.m[0][2] = scale.x * rotateXYZMatrix.m[0][2];
	A.m[0][3] = 0.0f;

	A.m[1][0] = scale.y * rotateXYZMatrix.m[1][0];
	A.m[1][1] = scale.y * rotateXYZMatrix.m[1][1];
	A.m[1][2] = scale.y * rotateXYZMatrix.m[1][2];
	A.m[1][3] = 0.0f;

	A.m[2][0] = scale.z * rotateXYZMatrix.m[2][0];
	A.m[2][1] = scale.z * rotateXYZMatrix.m[2][1];
	A.m[2][2] = scale.z * rotateXYZMatrix.m[2][2];
	A.m[2][3] = 0.0f;

	A.m[3][0] = translate.x;
	A.m[3][1] = translate.y;
	A.m[3][2] = translate.z;
	A.m[3][3] = 1.0f;
	return A;
}
