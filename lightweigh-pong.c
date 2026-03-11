#include <stdio.h>
#include <raylib.h>
struct Ball {
	float x, y, speedx, speedy, radius;
	Color clr; };
struct Paddle {
	float x, y, width, height;
	Color clr; };
int main(void) {
	InitWindow(800, 500, "Lightweigh Pong");
	SetTargetFPS(30);
	struct Ball b={ 400,250,200,-200,20,RED };
	struct Paddle p1={ 10,170,25,80,RED };
	struct Paddle pa={ 765,170,25,80,RED };
	while(!WindowShouldClose()) {
	BeginDrawing();
	float delta = GetFrameTime();
	if(CheckCollisionCircleRec((Vector2){b.x,b.y},b.radius,(Rectangle){p1.x,p1.y,p1.width,p1.height})) b.speedx *= -1;
	if(CheckCollisionCircleRec((Vector2){b.x,b.y},b.radius,(Rectangle){pa.x,pa.y,pa.width,pa.height})) b.speedx *= -1;
	b.x += b.speedx * delta;
	b.y += b.speedy * delta;
	if(p1.y >= GetScreenHeight()-p1.height) p1.y = GetScreenHeight()-p1.height;
	if(pa.y >= GetScreenHeight()-pa.height) pa.y = GetScreenHeight()-pa.height;
	if(p1.y <= 0) p1.y = 0;
	if(pa.y <= 0) pa.y = 0;
	if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) p1.y += 200 * delta;
	if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) p1.y -= 200 * delta;
	if(b.y > pa.y) { pa.y += 140 * delta;
	} else { pa.y -= 140 * delta; }
	ClearBackground(BLACK);
	DrawRectangle(p1.x,p1.y,p1.width,p1.height,p1.clr);
	DrawRectangle(pa.x,pa.y,pa.width,pa.height,pa.clr);
	DrawCircle(b.x, b.y, b.radius, b.clr);
	DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), RED);
	if(b.y <= 0 || b.y >= GetScreenHeight()-b.radius) b.speedy *= -1;
	if(b.x <= 0 || b.x >= GetScreenWidth()-b.radius) { b.speedx *= -1;
		b.x = GetScreenWidth()/2-b.radius; b.y = GetScreenHeight()/2-b.radius; }
	EndDrawing(); }
CloseWindow();
return 0; }
