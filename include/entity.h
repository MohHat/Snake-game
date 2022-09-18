#pragma once

#include "../lib/olcPixelGameEngine.h"

namespace SnakeGame {
    // typically, macros are ALL_CAPS so I made it lowercase (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#enum5-dont-use-all_caps-for-enumerators)
    enum Direction {
        freeze,
        up,
        down,
        left,
        right
    };

    class Entity {
        public:
            Entity(olc::PixelGameEngine*, olc::vf2d = { .0f, .0f });

            olc::PixelGameEngine* pge();

            const olc::vf2d& getLocation() const;
            void setLocation(const olc::vf2d&);
            const float& getX() const;
            const float& getY() const;
            void setX(const float&);
            void setY(const float&);

            virtual void logic() = 0;
            virtual void print() = 0;
        private:
            olc::PixelGameEngine* pge_; // see https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/Multiple-File-Projects
            olc::vf2d location_;
    };
}