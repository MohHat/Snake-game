#pragma once

#define FRUIT_RADIOUS 6

#include "functions.h"
#include "entity.h"
#include "snake.h"

namespace SnakeGame {
    class Snake;

    class Fruit : public Entity {
        public:
            Fruit(olc::PixelGameEngine*);

            void randomTeleport();

            void logic();
            void print();
        private:

    };
}
