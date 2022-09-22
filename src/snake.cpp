#include "../include/snake.h"

namespace SnakeGame {
    Snake::Snake(olc::PixelGameEngine* pge, const std::unique_ptr<Fruit>* fruit)
        : Entity(std::move(pge)), fruit_(std::move(fruit)) {}

    const Direction& Snake::getDirection() const { return snakeDirection; }

    void Snake::logic() {
        // perhaps we could simplify this...
        if (pge()->GetKey(olc::Key::LEFT).bHeld) { snakeDirection = Direction::left; }
	    if (pge()->GetKey(olc::Key::RIGHT).bHeld) { snakeDirection = Direction::right; }
        if (pge()->GetKey(olc::Key::UP).bHeld) { snakeDirection = Direction::up; }
	    if (pge()->GetKey(olc::Key::DOWN).bHeld) { snakeDirection = Direction::down; }

        switch (snakeDirection) {
            case Direction::left:
                setX(getX() - SPEED);
                break;
            case Direction::right:
                setX(getX() + SPEED);
                break;
            case Direction::up:
                setY(getY() - SPEED);
                break;
            case Direction::down:
                setY(getY() + SPEED);
                break;
            default:
                break;
        }
    }

    void Snake::print() {
        pge()->FillRect(getLocation(), olc::vi2d(10,10), olc::WHITE);
    }
}
