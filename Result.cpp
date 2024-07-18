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



}

void Result::Update()
{
	
	worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f,1.0f }, { 0,0,0 }, { 0,0,0 });
	cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.f);
	viewMatrixProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
	worldViewProjectionMatrix = Multiply(worldMatrix, viewMatrixProjectionMatrix);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);






	if (start)
	{
		MakeSpring(spring, ball);
		/*float deltaTime = 1.0f / 60.0f;
		Vector3 diff = Subtract(ball.position, spring.anchor);
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


			Vector3 force = Add(restoringForce , dampingForce);

			ball.acceleration = divide(force, ball.mass);





		}

		ball.velocity = Add(ball.velocity, Multiply(deltaTime, ball.acceleration));
		ball.position = Add(ball.position, Multiply(deltaTime, ball.velocity));*/
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
