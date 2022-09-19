#include "../include/game.h"

int main() {
    // Compile using: g++ olcPixelGameEngine.cpp game.cpp entity.cpp snake.cpp fruit.cpp functions.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
    // I'll make a makefile (no pun intended) soon
    SnakeGame::Game game;
    if (game.Construct(256, 256, 4, 4)) { game.Start(); }
    return 0;
}

namespace SnakeGame {
    Game::Game() {
        srand(time(NULL));
        sAppName = "SnakeGame"; 
    }

    bool Game::OnUserCreate() {
        fruit = std::make_unique<Fruit>(this, &snake);
        snake = std::make_unique<Snake>(this, &fruit);

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
        fruit->logic();
        // other logic...

        // We display stuff here //
        Clear(olc::DARK_GREEN);
        
        if (snake->getDirection() == Direction::freeze) { DrawString(60, 120, "PRESS ANY KEY TO START", olc::WHITE, 1); }

        snake->print();
        fruit->print();
        // other print()s...
        return true;
    }
}
