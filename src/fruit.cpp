#include "../include/fruit.h"

namespace SnakeGame {
    Fruit::Fruit(olc::PixelGameEngine* pge)
        : Entity(std::move(pge)) {
        randomTeleport();
    }

    // this might be moved inside Entity in the future so that it can be used by Snake as well
    void Fruit::randomTeleport() {
        setX(rngRange(2 * FRUIT_RADIOUS, pge()->ScreenWidth() - 2 * FRUIT_RADIOUS));
        setY(rngRange(2 * FRUIT_RADIOUS, pge()->ScreenHeight() - 2 * FRUIT_RADIOUS));
    }

    void Fruit::logic() {}

    void Fruit::print() {
        pge()->FillCircle(getLocation(), FRUIT_RADIOUS, olc::RED);
    }
}
