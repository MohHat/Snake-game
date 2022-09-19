#pragma once

#include "entity.h"

namespace SnakeGame {
    class Fruit : public Entity {
        public:
            Fruit(olc::PixelGameEngine*);
            Fruit(olc::PixelGameEngine*, olc::vf2d);

            void logic();
            void print();
        private:
        
    };
}