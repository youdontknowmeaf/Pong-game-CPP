#include <iostream>
#include <raylib.h>

        int screen_width = 800;
        int screen_height = 800;


class Ball{
    public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void draw() {
        DrawCircle(x, y, radius, WHITE);
    }

    void update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x *= -1;
        }
    }
};

class Paddle {
    public:
    float x,y;
    float width, height;
    int speed;

        void draw()
        {
            DrawRectangle(x, y, width, height, WHITE);
        }
                    void prevent_leaving()
                    {
                        if(y > 650)
                        {
                            y = 650;
                        }
                        if(y < 5)
                        {
                            y = 5;
                        }
                    }
                    void update()
                    {
                    if(IsKeyDown(KEY_UP))
                        {
                            y = y - speed;
                        }
                    else if(IsKeyDown(KEY_DOWN))
                        {
                            y = y + speed;
                        }
                    }

};

class AIPaddle: public Paddle
{
    public:
    void update(Ball &ball)
    {
        if(ball.y < y)
        {
            y = y - speed;
        }
        else
        {
            y = y + speed;
        }
    }
};




int main()
{
    Ball ball;
    Paddle paddlel;
    AIPaddle paddler;
    InitWindow(800, 800, "Game");
    SetTargetFPS(30);
    
    ball.radius = 2;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    paddlel.height = 150;
    paddlel.width = 30;
    paddlel.x = 10;
    paddlel.y = screen_height/2 - paddlel.height/2;
    paddlel.speed = 5;

    paddler.height = 150;
    paddler.width = 30;
    paddler.x = screen_width - paddler.width;
    paddler.y = screen_height/2 - paddler.height/2;
    paddler.speed = 5;

    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{paddlel.x, paddlel.y, paddlel.width, paddlel.height}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{paddler.x, paddler.y, paddler.width, paddler.height}))
        {
            ball.speed_x *= -1;
        }
        if(ball.x < 3 || ball.x > GetScreenWidth()-3)
        {
            ball.x = GetScreenWidth()/2;
            ball.y = GetScreenHeight()/2;
        }

        ball.update();

        paddlel.update();
        paddlel.prevent_leaving();

        paddler.update(ball);
        paddler.prevent_leaving();
        
    
        ClearBackground(BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        ball.draw();

        paddlel.draw();
        paddler.draw();



        EndDrawing();
    }



    CloseWindow();
    return 0;
}