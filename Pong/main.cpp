#include <iostream>
#include <raylib.h>
#include <string>


//----------------------------------[ Konfiguracja ]--------------------------------------------------------------------------//


        int screen_width = 800; // Zmiana szerokosci okna
								// Window width
        int screen_height = 500; // Zmiana wysokosci okna
								 // Window height
	int score_left = 0; // Poczatkowy wynik gracza lewego
						// Beginning score of left player
	int score_right = 0; // ------------==--------- prawego
						 // Same as before but for right player
	int MaxFps = 45; // Maksymalna liczba FPS
					 // Max FPS limit
	int ball_speed = 7; // Predkosc pileczki (ostrożnie)
						// Ball speed (careful)
        int ball_radius = screen_height/25;     // Promień koła (piłki)
                        // Radius of the circle (ball)
	int paddle_speed = 5; // Predkosc paletek do ping ponga
						// Speed of ping pong paddles
	std::string mainColor = "RED";     // Zmiana koloru glownego (zalecany: "default main")
									   // Changing main color (recommended: "default main")
	std::string secColor = "BLUE"; // Zmiana koloru pobocznego (zalecany: "default secondary")
									// Changing secondary color (recommended: "default secondary")
						  // |------ Table of colors -----------|
						  // |name:                             |
						  // |------ Tabela Kolorow ------------|
						  // |nazwa:                Tlumaczenie:|
						  // |----------------------------------|
						  //  WHITE        -        Bialy
						  //  BLACK        -        Czarny
						  //  RED          -        Czerwony
						  //  GREEN        -        Zielony
						  //  BLUE         -        Niebieski
						  //  YELLOW       -        Zolty
						  //  PURPLE       -        Fioletowy
						  //  ORANGE       -        Pomaranczowy
						  //  GRAY         -        Szary
						  //  This part is self axplainatory in english.

//------------------------------------------------------------------------------------------------------------------------------//

















	Color getCol(std::string name) {
	if (name == "WHITE") return WHITE;
	if (name == "BLACK") return BLACK;
    	if (name == "RED") return RED;
    	if (name == "GREEN") return GREEN;
    	if (name == "BLUE") return BLUE;
    	if (name == "YELLOW") return YELLOW;
    	if (name == "PURPLE") return PURPLE;
    	if (name == "ORANGE") return ORANGE;
    	if (name == "GRAY") return GRAY;
	if (name == "default secondary") return RAYWHITE;
	if (name == "default main") return BLACK;
	return RED;
}

class Ball{
    public:
    float x, y;
    int speed_x, speed_y;
    int radius = ball_radius;

    void draw() {
        DrawCircle(x, y, ball_radius, getCol(secColor));
    }

    void update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }

	// Why did I make this shit under this comment...?

        /*
	if(x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x *= -1;
        }
	*/
    }
};

class PaddleArrow {
    public:
    float x,y;
    float width, height;
    int speed;

        void draw()
        {
            DrawRectangle(x, y, width, height, getCol(secColor));
        }
                    void prevent_leaving()
                    {
                        if(y > GetScreenHeight() - height - 5)
                        {
                            y = GetScreenHeight() - height - 5;
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

class PaddleWSAD: public PaddleArrow
{
    public:
    void update()
                    {
                    if(IsKeyDown(KEY_W))
                        {
                            y = y - speed;
                        }
                    else if(IsKeyDown(KEY_S))
                        {
                            y = y + speed;
                        }
                    }
                };




int main()
{
    Ball ball;
    PaddleWSAD paddlel;
    PaddleArrow paddler;
    InitWindow(screen_width, screen_height, "Game");
    SetTargetFPS(MaxFps);
    
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = ball_speed;
    ball.speed_y = ball_speed;

    paddlel.height = 150;
    paddlel.width = 30;
    paddlel.x = 0;
    paddlel.y = screen_height/2 - paddlel.height/2;
    paddlel.speed = paddle_speed;

    paddler.height = 150;
    paddler.width = 30;
    paddler.x = screen_width - paddler.width;
    paddler.y = screen_height/2 - paddler.height/2;
    paddler.speed = paddle_speed;

    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{paddlel.x, paddlel.y, paddlel.width, paddlel.height}))
        {
            ball.speed_x *= -1;
	    score_left += 1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{paddler.x, paddler.y, paddler.width, paddler.height}))
        {
            ball.speed_x *= -1;
	    score_right += 1;
        }
	if(ball.x < 3 || ball.x > GetScreenWidth()-3)
        {
            ball.x = GetScreenWidth()/2;
            ball.y = GetScreenHeight()/2;
        }

        ball.update();

        paddlel.update();
        paddlel.prevent_leaving();

        paddler.update();
        paddler.prevent_leaving();
        
    
        ClearBackground(getCol(mainColor));
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, getCol(secColor));
        ball.draw();

        paddlel.draw();
        paddler.draw();

	DrawText(TextFormat("Score: %d", score_left), GetScreenWidth()/4-GetScreenHeight()/20, GetScreenHeight()/10, GetScreenHeight()/20, getCol(secColor)); //lewa paletka
	DrawText(TextFormat("Score: %d", score_right), GetScreenWidth()/4*3-GetScreenHeight()/20, GetScreenHeight()/10, GetScreenHeight()/20, getCol(secColor)); //prawa paletka
        EndDrawing();
    }



    CloseWindow();
    return 0;
}
