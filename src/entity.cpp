#include "../include/entity.h"

namespace SnakeGame {
    Entity::Entity(olc::PixelGameEngine* pge, olc::vf2d location)
        : pge_(std::move(pge)), location_(std::move(location)) {}

    olc::PixelGameEngine* Entity::pge() { return pge_; }

    const olc::vf2d& Entity::getLocation() const { return location_; }

    void Entity::setLocation(const olc::vf2d& location) { location_ = location; }

    const float& Entity::getX() const { return location_.x; }

    const float& Entity::getY() const { return location_.y; }

    void Entity::setX(const float& x) { location_.x = x; }

    void Entity::setY(const float& y) { location_.y = y; }
}
