#include <iostream>
#include <raylib.h>
using namespace std;
enum GameState
{
	MENU = 0,
	INGAME = 1,
	GAMEOVER = 2
};
int player1Score;
int player2Score;
int relayCount;
bool fastBall = false;
bool relayMode = false;
GameState state = MENU;
class Ball
{
public:
	float x, y;
	int speed_x, speed_y;
	int radius;
	void Draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}
	void Update()
	{
		x += speed_x;
		y += speed_y;
		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y = -speed_y;
		}

		if (x + radius >= GetScreenWidth())
		{
			speed_x = (-speed_x);
			player2Score++;
			ResetBall();
		}

		if (x - radius <= 0)
		{
			speed_x = (-speed_x);
			player1Score++;
			ResetBall();
		}
	}
	void ResetBall()
	{
		if (player1Score >= 5 || player2Score >= 5 || relayMode)
		{
			state = GAMEOVER;
		}
		x = speed_x > 0 ? GetScreenWidth() / 2 - 400 : GetScreenWidth() / 2 + 400;
		y = GetScreenHeight() / 2;
		int speed_choices[2] = {-1, 1};
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}
};
class Player
{
public:
	float x, y;
	int speed;
	float width, height;
	KeyboardKey up, down;
	void Draw()
	{
		DrawRectangle(x, y, width, height, WHITE);
	}
	void Update()
	{
		if (IsKeyDown(up) && !(y <= 0))
		{
			y -= speed;
		}
		if (IsKeyDown(down) && !(y + height >= GetScreenHeight()))
		{
			y += speed;
		}
	}
};
Ball ball;
Player player1;
Player player2;
const int screenWidth = 1280;
const int screenHeight = 800;
int framesElapsedInGame;
int lastCollisionTime;
void setClassProperties(bool fastBall)
{
	relayCount = 0;
	framesElapsedInGame = 0;
	lastCollisionTime = 0;
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
int main()
{
	InitWindow(screenWidth, screenHeight, "Pong");
	SetExitKey(KEY_DELETE);
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		if (state == MENU)
		{
			if (IsKeyPressed(KEY_F))
			{
				fastBall = !fastBall;
			}
			if (IsKeyPressed(KEY_R))
			{
				relayMode = !relayMode;
			}
			if (IsKeyPressed(KEY_ENTER))
			{
				setClassProperties(fastBall);
				state = INGAME;
			}

			BeginDrawing();
			ClearBackground(BLACK);
			DrawText("Pong", 40, 40, 160, WHITE);
			DrawText("A simple raylib game by omger.", 40, 240, 40, WHITE);
			DrawText("Player 1: Use up and down arrow keys.", 40, 320, 40, WHITE);
			DrawText("Player 2: Use A and D keys.", 40, 360, 40, WHITE);
			DrawText("First to 5 wins!", 40, 400, 40, WHITE);
			DrawText("Press ENTER to start", 40, 480, 80, WHITE);
			DrawText(TextFormat("Fast ball, press F to toggle: %s", fastBall ? "ON" : "OFF"), 40, 580, 40, WHITE);
			DrawText(TextFormat("Relay mode, press R to toggle: %s", relayMode ? "ON" : "OFF"), 40, 620, 40, WHITE);
			DrawText("Release version 1.0", 40, screenHeight - 120, 40, WHITE);
			DrawText("Press Delete to exit", 40, screenHeight - 80, 40, WHITE);
			EndDrawing();
		}
		else if (state == INGAME)
		{
			BeginDrawing();
			ClearBackground(BLACK);

			if (IsKeyPressed(KEY_ESCAPE))
			{
				state = MENU;
				continue;
			}

			ball.Update();
			ball.Draw();
			player1.Update();
			if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player1.x, player1.y, player1.width, player1.height}))
			{
				ball.speed_x = -(ball.speed_x);
				if ((framesElapsedInGame - lastCollisionTime) < 30)
				{
					lastCollisionTime = framesElapsedInGame;
				}
				else
				{
					lastCollisionTime = framesElapsedInGame;
					relayCount++;
				}
			}
			player1.Draw();
			player2.Update();
			if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height}))
			{
				ball.speed_x = -(ball.speed_x);
				if ((framesElapsedInGame - lastCollisionTime) < 30)
				{
					lastCollisionTime = framesElapsedInGame;
				}
				else
				{
					lastCollisionTime = framesElapsedInGame;
					relayCount++;
				}
			}
			player2.Draw();
			DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
			if (relayMode)
			{
				DrawText(TextFormat("%i", relayCount), screenWidth / 2 + 20, 20, 80, WHITE);
			}
			else
			{
				DrawText(TextFormat("%i", player2Score), screenWidth / 2 - 60, 20, 80, WHITE);
				DrawText(TextFormat("%i", player1Score), screenWidth / 2 + 20, 20, 80, WHITE);
			}
			if (framesElapsedInGame < 120)
			{
				DrawText("Player 1", screenWidth / 2 + 20, screenHeight / 2 - 20, 40, WHITE);
				DrawText("Player 2", screenWidth / 2 - 200, screenHeight / 2 - 20, 40, WHITE);
			}
			EndDrawing();
			framesElapsedInGame += 1;
		}
		else if (state == GAMEOVER)
		{
			BeginDrawing();
			ClearBackground(BLACK);
			if (player1Score >= 5 && !relayMode)
			{
				DrawText("Player 1 Wins!", 40, 40, 80, WHITE);
			}
			else if (player2Score >= 5 && !relayMode)
			{
				DrawText("Player 2 Wins!", 40, 40, 80, WHITE);
			}
			else if (relayMode)
			{
				DrawText(TextFormat("Total Score: %i", relayCount), 40, 40, 80, WHITE);
			}
			DrawText("Press ENTER to play again.", 40, 160, 40, WHITE);
			if (IsKeyPressed(KEY_ENTER))
			{
				setClassProperties(fastBall);
				player1Score = 0;
				player2Score = 0;
				relayCount = 0;
				state = INGAME;
			}
			else if (IsKeyPressed(KEY_ESCAPE))
			{
				setClassProperties(fastBall);
				player1Score = 0;
				player2Score = 0;
				relayCount = 0;
				state = MENU;
			}
			EndDrawing();
		}
	}

	return 0;
}