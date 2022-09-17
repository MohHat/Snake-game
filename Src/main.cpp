#define OLC_PGE_APPLICATION
#include "headers/olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
        /*
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
        */
        

        Clear(olc::DARK_BLUE);

        if (GetKey(olc::Key::LEFT).bHeld) vec.x -= .5f;
	    if (GetKey(olc::Key::RIGHT).bHeld) vec.x += .5f;
	    if (GetKey(olc::Key::UP).bHeld) vec.y -= .5f;
	    if (GetKey(olc::Key::DOWN).bHeld) vec.y += .5f;

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

        FillCircle(vec, 20, olc::WHITE);
        DrawLine(10, 10, 502, 10, olc::YELLOW);
        
		return true;
	}

    private:
        olc::vi2d vec;

        bool upPressed = false;
        bool downPressed = false;
        bool rightPressed = false;
        bool leftPressed = false;

        float fAccumulatedTime = .0f;
        float fTargetFrameTime = 1.0f / 60.0f;
};


int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
