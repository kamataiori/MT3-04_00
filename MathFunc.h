#pragma once
#include "struct.h"
#include <Novice.h>
#include <assert.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <imgui.h>

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

Matrix4x4 Add(Matrix4x4& m1, Matrix4x4& m2);

Vector3 Add(const Vector3& v1, const Vector3& v2);

Matrix4x4 Subtract(Matrix4x4& m1, Matrix4x4& m2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Vector3 Multiply(Vector3& v1, Vector3& v2);

Vector3 Multiply(const float& f, const Vector3& v1);

Matrix4x4 Inverse(Matrix4x4& m1);

Matrix4x4 Transpose(Matrix4x4& m1);

Matrix4x4 MakeIdentify4x4();

Matrix4x4 MakeScaleMatrix(Vector3& scale);

Matrix4x4 MakeTranslateMatrix(Vector3& transform);

Vector3 Transform(const Vector3& vector, const Matrix4x4& Matrix);

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

bool IsCollision(const Sphere& s1, const Sphere& s2);

bool IsCollision(const Sphere& sphere, const Plane& plane);

bool IsCollision(const Segment& segment, const Plane& plane);

bool IsCollision(const Segment& segment, const Triangle& triangle);

bool IsCollision(const AABB& aabb1, const AABB& aabb2);

bool IsCollision(const AABB& aabb, const Sphere& sphere);

bool IsCollision(const AABB& aabb, const Segment& segment);

float Length(const Vector3& point1, const Vector3& point2);

Vector3 Perpendicular(const Vector3& vector);

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color, uint32_t color2, uint32_t color3, uint32_t color4);

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color);

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color);

Vector3 Normalize(Vector3 v);

float Dot(Vector3 v1, Vector3 v2);

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color);

Vector3 CatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t);

void DrawCatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3, Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color);

void MakeSpring(Spring& spring, Ball& ball);

void DrawSpring(const Spring& spring, const Ball& ball, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);


Vector3 divide(const Vector3& v1, float v2);

float Length(const Vector3 & vector);
