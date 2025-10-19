#pragma once
#include <SFML/System/Vector2.hpp>

namespace World
{
    constexpr float PIXELS_PER_METER = 100.f;

    inline sf::Vector2f toMeters(sf::Vector2f pixels)
    {
        return pixels / PIXELS_PER_METER;
    }

    inline sf::Vector2f toPixels(sf::Vector2f meters)
    {
        return meters * PIXELS_PER_METER;
    }
}
