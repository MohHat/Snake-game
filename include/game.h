#pragma once

#define FPS 60.0f

#include "../include/snake.h"
#include "../include/fruit.h"

namespace SnakeGame {
    class Game : public olc::PixelGameEngine {
        public:
            Game();
            bool OnUserCreate() override;
            bool OnUserUpdate(float) override;
        private:
            std::unique_ptr<Snake> snake { nullptr };
            std::unique_ptr<Fruit> fruit { nullptr };

            float fAccumulatedTime = .0f;
            float fTargetFrameTime = 1.0f / FPS;
    };
}
