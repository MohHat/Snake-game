#include "../include/game.h"

int main() {
    // Compile using: g++ olcPixelGameEngine.cpp game.cpp entity.cpp snake.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
    // I'll make a makefile (no pun intended) soon
    SnakeGame::Game game;
    if (game.Construct(256, 256, 4, 4)) { game.Start(); }
    return 0;
}

namespace SnakeGame {
    Game::Game() {
        sAppName = "SnakeGame";


    }

    bool Game::OnUserCreate() {
        snake = std::make_unique<Snake>(this);

        return true; 
    }

    bool Game::OnUserUpdate(float fElapsedTime) {
        fAccumulatedTime += fElapsedTime;
        if (fAccumulatedTime >= fTargetFrameTime) {
            fAccumulatedTime -= fTargetFrameTime;
            fElapsedTime = fTargetFrameTime;
        } else { return true; }
        

        // We do logic here //
        snake->logic();
        // other logic...

        // We display stuff here //
        Clear(olc::DARK_GREEN);
        
        if (snake->getDirection() == Direction::freeze) { DrawString(60, 120, "PRESS ANY KEY TO START", olc::WHITE, 1); }

        snake->print();
        // other print()s...
        return true;
    }
}
