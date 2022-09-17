#define OLC_PGE_APPLICATION
#include "headers/olcPixelGameEngine.h"

int randomNumber(const int& a, const int& b) 
{
    return rand() % b + a;
}

class Example : public olc::PixelGameEngine
{
public:
    enum DIR
    {
        STAYING = 0,
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4,
    };

	Example()
	{
		sAppName = "Example";

        fruit_pos.x = randomNumber(10, 240);
        fruit_pos.y = randomNumber(10, 240);
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        

        if (GetKey(olc::Key::LEFT).bHeld) snake_direction = DIR::LEFT;
	    if (GetKey(olc::Key::RIGHT).bHeld) snake_direction = DIR::RIGHT;
        if (GetKey(olc::Key::UP).bHeld) snake_direction = DIR::UP;
	    if (GetKey(olc::Key::DOWN).bHeld) snake_direction = DIR::DOWN;

        fAccumulatedTime += fElapsedTime;
        if (fAccumulatedTime >= fTargetFrameTime) 
        {
            fAccumulatedTime -= fTargetFrameTime;
            fElapsedTime = fTargetFrameTime;
        }
        else
        {
            return true;
        }

        switch (snake_direction)
        {
        case DIR::STAYING:
            DrawString(128, 120, "PRESS ANY KEY TO START", olc::WHITE, 2);
            break;

        case DIR::UP:
            vec.y -= 1.75f;
            break;
        case DIR::DOWN:
            vec.y += 1.75f;
            break;
        case DIR::LEFT:
            vec.x -= 1.75f;
            break;
        case DIR::RIGHT:
            vec.x += 1.75f;
            break;
        }

        if(sqrt
        (
            (vec.x - fruit_pos.x)* (vec.x - fruit_pos.x) 
            + 
            (vec.y - fruit_pos.y) * (vec.y - fruit_pos.y)
        ) < 16.0f
          )
        {
            fruit_pos.x = randomNumber(10, 240);
            fruit_pos.y = randomNumber(10, 240);
        }

        Clear(olc::DARK_GREEN);


        FillRect(vec, olc::vi2d(10,10), olc::WHITE);
        FillCircle(fruit_pos, 8, olc::RED);
        DrawString(20, 240, std::to_string(vec.x) + "   " + std::to_string(vec.y), olc::WHITE, 1);
        DrawString(20, 210, std::to_string((vec.x - fruit_pos.x) * (vec.x - fruit_pos.x) +  (vec.y - fruit_pos.y) * (vec.y - fruit_pos.y)), olc::WHITE, 1);
		return true;
	}

    private:

        
        // variables //////////////////////

        std::vector<olc::vf2d> snake_body;

        olc::vf2d vec, fruit_pos;

        unsigned short snake_direction = 0;

        float fAccumulatedTime = .0f;
        float fTargetFrameTime = 1.0f / 60.0f;

        /////////////////////////////////////
        
        ///// methods///////////
        void DisplaySnake()
        {

        }
};


int main()
{
    srand(time(0));
	Example demo;
	if (demo.Construct(256, 256, 4, 4))
		demo.Start();

	return 0;
}
