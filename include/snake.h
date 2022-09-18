#pragma once

#define SPEED 1.75f

#include "entity.h"

namespace SnakeGame {
    class Snake : public Entity {
        public:
            Snake(olc::PixelGameEngine*);
            Snake(olc::PixelGameEngine*, olc::vf2d);

            const Direction& getDirection() const;

            void logic();
            void print();
        private:
            Direction snakeDirection = Direction::freeze;
    };
}