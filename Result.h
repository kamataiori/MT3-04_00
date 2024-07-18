#pragma once
#include "MathFunc.h"


class Result
{
public:

	Vector3 cameraRotate = {};
	Vector3 cameraTranslate;
	Vector3 cameraPosition;

	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	/*	Matrix4x4 shoulderMatrix = ->MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 elbowMatrix = ->Multiply(shoulderMatrix, ->MakeAffineMatrix(scales[1], rotates[1], translates[1]));
		Matrix4x4 handMatrix = ->Multiply(elbowMatrix, ->MakeAffineMatrix(scales[2], rotates[2], translates[2]));*/
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 viewMatrixProjectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;
	//Vector3 start = ->Transform(->Transform(segment.origin, viewMatrixProjectionMatrix), viewportMatrix);
	//Vector3 end =->Transform(->Transform(->Add(segment.origin, segment.diff), viewMatrixProjectionMatrix), viewportMatrix);


	Spring spring{};

	Ball ball{};

	bool start = false;

	

	Vector3 screenBall = {};
	Vector3 screenSpring = {};



	void Initialize();


	void Update();


	void Draw();
};

