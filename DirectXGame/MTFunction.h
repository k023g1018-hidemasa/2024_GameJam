#pragma once
//#include <Novice.h>
#include<cmath>
#include "Vector3.h"
#include "Matrix4x4.h"
#include<assert.h>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 Multiply(Matrix4x4 a, Matrix4x4 b);
Matrix4x4 MakeScaleMatrix(const Vector3& a);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
<<<<<<< Updated upstream
//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
=======
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
bool IsCollision(const AABB& a, const AABB& b);
Vector3 Transform(const Vector3& vector, const Matrix4x4& mattrix);
>>>>>>> Stashed changes
