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


	ball.position = { 1.2f, 0.0f, 0.f };
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



}

void Result::Update()
{
	
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
	if (ImGui::Button("Start"))
	{
		start = true;
	}
	ImGui::End();
}
