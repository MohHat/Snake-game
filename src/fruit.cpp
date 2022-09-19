#include "../include/fruit.h"

namespace SnakeGame {
    Fruit::Fruit(olc::PixelGameEngine* pge)
        : Entity(std::move(pge)) {}

    Fruit::Fruit(olc::PixelGameEngine* pge, olc::vf2d location)
        : Entity(std::move(pge), std::move(location)) {}

    void Fruit::logic() {}

    void Fruit::print() {}
}