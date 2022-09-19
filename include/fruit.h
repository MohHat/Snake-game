#pragma once

#include "functions.h"
#include "entity.h"
#include "snake.h"

namespace SnakeGame {
    class Snake;

    class Fruit : public Entity {
        public:
            Fruit(olc::PixelGameEngine*, const std::unique_ptr<Snake>*);

            void logic();
            void print();
        private:
            const std::unique_ptr<Snake>* snake_;
    };
}
