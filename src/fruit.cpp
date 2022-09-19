#include "../include/fruit.h"

namespace SnakeGame {
    Fruit::Fruit(olc::PixelGameEngine* pge, const std::unique_ptr<Snake>* snake)
        : Entity(std::move(pge)), snake_(std::move(snake)) {}

    void Fruit::logic() {
        if(sqrt(
            (snake_->get()->getX() - getX()) * (snake_->get()->getX() - getX()) + 
            (snake_->get()->getY() - getY()) * (snake_->get()->getY() - getY())
        ) < 16.0f ) {
            setX(rngRange(10, 240));
            setY(rngRange(10, 240));
        }
    }

    void Fruit::print() {
        pge()->FillCircle(getLocation(), 8, olc::RED);
    }
}