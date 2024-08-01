#include "Result.h"

void Result::Initialize()
{
	cameraRotate = { 0.26f, 0.0f, 0.0f };
	cameraTranslate = { 0.0f,1.9f, -6.49f };
	cameraPosition = { 0,0,-10.0f };


	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;


	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;


	Vector3 translates[3] = 
	{
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f}
	};

	Vector3 rotates[3] =
	{
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f}
	};

	Vector3 scales[3] =
	{
		{1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 1.0f}
	};




	worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f,1.0f }, { 0,0,0 }, { 0,0,0 });
	cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.f);
	viewMatrixProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	worldViewProjectionMatrix = Multiply(worldMatrix, viewMatrixProjectionMatrix);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);



	screenBall = Transform(Transform(ball.position, viewMatrixProjectionMatrix), viewportMatrix);
	screenSpring = Transform(Transform(spring.anchor, viewMatrixProjectionMatrix), viewportMatrix);



}

void Result::Update()
{
	
	worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f,1.0f }, { 0,0,0 }, { 0,0,0 });
	cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	/*	Matrix4x4 shoulderMatrix = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 elbowMatrix = Multiply(shoulderMatrix, MakeAffineMatrix(scales[1], rotates[1], translates[1]));
		Matrix4x4 handMatrix = Multiply(elbowMatrix, MakeAffineMatrix(scales[2], rotates[2], translates[2]));*/
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.f);
	viewMatrixProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	worldViewProjectionMatrix = Multiply(worldMatrix, viewMatrixProjectionMatrix);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	//Vector3 start = Transform(Transform(segment.origin, viewMatrixProjectionMatrix), viewportMatrix);
	//Vector3 end =Transform(Transform(Add(segment.origin, segment.diff), viewMatrixProjectionMatrix), viewportMatrix);
	if (start)
	{
		MakeSpring(spring, ball);
	}
	
	
}

void Result::Draw()
{
	DrawGrid(viewMatrixProjectionMatrix, viewportMatrix);
	screenBall = Transform(Transform(ball.position, viewMatrixProjectionMatrix), viewportMatrix);
	screenSpring = Transform(Transform(spring.anchor, viewMatrixProjectionMatrix), viewportMatrix);
	Transform(spring.anchor, worldViewProjectionMatrix);
	DrawSphere({ ball.position, ball.radius }, viewMatrixProjectionMatrix, viewportMatrix, ball.color);
	Novice::DrawLine((int)screenBall.x, (int)screenBall.y, (int)screenSpring.x, (int)screenSpring.y, WHITE);


	ImGui::Begin("Window");
	//ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
	if (ImGui::Button("Start"))
	{
		start = true;
	}
	ImGui::End();
}
