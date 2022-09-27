#pragma once

#define SNAKE_SPEED 1.75f
#define SNAKE_SIZE  { 10, 10 }

#include "entity.h"
#include "fruit.h"

namespace SnakeGame {
    class Fruit;

    class Snake : public Entity {
        public:
            Snake(olc::PixelGameEngine*, std::unique_ptr<Fruit>*);

            const Direction& getDirection() const;

            void logic();
            void print();
        private:
            Direction snakeDirection_ = Direction::freeze;
            std::vector<olc::vf2d> body_;
            std::unique_ptr<Fruit>* fruit_;

            Fruit* getFruit() const;

            bool isTouchingFruit() const;
    };
}