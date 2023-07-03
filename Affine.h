#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include <cassert>
#include<math.h>

Matrix4x4 MakeRotateXMatrix(float theta);
Matrix4x4 MakeRotateYMatrix(float theta);

Matrix4x4 MakeRotateZMatrix(float theta);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Vector3 Normalize(const Vector3& v);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, Vector3& translate);

Matrix4x4 Inverse(const Matrix4x4& m);