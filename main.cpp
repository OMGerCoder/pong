#include <iostream>
#include <raylib.h>
using namespace std;
int player1Score;
int player2Score;
int relayCount;
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
		x = speed_x > 0 ? GetScreenWidth() / 2 - 400 : GetScreenWidth() / 2 + 400;
		y = GetScreenHeight() / 2;
		int speed_choices[2] = { -1,1 };
		speed_y *= speed_choices[GetRandomValue(0, 1)];
		relayCount = 0;
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
bool isInMenu = true;
bool fastBall = false;
bool relayMode = false;
const int screenWidth = 1280;
const int screenHeight = 800;
void setClassProperties() {
	ball.radius = 20;
	ball.x = screenWidth / 2;
	ball.y = screenHeight / 2;
	ball.speed_x = fastBall ? 15 : 7;
	ball.speed_y = fastBall ? 15 : 7;
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
}
int main() {
	InitWindow(screenWidth, screenHeight, "Pong");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	setClassProperties();
	while (!WindowShouldClose()) {
		if(isInMenu) {
			if(IsKeyPressed(KEY_F)) {
				fastBall = !fastBall;
				if(fastBall) {
					ball.speed_x = 15;
					ball.speed_y = 15;
				} else {
					ball.speed_x = 7;
					ball.speed_y = 7;
				}
			}
			if(IsKeyPressed(KEY_R)) {
				relayMode = !relayMode;
			}
			if(IsKeyPressed(KEY_ENTER)) {
				isInMenu = false;
			}
			
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText("Pong", 40, 40, 160, WHITE);
			DrawText("A simple raylib game by omger.", 40, 240, 40, WHITE);
			DrawText("Player 1: Use up and down arrow keys.", 40, 320, 40, WHITE);
			DrawText("Player 2: Use A and D keys.", 40, 360, 40, WHITE);
			DrawText("Press ENTER to start", 40, 440, 80, WHITE);
			DrawText(TextFormat("Fast ball, press F to toggle: %s", fastBall ? "ON" : "OFF"), 40, 540, 40, WHITE);
			DrawText(TextFormat("Relay mode, press R to toggle: %s", relayMode ? "ON" : "OFF"), 40, 580, 40, WHITE);
			EndDrawing();
		} else {
			BeginDrawing();
			ClearBackground(BLACK);
			
			if(IsKeyPressed(KEY_ESCAPE)) {
				isInMenu = true;
				setClassProperties();
				continue;
			}
			
			ball.Update();
			ball.Draw();
			player1.Update();
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player1.x, player1.y, player1.width, player1.height })) {
				ball.speed_x = -(ball.speed_x);
				relayCount++;
			}
			player1.Draw();
			player2.Update();
			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player2.x, player2.y, player2.width, player2.height })) {
				ball.speed_x = -(ball.speed_x);
				relayCount++;
			}
			player2.Draw();
			DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
			if(relayMode) {
				DrawText(TextFormat("%i", relayCount), screenWidth / 2 + 20, 20, 80, WHITE);
			} else {
				DrawText(TextFormat("%i", player2Score), screenWidth / 2 - 60, 20, 80, WHITE);
				DrawText(TextFormat("%i", player1Score), screenWidth / 2 + 20, 20, 80, WHITE);
			}
			EndDrawing();
		}
	}

	return 0;
}