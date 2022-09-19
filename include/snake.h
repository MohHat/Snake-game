#pragma once

#define SPEED 1.75f

#include "entity.h"
#include "fruit.h"

namespace SnakeGame {
    class Fruit;

    class Snake : public Entity {
        public:
            Snake(olc::PixelGameEngine*, const std::unique_ptr<Fruit>*);

            const Direction& getDirection() const;

            void logic();
            void print();
        private:
            Direction snakeDirection = Direction::freeze;
            const std::unique_ptr<Fruit>* fruit_;
    };
}