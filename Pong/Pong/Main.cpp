/*
		~~ PONG GAME ~~

	Windows CMD pong game also includes ball gravity impact mod.
*/

#include <Windows.h> // for GetAsyncKeyState() and SetConsoleCursorPosition() and GetStdHandle()
#include <iostream>  // for printf_s() and std::cout
#include <chrono>    
#include <thread>	 // for this_thread::sleep_for();
#include <conio.h>   // for _getch()

#include "Random.h"
#include "Vector2.h"
#include "Scene.h"
#include "Ball.h"
#include "Paddle.h"

int main()
{
	// ==============================================================================
	// Start Menu

	int maxScore{ 15 };

	std::cout << "\n\t\t\tPONG GAME\n\n";
	std::cout << "\tThe first to reach " << maxScore << " points wins!\n\n";
	std::cout << "\tleft control: W S\tright control: " << (char)30 << ' ' << (char)31 << "\n\n";
	std::cout << "\tPress ENTER to start\n";
	std::cout << "\t[To play with ball gravity impact mod press 'G']\n";

	// ==============================================================================
	// ~~START~~

	// Note: (0, 0) coordinates is top left corner in our game scene.

	Scene::set(60, 25); // Set scene width and height at start.

	bool gravityImpact{ false };
	switch (_getch())
	{
	case 'g':
	case 'G':
		gravityImpact = true;
	}

	std::system("cls"); // We need to clear the console before proceeding.

	int leftScore{ 0 };
	int rightScore{ 0 };
	float paddleSpeed{ 20.0f };
	Vector2 gravityVector{ 0.0f, -20.0f };
	Vector2 initialVelocity{ Vector2::getUnitVector(std::_Pi / 8.0f) * 35.0f }; // ball initial velocity

	// Creating ball object
	bool leftOrRight{ Random::getBool() }; // this determines whether ball throws left or right at start.
	Ball ball
	{
		(leftOrRight ? Ball::leftStartPos() : Ball::rightStartPos()), // pick a random position at start
		initialVelocity * (leftOrRight ? 1 : -1), // pick a random direction at start
		false // initially ball.enable = false
	};

	Paddle leftPaddle{ Vector2{6.0f, Scene::getCenter().y + 1.0f} };
	Paddle rightPaddle{ Vector2{Scene::getBounds().x - 6.0f, Scene::getCenter().y + 1.0f} };

	float timer{ 0.0f };

	// ==============================================================================
	// ~~GAME LOOP~~

	auto tp1{ std::chrono::system_clock::now() };
	while (true)
	{
		auto tp2{ std::chrono::system_clock::now() };

		// elapsedTime is difference between the prevous frame that was drawn and the current frame
		float elapsedTime{ std::chrono::duration<float>(tp2 - tp1).count() };
		tp1 = tp2;

		// This function sets console cursor position to top left corner.
		// It is faster than clearing whole console, we should avoid system(cls)
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

		// ==============================================================================
		// ~~UPDATE~~

		// ==============================================================
		// Handle paddle movement

		if (GetAsyncKeyState((unsigned short)'W'))
		{
			if (leftPaddle.topPos().y < -2.0f)
				leftPaddle.moveUp(paddleSpeed * elapsedTime);
		}

		if (GetAsyncKeyState((unsigned short)'S'))
		{
			if (leftPaddle.downPos().y > -Scene::getHeight() + 2.0f)
				leftPaddle.moveDown(paddleSpeed * elapsedTime);
		}

		if (GetAsyncKeyState((unsigned short)38)) // up arrow key
		{
			if (rightPaddle.topPos().y < -2.0f)
				rightPaddle.moveUp(paddleSpeed * elapsedTime);
		}

		if (GetAsyncKeyState((unsigned short)40)) // down arraw key
		{
			if (rightPaddle.downPos().y > -Scene::getHeight() + 2.0f)
				rightPaddle.moveDown(paddleSpeed * elapsedTime);
		}

		// ==============================================================
		// Handle ball movement

		ball.move(elapsedTime);

		if (gravityImpact)
			ball.gravityImpact(gravityVector, elapsedTime);

		// ==============================================================
		// Handle ball bouncing

		Scene::Object obj{ Scene::getObjAtPoint(ball.position) };

		if (obj == Scene::Object::thblock || obj == Scene::Object::bhblock)
			ball.bounce(Ball::upDown);
		else if (obj == Scene::Object::fblock)
			ball.bounce(Ball::leftRight);

		// ==============================================================
		// Handle score increment and ball position adjustment

		if (ball.position.x < leftPaddle.topPos().x - 2.0f)
		{
			ball.active = false;
			ball.position = Ball::rightStartPos();
			ball.velocity = -initialVelocity;
			++rightScore;
		}

		if (ball.position.x > rightPaddle.topPos().x + 2.0f)
		{
			ball.active = false;
			ball.position = Ball::leftStartPos();
			ball.velocity = initialVelocity;
			++leftScore;
		}

		// ==============================================================
		// Ball waits for 2 seconds before throwing via this code

		if (!ball.active && timer <= 2.0f)
		{
			timer += elapsedTime;
		}
		else if (!ball.active)
		{
			ball.velocity.y *= Random::getBool() ? 1 : -1;
			ball.active = true;
			timer = 0.0f;
		}

		// ==============================================================
		// Draw

		Scene::draw();
		ball.draw();
		leftPaddle.draw();
		rightPaddle.draw();

		// ==============================================================
		// Display

		Scene::display();
		printf_s("LEFT: %i                                            RIGHT: %i", leftScore, rightScore);

		// ==============================================================
		// Score checking

		if (leftScore >= maxScore || rightScore >= maxScore) break;

		// ==============================================================================
	}

	if (leftScore > rightScore)
		std::cout << "\n\n\t\t    LEFT PLAYER WON!\n";
	else
		std::cout << "\n\n\t\t    RIGHT PLAYER WON!\n";

	std::cin.get();

	return 0;
}