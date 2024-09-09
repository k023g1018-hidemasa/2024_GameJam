#pragma once
#include<cmath>
#include "math/Vector2.h"
#include "Vector3f.h"
#include "Matrix4x4.h"

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct AABB {
	Vector3 min;
	Vector3 max;
};

Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 Multiply(Matrix4x4 a, Matrix4x4 b);
Matrix4x4 MakeScaleMatrix(const Vector3& a);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
bool IsCollision(const AABB& a, const AABB& b);