/*
<rant>
        I want to fully rework the thing in C so it runs a little pittle better.
        This is part of the rework. I will reuse the code from lightweigh version.
        Unstable, untested, likely doesn't work. I will have to rewrite make file,
        fuck this shit.
</rant>
*/

#include <stdio.h>
#include <raylib.h>


// ---------------------------------[ ~ CONFIG ~ ]---------------------------------
/*
                Colors table | Tabela kolorów: | [place for other languages]
                RED          | Czerwony        |
                BLACK        | Czarny          |
                WHITE        | Biały           |
                RAYWHITE     | Ciemny biały    |
                BLUE         | Niebieski       |
                GREEN        | Zielony         |
*/
// ---------------------------------[ Window cnf. ]---------------------------------

        int window_width = 0;
        int window_height = 0;
        int window_max_fps = 30;

// ---------------------------------[ Paddles cnf ]---------------------------------

        float paddle_width = 25;
        float paddle_height = 80;
        Color paddle_color = RED;
		int paddles_speed = 200;

// ---------------------------------[ Ball conf. ]---------------------------------

        float ball_radius = 20;
        Color ball_color = RED;

// ---------------------------------[ END CONFIG ]---------------------------------

struct Ball {
	float x, y, speedx, speedy, radius;
	Color clr;
};
struct Paddle {
	float x, y, width, height;
	Color clr;
};

int main(void) {
	
	InitWindow(window_width, window_height, "Lightweigh Pong");
	SetTargetFPS(window_max_fps);

	struct Ball b={ 400,250,200,-200,ball_radius,ball_color };
	struct Paddle p1={ 10,170,paddle_width,paddle_height,paddle_color };
	struct Paddle pa={ 765,170,paddle_width,paddle_height,color };

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

	
	if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) p1.y += paddles_speed * delta;
	if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) p1.y -= paddles_speed * delta;
	
	if(b.y > pa.y) { pa.y += paddles_speed-60 * delta;
	} else { pa.y -= paddles_speed-60 * delta; }
	
	ClearBackground(BLACK);

	DrawRectangle(p1.x,p1.y,p1.width,p1.height,p1.clr);
	DrawRectangle(pa.x,pa.y,pa.width,pa.height,pa.clr);
	DrawCircle(b.x, b.y, b.radius, b.clr);
	DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), RED);
	
	if(b.y <= 0 || b.y >= GetScreenHeight()-b.radius) b.speedy *= -1;
	if(b.x <= 10 + paddle_width/2 || b.x >= GetScreenWidth()-10-paddle_width) { b.speedx *= -1;
		b.x = GetScreenWidth()/2-b.radius; b.y = GetScreenHeight()/2-b.radius; }
	
	EndDrawing();	
	}

CloseWindow();
return 0;
}
