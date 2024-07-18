#pragma once
#include "Vector4.h"
#include "Vector3.h"

static const int kColumnWidth = 60;
static const int kColumnHeight = 20;
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

struct Matrix4x4 {
	float m[4][4];

	Matrix4x4 operator*(const Matrix4x4& other) const {
		Matrix4x4 result = {};
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.m[i][j] = 0;
				for (int k = 0; k < 4; ++k) {
					result.m[i][j] += m[i][k] * other.m[k][j];
				}
			}
		}
		return result;
	}

};

struct Sphere {
	Vector3 center;
	float radius;
	int color;
};

struct Plane {
	Vector3 normal;
	float distance;
};

struct Line {
	Vector3 origin; //start point
	Vector3 diff; //difference between start and end
};

struct Ray {
	Vector3 origin; //start point
	Vector3 diff; //difference between start and end
};

struct Segment {
	Vector3 origin; //start point
	Vector3 diff; //difference between start and end
	int color;
};

struct Triangle {
	Vector3 vertices[3];
	int color;
};

struct AABB {
	Vector3 min;
	Vector3 max;
	int color;
};

struct Spring {
	Vector3 anchor;
	float naturalLength;
	float stiffness;
	float dampingCoefficient;
};

struct Ball {
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;
	float radius;
	unsigned int color;
};