#include "../include/snake.h"

namespace SnakeGame {
    Snake::Snake(olc::PixelGameEngine* pge, std::unique_ptr<Fruit>* fruit)
        : Entity(std::move(pge)), fruit_(std::move(fruit)) {}

    const Direction& Snake::getDirection() const { return snakeDirection_; }

    void Snake::logic() {
        // perhaps we could simplify this...
        if (pge()->GetKey(olc::Key::LEFT).bHeld) { snakeDirection_ = Direction::left; }
	    if (pge()->GetKey(olc::Key::RIGHT).bHeld) { snakeDirection_ = Direction::right; }
        if (pge()->GetKey(olc::Key::UP).bHeld) { snakeDirection_ = Direction::up; }
	    if (pge()->GetKey(olc::Key::DOWN).bHeld) { snakeDirection_ = Direction::down; }
        
        switch (snakeDirection_) {
            case Direction::left:
                setX(getX() - SNAKE_SPEED);
                break;
            case Direction::right:
                setX(getX() + SNAKE_SPEED);
                break;
            case Direction::up:
                setY(getY() - SNAKE_SPEED);
                break;
            case Direction::down:
                setY(getY() + SNAKE_SPEED);
                break;
            default:
                break;
        }
        
        if (isTouchingFruit()) {
            getFruit()->randomTeleport();
            // snake stuff
        }
        
    }

    void Snake::print() {
        pge()->FillRect(getLocation(), SNAKE_SIZE, olc::WHITE);
    }

    Fruit* Snake::getFruit() const {
        return fruit_->get();
    }

    bool Snake::isTouchingFruit() const {
        // TODO: check for collision in 4 points
        return sqrt(
            (getX() - getFruit()->getX()) * (getX() - getFruit()->getX()) + 
            (getY() - getFruit()->getY()) * (getY() - getFruit()->getY())
        ) < FRUIT_RADIOUS * 2;
    }
}
