#include <iostream>
#include <raylib.h>
using namespace std;
int player1Score;
int player2Score;
class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;
	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}
	void Update() {
		x += speed_x;
		y += speed_y;
		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y = -speed_y;
		}

		if (x + radius >= GetScreenWidth()) {
			speed_x = (-speed_x);
			player2Score++;
			ResetBall();
		}
		
		if (x - radius <= 0) {
			speed_x = (-speed_x);
			player1Score++;
			ResetBall();
		}
	}
	void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		int speed_choices[2] = { -1,1 };
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}
};
class Player {
public:
	float x, y;
	int speed;
	float width, height;
	KeyboardKey up, down;
	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}
	void Update() {
		if (IsKeyDown(up) && !(y <= 0)) {
			y -= speed;
		}
		if (IsKeyDown(down) && !(y + height >= GetScreenHeight())) {
			y += speed;
		}
	}
};
Ball ball;
Player player1;
Player player2;
int main() {

	const int screenWidth = 1280;
	const int screenHeight = 800;
#pragma region long ass class property definition
	ball.radius = 20;
	ball.x = screenWidth / 2;
	ball.y = screenHeight / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;
	player1.width = 25;
	player2.width = 25;
	player1.height = 120;
	player2.height = 120;
	player1.x = screenWidth - player1.width - 10;
	player2.x = 10;
	player1.y = screenHeight / 2 - player1.height / 2;
	player2.y = screenHeight / 2 - player2.height / 2;
	player1.speed = 15;
	player2.speed = 15;
	player1.up = KEY_UP;
	player1.down = KEY_DOWN;
	player2.up = KEY_W;
	player2.down = KEY_S;
#pragma endregion
	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		ball.Update();
		ball.Draw();
		player1.Update();
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player1.x, player1.y, player1.width, player1.height })) {
			ball.speed_x = -(ball.speed_x);
		}
		player1.Draw();
		player2.Update();
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player2.x, player2.y, player2.width, player2.height })) {
			ball.speed_x = -(ball.speed_x);
		}
		player2.Draw();
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		DrawText(TextFormat("%i", player2Score), screenWidth / 2 - 60, 20, 80, WHITE);
		DrawText(TextFormat("%i", player1Score), screenWidth / 2 + 20, 20, 80, WHITE);
		EndDrawing();
	}

	return 0;
}