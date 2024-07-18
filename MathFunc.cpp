#include "MathFunc.h"
#include <algorithm>

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubDivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubDivision);
	Vector3 start[kSubDivision + 1]{};
	Vector3 end[kSubDivision + 1]{};
	Vector3 ndcVertexStart[kSubDivision + 1]{};
	Vector3 screenVerticesStart[kSubDivision + 1]{};
	Vector3 ndcVertexEnd[kSubDivision + 1]{};
	Vector3 screenVerticesEnd[kSubDivision + 1]{};
	int color = 0xAAAAAAFF;

	for (uint32_t xIndex = 0; xIndex <= kSubDivision; xIndex++) {
		// Vector3 pos;

		start[xIndex].x = (-5.0f + xIndex) * kGridEvery; // start of the x line
		end[xIndex].x = (-5.0f + xIndex) * kGridEvery;
		start[xIndex].z = -kGridHalfWidth; // space between lines
		end[xIndex].z = kGridHalfWidth;
		// pos.x = -kGridHalfWidth + xIndex * kGridEvery; // Calculate the x position

		ndcVertexStart[xIndex] = Transform(start[xIndex], viewProjectionMatrix); // change into screen coord
		screenVerticesStart[xIndex] = Transform(ndcVertexStart[xIndex], viewportMatrix);
		ndcVertexEnd[xIndex] = Transform(end[xIndex], viewProjectionMatrix);
		screenVerticesEnd[xIndex] = Transform(ndcVertexEnd[xIndex], viewportMatrix);

		if (xIndex == 5) {
			color = BLACK;
		}
		else {
			color = 0xAAAAAAFF;
		}

		//Novice::ScreenPrintf(0, 30 * xIndex, "%f", start[xIndex].x);
		//Novice::ScreenPrintf(100, 30 * xIndex, "%f", end[xIndex].x);
		Novice::DrawLine((int)screenVerticesStart[xIndex].x, (int)screenVerticesStart[xIndex].y, (int)screenVerticesEnd[xIndex].x, (int)screenVerticesEnd[xIndex].y, color);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubDivision; zIndex++) {

		start[zIndex].x = -kGridHalfWidth;
		end[zIndex].x = kGridHalfWidth;
		start[zIndex].z = (-5.0f + zIndex) * kGridEvery;
		end[zIndex].z = (-5.0f + zIndex) * kGridEvery;
		ndcVertexStart[zIndex] = Transform(start[zIndex], viewProjectionMatrix);
		screenVerticesStart[zIndex] = Transform(ndcVertexStart[zIndex], viewportMatrix);
		ndcVertexEnd[zIndex] = Transform(end[zIndex], viewProjectionMatrix);
		screenVerticesEnd[zIndex] = Transform(ndcVertexEnd[zIndex], viewportMatrix);
		// pos.x = -kGridHalfWidth + xIndex * kGridEvery; // Calculate the x position

		if (zIndex == 5) {
			color = BLACK;
		}
		else {
			color = 0xAAAAAAFF;
		}

		//Novice::ScreenPrintf(300, 30 * zIndex, "%f", start[zIndex].z);
		//Novice::ScreenPrintf(500, 30 * zIndex, "%f", end[zIndex].z);
		Novice::DrawLine((int)screenVerticesStart[zIndex].x, (int)screenVerticesStart[zIndex].y, (int)screenVerticesEnd[zIndex].x, (int)screenVerticesEnd[zIndex].y, color);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 20; // amount of lines
	const float pi = float(M_PI);
	const float longD = pi / kSubdivision;		// longitude of 1 line
	const float latiD = (2 * pi) / kSubdivision;	// latitude of 1 line

	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++) {
		float lat = (-pi / 2.0f) + (latiD * latIndex); // the latitude line we are currently on

		for (uint32_t longIndex = 0; longIndex < kSubdivision; longIndex++) {
			float lon = longIndex * longD; // the longitude line we are currently on

			Vector3 a, b, c;

			a = { cosf(lat) * cosf(lon) * sphere.radius + sphere.center.x, sinf(lat) * sphere.radius + sphere.center.y, cosf(lat) * sinf(lon) * sphere.radius + sphere.center.z };
			b = { cosf(lat + latiD) * cosf(lon) * sphere.radius + sphere.center.x, sinf(lat + latiD) * sphere.radius + sphere.center.y, cosf(lat + latiD) * sin(lon) * sphere.radius + sphere.center.z };
			c = { cosf(lat) * cosf(lon + longD) * sphere.radius + sphere.center.x, sinf(lat) * sphere.radius + sphere.center.y, cosf(lat) * sinf(lon + longD) * sphere.radius + sphere.center.z };

			Vector3 screenTransformA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenTransformB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenTransformC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);
			Novice::DrawLine((int)screenTransformA.x, (int)screenTransformA.y, (int)screenTransformB.x, (int)screenTransformB.y, color);
			Novice::DrawLine((int)screenTransformA.x, (int)screenTransformA.y, (int)screenTransformC.x, (int)screenTransformC.y, color);
		}
	}
}

Matrix4x4 Add(Matrix4x4& m1, Matrix4x4& m2) {
	Matrix4x4 result{
		m1.m[0][0] + m2.m[0][0], m1.m[0][1] + m2.m[0][1], m1.m[0][2] + m2.m[0][2], m1.m[0][3] + m2.m[0][3], m1.m[1][0] + m2.m[1][0], m1.m[1][1] + m2.m[1][1],
		m1.m[1][2] + m2.m[1][2], m1.m[1][3] + m2.m[1][3], m1.m[2][0] + m2.m[2][0], m1.m[2][1] + m2.m[2][1], m1.m[2][2] + m2.m[2][2], m1.m[2][3] + m2.m[2][3],
		m1.m[3][0] + m2.m[3][0], m1.m[3][1] + m2.m[3][1], m1.m[3][2] + m2.m[3][2], m1.m[3][3] + m2.m[3][3],
	};

	return result;
}

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	return result;
}

Matrix4x4 Subtract(Matrix4x4& m1, Matrix4x4& m2) {
	Matrix4x4 result{
		m1.m[0][0] - m2.m[0][0], m1.m[0][1] - m2.m[0][1], m1.m[0][2] - m2.m[0][2], m1.m[0][3] - m2.m[0][3], m1.m[1][0] - m2.m[1][0], m1.m[1][1] - m2.m[1][1],
		m1.m[1][2] - m2.m[1][2], m1.m[1][3] - m2.m[1][3], m1.m[2][0] - m2.m[2][0], m1.m[2][1] - m2.m[2][1], m1.m[2][2] - m2.m[2][2], m1.m[2][3] - m2.m[2][3],
		m1.m[3][0] - m2.m[3][0], m1.m[3][1] - m2.m[3][1], m1.m[3][2] - m2.m[3][2], m1.m[3][3] - m2.m[3][3],
	};
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{
		m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
		/*here*/ m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
		/*here*/ m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
		/*here*/ m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],
		m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
		/*here*/ m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
		/*here*/ m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
		/*here*/ m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],
		m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
		/*here*/ m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
		/*here*/ m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
		/*here*/ m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],
		m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
		/*here*/ m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
		/*here*/ m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
		/*here*/ m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3],

	};
	return result;
}

Vector3 Multiply(Vector3& v1, Vector3& v2)
{
	Vector3 result
	{
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	};
	return result;
}

Vector3 Multiply(const float& f, const Vector3& v1)
{
	Vector3 result
	{
		f * v1.x,
		f * v1.y,
		f * v1.z
	};
	return result;
}

Matrix4x4 Inverse(Matrix4x4& m1) {
	float A = m1.m[0][0] * m1.m[1][1] * m1.m[2][2] * m1.m[3][3] + m1.m[0][0] * m1.m[1][2] * m1.m[2][3] * m1.m[3][1] + m1.m[0][0] * m1.m[1][3] * m1.m[2][1] * m1.m[3][2] -
		m1.m[0][0] * m1.m[1][3] * m1.m[2][2] * m1.m[3][1] - m1.m[0][0] * m1.m[1][2] * m1.m[2][1] * m1.m[3][3] - m1.m[0][0] * m1.m[1][1] * m1.m[2][3] * m1.m[3][2] -
		m1.m[0][1] * m1.m[1][0] * m1.m[2][2] * m1.m[3][3] - m1.m[0][2] * m1.m[1][0] * m1.m[2][3] * m1.m[3][1] - m1.m[0][3] * m1.m[1][0] * m1.m[2][1] * m1.m[3][2] +
		m1.m[0][3] * m1.m[1][0] * m1.m[2][2] * m1.m[3][1] + m1.m[0][2] * m1.m[1][0] * m1.m[2][1] * m1.m[3][3] + m1.m[0][1] * m1.m[1][0] * m1.m[2][3] * m1.m[3][2] +
		m1.m[0][1] * m1.m[1][2] * m1.m[2][0] * m1.m[3][3] + m1.m[0][2] * m1.m[1][3] * m1.m[2][0] * m1.m[3][1] + m1.m[0][3] * m1.m[1][1] * m1.m[2][0] * m1.m[3][2] -
		m1.m[0][3] * m1.m[1][2] * m1.m[2][0] * m1.m[3][1] - m1.m[0][2] * m1.m[1][1] * m1.m[2][0] * m1.m[3][3] - m1.m[0][1] * m1.m[1][3] * m1.m[2][0] * m1.m[3][2] -
		m1.m[0][1] * m1.m[1][2] * m1.m[2][3] * m1.m[3][0] - m1.m[0][2] * m1.m[1][3] * m1.m[2][1] * m1.m[3][0] - m1.m[0][3] * m1.m[1][1] * m1.m[2][2] * m1.m[3][0] +
		m1.m[0][3] * m1.m[1][2] * m1.m[2][1] * m1.m[3][0] + m1.m[0][2] * m1.m[1][1] * m1.m[2][3] * m1.m[3][0] + m1.m[0][1] * m1.m[1][3] * m1.m[2][2] * m1.m[3][0];

	Matrix4x4 result;

	result.m[0][0] = 1 / A *
		(m1.m[1][1] * m1.m[2][2] * m1.m[3][3] + m1.m[1][2] * m1.m[2][3] * m1.m[3][1] + m1.m[1][3] * m1.m[2][1] * m1.m[3][2] - m1.m[1][3] * m1.m[2][2] * m1.m[3][1] -
			m1.m[1][2] * m1.m[2][1] * m1.m[3][3] - m1.m[1][1] * m1.m[2][3] * m1.m[3][2]);
	result.m[0][1] = 1 / A *
		(-m1.m[0][1] * m1.m[2][2] * m1.m[3][3] - m1.m[0][2] * m1.m[2][3] * m1.m[3][1] - m1.m[0][3] * m1.m[2][1] * m1.m[3][2] + m1.m[0][3] * m1.m[2][2] * m1.m[3][1] +
			m1.m[0][2] * m1.m[2][1] * m1.m[3][3] + m1.m[0][1] * m1.m[2][3] * m1.m[3][2]);
	result.m[0][2] = 1 / A *
		(m1.m[0][1] * m1.m[1][2] * m1.m[3][3] + m1.m[0][2] * m1.m[1][3] * m1.m[3][1] + m1.m[0][3] * m1.m[1][1] * m1.m[3][2] - m1.m[0][3] * m1.m[1][2] * m1.m[3][1] -
			m1.m[0][2] * m1.m[1][1] * m1.m[3][3] - m1.m[0][1] * m1.m[1][3] * m1.m[3][2]);
	result.m[0][3] = 1 / A *
		(-m1.m[0][1] * m1.m[1][2] * m1.m[2][3] - m1.m[0][2] * m1.m[1][3] * m1.m[2][1] - m1.m[0][3] * m1.m[1][1] * m1.m[2][2] + m1.m[0][3] * m1.m[1][2] * m1.m[2][1] +
			m1.m[0][2] * m1.m[1][1] * m1.m[2][3] + m1.m[0][1] * m1.m[1][3] * m1.m[2][2]);

	result.m[1][0] = 1 / A *
		(-m1.m[1][0] * m1.m[2][2] * m1.m[3][3] - m1.m[1][2] * m1.m[2][3] * m1.m[3][0] - m1.m[1][3] * m1.m[2][0] * m1.m[3][2] + m1.m[1][3] * m1.m[2][2] * m1.m[3][0] +
			m1.m[1][2] * m1.m[2][0] * m1.m[3][3] + m1.m[1][0] * m1.m[2][3] * m1.m[3][2]);
	result.m[1][1] = 1 / A *
		(m1.m[0][0] * m1.m[2][2] * m1.m[3][3] + m1.m[0][2] * m1.m[2][3] * m1.m[3][0] + m1.m[0][3] * m1.m[2][0] * m1.m[3][2] - m1.m[0][3] * m1.m[2][2] * m1.m[3][0] -
			m1.m[0][2] * m1.m[2][0] * m1.m[3][3] - m1.m[0][0] * m1.m[2][3] * m1.m[3][2]);
	result.m[1][2] = 1 / A *
		(-m1.m[0][0] * m1.m[1][2] * m1.m[3][3] - m1.m[0][2] * m1.m[1][3] * m1.m[3][0] - m1.m[0][3] * m1.m[1][0] * m1.m[3][2] + m1.m[0][3] * m1.m[1][2] * m1.m[3][0] +
			m1.m[0][2] * m1.m[1][0] * m1.m[3][3] + m1.m[0][0] * m1.m[1][3] * m1.m[3][2]);
	result.m[1][3] = 1 / A *
		(m1.m[0][0] * m1.m[1][2] * m1.m[2][3] + m1.m[0][2] * m1.m[1][3] * m1.m[2][0] + m1.m[0][3] * m1.m[1][0] * m1.m[2][2] - m1.m[0][3] * m1.m[1][2] * m1.m[2][0] -
			m1.m[0][2] * m1.m[1][0] * m1.m[2][3] - m1.m[0][0] * m1.m[1][3] * m1.m[2][2]);

	result.m[2][0] = 1 / A *
		(m1.m[1][0] * m1.m[2][1] * m1.m[3][3] + m1.m[1][1] * m1.m[2][3] * m1.m[3][0] + m1.m[1][3] * m1.m[2][0] * m1.m[3][1] - m1.m[1][3] * m1.m[2][1] * m1.m[3][0] -
			m1.m[1][1] * m1.m[2][0] * m1.m[3][3] - m1.m[1][0] * m1.m[2][3] * m1.m[3][1]);
	result.m[2][1] = 1 / A *
		(-m1.m[0][0] * m1.m[2][1] * m1.m[3][3] - m1.m[0][1] * m1.m[2][3] * m1.m[3][0] - m1.m[0][3] * m1.m[2][0] * m1.m[3][1] + m1.m[0][3] * m1.m[2][1] * m1.m[3][0] +
			m1.m[0][1] * m1.m[2][0] * m1.m[3][3] + m1.m[0][0] * m1.m[2][3] * m1.m[3][1]);
	result.m[2][2] = 1 / A *
		(m1.m[0][0] * m1.m[1][1] * m1.m[3][3] + m1.m[0][1] * m1.m[1][3] * m1.m[3][0] + m1.m[0][3] * m1.m[1][0] * m1.m[3][1] - m1.m[0][3] * m1.m[1][1] * m1.m[3][0] -
			m1.m[0][1] * m1.m[1][0] * m1.m[3][3] - m1.m[0][0] * m1.m[1][3] * m1.m[3][1]);
	result.m[2][3] = 1 / A *
		(-m1.m[0][0] * m1.m[1][1] * m1.m[2][3] - m1.m[0][1] * m1.m[1][3] * m1.m[2][0] - m1.m[0][3] * m1.m[1][0] * m1.m[2][1] + m1.m[0][3] * m1.m[1][1] * m1.m[2][0] +
			m1.m[0][1] * m1.m[1][0] * m1.m[2][3] + m1.m[0][0] * m1.m[1][3] * m1.m[2][1]);

	result.m[3][0] = 1 / A *
		(-m1.m[1][0] * m1.m[2][1] * m1.m[3][2] - m1.m[1][1] * m1.m[2][2] * m1.m[3][0] - m1.m[1][2] * m1.m[2][0] * m1.m[3][1] + m1.m[1][2] * m1.m[2][1] * m1.m[3][0] +
			m1.m[1][1] * m1.m[2][0] * m1.m[3][2] + m1.m[1][0] * m1.m[2][2] * m1.m[3][1]);
	result.m[3][1] = 1 / A *
		(m1.m[0][0] * m1.m[2][1] * m1.m[3][2] + m1.m[0][1] * m1.m[2][2] * m1.m[3][0] + m1.m[0][2] * m1.m[2][0] * m1.m[3][1] - m1.m[0][2] * m1.m[2][1] * m1.m[3][0] -
			m1.m[0][1] * m1.m[2][0] * m1.m[3][2] - m1.m[0][0] * m1.m[2][2] * m1.m[3][1]);
	result.m[3][2] = 1 / A *
		(-m1.m[0][0] * m1.m[1][1] * m1.m[3][2] - m1.m[0][1] * m1.m[1][2] * m1.m[3][0] - m1.m[0][2] * m1.m[1][0] * m1.m[3][1] + m1.m[0][2] * m1.m[1][1] * m1.m[3][0] +
			m1.m[0][1] * m1.m[1][0] * m1.m[3][2] + m1.m[0][0] * m1.m[1][2] * m1.m[3][1]);
	result.m[3][3] = 1 / A *
		(m1.m[0][0] * m1.m[1][1] * m1.m[2][2] + m1.m[0][1] * m1.m[1][2] * m1.m[2][0] + m1.m[0][2] * m1.m[1][0] * m1.m[2][1] - m1.m[0][2] * m1.m[1][1] * m1.m[2][0] -
			m1.m[0][1] * m1.m[1][0] * m1.m[2][2] - m1.m[0][0] * m1.m[1][2] * m1.m[2][1]);

	return result;
}

Matrix4x4 Transpose(Matrix4x4& m1) {
	Matrix4x4 result{ m1.m[0][0], m1.m[1][0], m1.m[2][0], m1.m[3][0], m1.m[0][1], m1.m[1][1], m1.m[2][1], m1.m[3][1],
					 m1.m[0][2], m1.m[1][2], m1.m[2][2], m1.m[3][2], m1.m[0][3], m1.m[1][3], m1.m[2][3], m1.m[3][3] };
	return result;
}

Matrix4x4 MakeIdentify4x4() {
	Matrix4x4 result{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	return result;
}

Matrix4x4 MakeScaleMatrix(Vector3& scale) {
	Matrix4x4 result{ scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1 };
	return result;
}

Matrix4x4 MakeTranslateMatrix(Vector3& translate) {
	Matrix4x4 result{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, translate.x, translate.y, translate.z, 1 };
	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& Matrix) {
	Vector3 result;

	result.x = vector.x * Matrix.m[0][0] + vector.y * Matrix.m[1][0] + vector.z * Matrix.m[2][0] + 1.0f * Matrix.m[3][0];
	result.y = vector.x * Matrix.m[0][1] + vector.y * Matrix.m[1][1] + vector.z * Matrix.m[2][1] + 1.0f * Matrix.m[3][1];
	result.z = vector.x * Matrix.m[0][2] + vector.y * Matrix.m[1][2] + vector.z * Matrix.m[2][2] + 1.0f * Matrix.m[3][2];
	float w = vector.x * Matrix.m[0][3] + vector.y * Matrix.m[1][3] + vector.z * Matrix.m[2][3] + 1.0f * Matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kColumnHeight + 20, "%6.02f\n", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, "%s", label);
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{ 1, 0, 0, 0, 0, std::cos(radian), std::sin(radian), 0, 0, -std::sin(radian), std::cos(radian), 0, 0, 0, 0, 1 };
	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{ std::cos(radian), 0, -std::sin(radian), 0, 0, 1, 0, 0, std::sin(radian), 0, std::cos(radian), 0, 0, 0, 0, 1 };
	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{ std::cos(radian), std::sin(radian), 0, 0, -std::sin(radian), std::cos(radian), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {

	Matrix4x4 MakeRotateMatrixZ{ std::cos(rot.z), std::sin(rot.z), 0, 0, -std::sin(rot.z), std::cos(rot.z), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

	Matrix4x4 MakeRotateMatrixX{ 1, 0, 0, 0, 0, std::cos(rot.x), std::sin(rot.x), 0, 0, -std::sin(rot.x), std::cos(rot.x), 0, 0, 0, 0, 1 };

	Matrix4x4 MakeRotateMatrixY{ std::cos(rot.y), 0, -std::sin(rot.y), 0, 0, 1, 0, 0, std::sin(rot.y), 0, std::cos(rot.y), 0, 0, 0, 0, 1 };

	Matrix4x4 RotateYZ = Multiply(MakeRotateMatrixY, MakeRotateMatrixZ);

	Matrix4x4 Rotate = Multiply(MakeRotateMatrixX, RotateYZ);

	Matrix4x4 result{
		scale.x * Rotate.m[0][0],
		scale.x * Rotate.m[0][1],
		scale.x * Rotate.m[0][2],
		0,
		scale.y * Rotate.m[1][0],
		scale.y * Rotate.m[1][1],
		scale.y * Rotate.m[1][2],
		0,
		scale.z * Rotate.m[2][0],
		scale.z * Rotate.m[2][1],
		scale.z * Rotate.m[2][2],
		0,
		translate.x,
		translate.y,
		translate.z,
		1

	};

	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{ 1 / aspectRatio * 1 / std::tan(fovY / 2), 0, 0, 0, 0, 1 / std::tan(fovY / 2), 0, 0, 0, 0, farClip / (farClip - nearClip), 1, 0, 0, -nearClip * farClip / (farClip - nearClip), 0 };

	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{ 2 / (right - left),
					 0,
					 0,
					 0,
					 0,
					 2 / (top - bottom),
					 0,
					 0,
					 0,
					 0,
					 1 / (farClip - nearClip),
					 0,
					 (left + right) / (left - right),
					 (top + bottom) / (bottom - top),
					 nearClip / (nearClip - farClip),
					 1 };
	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{ width / 2, 0, 0, 0, 0, -(height / 2), 0, 0, 0, 0, maxDepth - minDepth, 0, left + (width / 2), top + (height / 2), minDepth, 1 };
	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;

	float dotProduct = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	float v2LengthSquared = (v2.x * v2.x) + (v2.y * v2.y) + (v2.z * v2.z);

	if (v2LengthSquared != 0.0f)
	{
		float projectionFactor = dotProduct / v2LengthSquared;

		result.x = projectionFactor * v2.x;
		result.y = projectionFactor * v2.y;
		result.z = projectionFactor * v2.z;
	}
	else {

		result = { 0.0f,0.0f,0.0f };
	}

	return result;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	return Add(segment.origin, project);
}

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(s1.center, s2.center);
	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	float distance = Dot(plane.normal, sphere.center) - plane.distance;

	if (fabsf(distance) - sphere.radius <= 0)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Segment& segment, const Plane& plane)
{
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f)
	{
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;


	Novice::ScreenPrintf(0, 0, "T = %f", t);

	if (t >= 0.0f && t <= 1.0f)
	{

		return true;
	}

	return false;

}

bool IsCollision(const Segment& segment, const Triangle& triangle)
{
	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	Vector3 v01 = //edge from vertex v0 to vertex v1
	{
		v0.x - v1.x,
		v0.y - v1.y,
		v0.z - v1.z
	};
	Vector3 v20 = //edge from vertex v2 to vertex v0
	{
		v2.x - v0.x,
		v2.y - v0.y,
		v2.z - v0.z
	};

	Vector3 v12 = //edge from vertex v1 to vertex v2
	{
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};

	Vector3 normal = Cross(v01, v20); //cross the edges

	Vector3 segmentToPlane = //Vector between the line and edge v0 of the triangle
	{
		v0.x - segment.origin.x,
		v0.y - segment.origin.y,
		v0.z - segment.origin.z
	};

	float denom = Dot(segment.diff, normal); //dot product of the line and the crossed edges

	if (denom == 0.0f) //if the dot product is zero we are not colliding
	{
		return false;
	}

	float t = Dot(segmentToPlane, normal) / denom; //determine intersection point, if we are between 0 and 1 we are colliding

	if (t < 0.0f || t > 1.0f)  //if were not between 0 and 1
	{
		return false;

	}

	Vector3 intersection = //calculate the lines start and end with the intersection points
	{
		{segment.origin.x + t * segment.diff.x},
		{segment.origin.y + t * segment.diff.y},
		{segment.origin.z + t * segment.diff.z}
	};

	Vector3 v0p =
	{
		intersection.x - v0.x,
		intersection.y - v0.y,
		intersection.z - v0.z
	};

	Vector3 v1p =
	{
		intersection.x - v1.x,
		intersection.y - v1.y,
		intersection.z - v1.z
	};

	Vector3 v2p =
	{
		intersection.x - v2.x,
		intersection.y - v2.y,
		intersection.z - v2.z
	};


	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f)
	{
		return true;
	}
	return false;

}

bool IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	//aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);

	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z))
	{
		return true;
	}

	return false;
}

bool IsCollision(const AABB& aabb, const Sphere& sphere)
{
	Vector3 closestPoint =
	{
		std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
		std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
		std::clamp(sphere.center.z, aabb.min.z, aabb.max.z)
	};

	float distance = Length(closestPoint, sphere.center);

	if (distance <= sphere.radius)
	{
		return true;
	}

	return false;
}

bool IsCollision(const AABB& aabb, const Segment& segment)
{

	float txMin, txMax;
	float tyMin, tyMax;
	float tzMin, tzMax;

	if (segment.diff.x != 0.0f)
	{
		txMin = (aabb.min.x - segment.origin.x) / segment.diff.x;
		txMax = (aabb.max.x - segment.origin.x) / segment.diff.x;
	}
	else
	{
		txMin = -INFINITY;
		txMax = INFINITY;
	}

	if (segment.diff.y != 0.0f)
	{
		tyMin = (aabb.min.y - segment.origin.y) / segment.diff.y;
		tyMax = (aabb.max.y - segment.origin.y) / segment.diff.y;
	}
	else
	{
		tyMin = -INFINITY;
		tyMax = INFINITY;
	}

	if (segment.diff.z != 0.0f)
	{
		tzMin = (aabb.min.z - segment.origin.z) / segment.diff.z;
		tzMax = (aabb.max.z - segment.origin.z) / segment.diff.z;
	}
	else
	{
		tzMin = -INFINITY;
		tzMax = INFINITY;
	}

	float tNearX = min(txMin, txMax);
	float tNearY = min(tyMin, tyMax);
	float tNearZ = min(tzMin, tzMax);

	float tFarX = max(txMin, txMax);
	float tFarY = max(tyMin, tyMax);
	float tFarZ = max(tzMin, tzMax);

	float tmin = max(max(tNearX, tNearY), tNearZ);
	float tmax = min(min(tFarX, tFarY), tFarZ);

	if (tmin <= tmax && tmax >= 0 && tmin <= 1)
	{
		return true;
	}

	return false;


}

float Length(const Vector3& point1, const Vector3& point2)
{
	Vector3 difference;
	difference.x = point1.x - point2.x;
	difference.y = point1.y - point2.y;
	difference.z = point1.z - point2.z;

	return sqrtf(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);
}

Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f)
	{
		return { -vector.y, vector.x, 0.0f };
	}
	return { 0.0f, -vector.z, vector.y };
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color, uint32_t color2, uint32_t color3, uint32_t color4)
{

	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++)
	{
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewPortMatrix);
	}
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);//white
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color2);//red
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color3);//blue
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color4);//green
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color)
{
	Vector3 screenVertices[3];
	for (uint32_t i = 0; i < 3; i++)
	{
		Vector3 ndcVertex = Transform(triangle.vertices[i], viewProjectionMatrix);
		screenVertices[i] = Transform(ndcVertex, viewPortMatrix);
	}

	Novice::DrawTriangle((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[2].x, (int)screenVertices[2].y, color, kFillModeWireFrame);
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color)
{
	Vector3 corners[8] = {
		{aabb.min.x, aabb.min.y, aabb.min.z},
		{aabb.max.x, aabb.min.y, aabb.min.z},
		{aabb.min.x, aabb.max.y, aabb.min.z},
		{aabb.max.x, aabb.max.y, aabb.min.z},
		{aabb.min.x, aabb.min.y, aabb.max.z},
		{aabb.max.x, aabb.min.y, aabb.max.z},
		{aabb.min.x, aabb.max.y, aabb.max.z},
		{aabb.max.x, aabb.max.y, aabb.max.z}
	};

	Vector3 screenCorners[8];
	for (int i = 0; i < 8; i++)
	{
		Vector3 temp = Transform(corners[i], viewProjectionMatrix);
		screenCorners[i] = Transform(temp, viewPortMatrix);
	}

	// Draw the bottom face (min z)
	Novice::DrawLine((int)screenCorners[0].x, (int)screenCorners[0].y, (int)screenCorners[1].x, (int)screenCorners[1].y, color);
	Novice::DrawLine((int)screenCorners[1].x, (int)screenCorners[1].y, (int)screenCorners[3].x, (int)screenCorners[3].y, color);
	Novice::DrawLine((int)screenCorners[3].x, (int)screenCorners[3].y, (int)screenCorners[2].x, (int)screenCorners[2].y, color);
	Novice::DrawLine((int)screenCorners[2].x, (int)screenCorners[2].y, (int)screenCorners[0].x, (int)screenCorners[0].y, color);

	// Draw the top face (max z)
	Novice::DrawLine((int)screenCorners[4].x, (int)screenCorners[4].y, (int)screenCorners[5].x, (int)screenCorners[5].y, color);
	Novice::DrawLine((int)screenCorners[5].x, (int)screenCorners[5].y, (int)screenCorners[7].x, (int)screenCorners[7].y, color);
	Novice::DrawLine((int)screenCorners[7].x, (int)screenCorners[7].y, (int)screenCorners[6].x, (int)screenCorners[6].y, color);
	Novice::DrawLine((int)screenCorners[6].x, (int)screenCorners[6].y, (int)screenCorners[4].x, (int)screenCorners[4].y, color);

	// Draw the vertical edges connecting top and bottom faces
	Novice::DrawLine((int)screenCorners[0].x, (int)screenCorners[0].y, (int)screenCorners[4].x, (int)screenCorners[4].y, color);
	Novice::DrawLine((int)screenCorners[1].x, (int)screenCorners[1].y, (int)screenCorners[5].x, (int)screenCorners[5].y, color);
	Novice::DrawLine((int)screenCorners[2].x, (int)screenCorners[2].y, (int)screenCorners[6].x, (int)screenCorners[6].y, color);
	Novice::DrawLine((int)screenCorners[3].x, (int)screenCorners[3].y, (int)screenCorners[7].x, (int)screenCorners[7].y, color);

	
}

Vector3 Normalize(Vector3 v)
{
	float normalize(v.x * v.x + v.y * v.y + v.z * v.z);

	if (normalize != 0)
	{
		return Vector3(v.x / normalize, v.y / normalize, v.z / normalize);
	}
	return v;
}

float Dot(Vector3 v1, Vector3 v2)
{
	float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	Vector3 p{};

	p.x = t * v1.x + (1.0f - t) * v2.x;
	p.y = t * v1.y + (1.0f - t) * v2.y;
	p.z = t * v1.z + (1.0f - t) * v2.z;

	return p;
}

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t)
{
	Vector3 p0p1 = Lerp(p0, p1, t);
	Vector3 p1p2 = Lerp(p1, p2, t);
	Vector3 p = Lerp(p0p1, p1p2, t);

	return p;
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color)
{
	int points = 32;
	float t0;
	float t1;
	Vector3 bezier0{};
	Vector3 bezier1{};


	Sphere sphere1
	{
		controlPoint0,
		0.01f,
		(int)BLACK

	};

	Sphere sphere2
	{
		controlPoint1,
		0.01f,
		(int)BLACK

	};

	Sphere sphere3
	{
		controlPoint2,
		0.01f,
		(int)BLACK

	};


	for (int i = 0; i < points; i++)
	{
		t0 = i / float(points);
		t1 = (i + 1) / float(points);

		bezier0 = Bezier(controlPoint0, controlPoint1, controlPoint2, t0);
		bezier1 = Bezier(controlPoint0, controlPoint1, controlPoint2, t1);

		Vector3 screenStart = Transform(Transform(bezier0, viewProjectionMatrix), viewPortMatrix);
		Vector3 screenEnd = Transform(Transform(bezier1, viewProjectionMatrix), viewPortMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);




	}

	DrawSphere(sphere1, viewProjectionMatrix, viewPortMatrix, sphere1.color);
	DrawSphere(sphere2, viewProjectionMatrix, viewPortMatrix, sphere2.color);
	DrawSphere(sphere3, viewProjectionMatrix, viewPortMatrix, sphere3.color);

}

Vector3 CatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	Vector3 result = {
		0.5f * ((-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3 +
				(2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2 +
				(-p0.x + p2.x) * t +
				2.0f * p1.x),
		0.5f * ((-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3 +
				(2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2 +
				(-p0.y + p2.y) * t +
				2.0f * p1.y),
		0.5f * ((-p0.z + 3.0f * p1.z - 3.0f * p2.z + p3.z) * t3 +
				(2.0f * p0.z - 5.0f * p1.z + 4.0f * p2.z - p3.z) * t2 +
				(-p0.z + p2.z) * t +
				2.0f * p1.z)
	};

	return result;
}

void DrawCatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3, Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewPortMatrix, uint32_t color)
{
	int points = 32;
	Vector3 spline0{}, spline1{};

	Sphere sphere1
	{
		controlPoint0,
		0.01f,
		(int)BLACK
	};

	Sphere sphere2
	{
		controlPoint1,
		0.01f,
		(int)BLACK
	};

	Sphere sphere3
	{
		controlPoint2,
		0.01f,
		(int)BLACK
	};

	Sphere sphere4
	{
		controlPoint3,
		0.01f,
		(int)BLACK
	};

	for (int i = 0; i < points; i++)
	{
		float t0, t1;
		t0 = i / float(points); // Adjusted to cover the range [0, 1]
		t1 = (i + 1) / float(points); // Adjusted to cover the range [0, 1]

		spline0 = CatmullRom(controlPoint0, controlPoint0, controlPoint1, controlPoint2, t0);
		spline1 = CatmullRom(controlPoint0, controlPoint0, controlPoint1, controlPoint2, t1);

		Vector3 screenStart = Transform(Transform(spline0, viewProjectionMatrix), viewPortMatrix);
		Vector3 screenEnd = Transform(Transform(spline1, viewProjectionMatrix), viewPortMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);
	}

	for (int i = 0; i < points; i++)
	{
		float t0, t1;
		t0 = i / float(points); // Adjusted to cover the range [0, 1]
		t1 = (i + 1) / float(points); // Adjusted to cover the range [0, 1]

		spline0 = CatmullRom(controlPoint0, controlPoint1, controlPoint2, controlPoint3, t0);
		spline1 = CatmullRom(controlPoint0, controlPoint1, controlPoint2, controlPoint3, t1);

		Vector3 screenStart = Transform(Transform(spline0, viewProjectionMatrix), viewPortMatrix);
		Vector3 screenEnd = Transform(Transform(spline1, viewProjectionMatrix), viewPortMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);
	}

	for (int i = 0; i < points; i++)
	{
		float t0, t1;
		t0 = i / float(points); // Adjusted to cover the range [0, 1]
		t1 = (i + 1) / float(points); // Adjusted to cover the range [0, 1]

		spline0 = CatmullRom(controlPoint1, controlPoint2, controlPoint3, controlPoint3, t0);
		spline1 = CatmullRom(controlPoint1, controlPoint2, controlPoint3, controlPoint3, t1);

		Vector3 screenStart = Transform(Transform(spline0, viewProjectionMatrix), viewPortMatrix);
		Vector3 screenEnd = Transform(Transform(spline1, viewProjectionMatrix), viewPortMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);
	}

	DrawSphere(sphere1, viewProjectionMatrix, viewPortMatrix, sphere1.color);
	DrawSphere(sphere2, viewProjectionMatrix, viewPortMatrix, sphere2.color);
	DrawSphere(sphere3, viewProjectionMatrix, viewPortMatrix, sphere3.color);
	DrawSphere(sphere4, viewProjectionMatrix, viewPortMatrix, sphere4.color);
}

void MakeSpring(Spring& spring, Ball& ball)
{
	float deltaTime = 1.0f / 60.0f;
	Vector3 diff = Subtract(ball.position , spring.anchor);
	float length = Length(ball.position, spring.anchor);
	if (length != 0.0f)
	{
		Vector3 direction = Normalize(diff);
		Vector3 restPosition;
		restPosition.x = spring.anchor.x + direction.x * spring.naturalLength;
		restPosition.y = spring.anchor.y + direction.y * spring.naturalLength;
		restPosition.z = spring.anchor.z + direction.z * spring.naturalLength;

		Vector3 displacement;
		displacement.x = length * (ball.position.x - restPosition.x);
		displacement.y = length * (ball.position.y - restPosition.y);
		displacement.z = length * (ball.position.z - restPosition.z);

		Vector3 restoringForce;
		restoringForce.x = -spring.stiffness * displacement.x;
		restoringForce.y = -spring.stiffness * displacement.y;
		restoringForce.z = -spring.stiffness * displacement.z;

		Vector3 dampingForce;
		dampingForce.x = -spring.dampingCoefficient * ball.velocity.x;
		dampingForce.y = -spring.dampingCoefficient * ball.velocity.y;
		dampingForce.z = -spring.dampingCoefficient * ball.velocity.z;


		Vector3 force =  Add(restoringForce , dampingForce);

		ball.acceleration = divide(force , ball.mass);


	}

	ball.velocity = Add(ball.velocity,Multiply(deltaTime , ball.acceleration));
	ball.position = Add(ball.position, Multiply(deltaTime, ball.velocity));

}

Vector3 divide(const Vector3& v1, float v2) {
	if (v2 != 0) {
		return Vector3(v1.x / v2, v1.y / v2, v1.z / v2);
	}
	else {
		return Vector3(0, 0, 0); // ゼロ除算の場合、(0, 0, 0)ベクトルを返す
	}
}
