#include "Vector3f.h"
#include <math.h>

Vector3 Add(const Vector3& v1, const Vector3& v2){
	Vector3 result{ 0 };
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2){
	Vector3 result = { 0 };
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Multiply(float scalar, const Vector3& v){
	Vector3 result = { 0 };
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2){
	float result = ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
	return result;
}

float Length(const Vector3& v){
	Vector3 result{};
	result.x = v.x * v.x;
	result.y = v.y * v.y;
	result.z = v.z * v.z;

	float length = sqrtf(result.x + result.y + result.z);
	return length;
}

Vector3 Normalize(const Vector3& v){
	Vector3 result;
	float len = Length(v);

	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;

	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2){
	Vector3 result{};
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

Vector3 UnitVector(const Vector3& v){
	float length = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	return Vector3(v.x / length, v.y / length, v.z / length);
}
