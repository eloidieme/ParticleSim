#pragma once

#include <SFML/Graphics.hpp>

#include "Defaults.hpp"

class Particle
{
public:
    Particle(sf::Vector2f position_m);

    void applyForce(sf::Vector2f force);
    void clearForces();
    void update(float dt);
    void draw(sf::RenderWindow &window);

    sf::Vector2f position_meters() const { return position_meters_; }
    bool isDead() const { return lifetime_secs_ <= 0.f; }

private:
    sf::Vector2f position_meters_;
    sf::Vector2f velocity_meters_per_sec_;
    sf::Vector2f acceleration_meters_per_sec2_;
    sf::Vector2f forceAccumulator_;

    sf::CircleShape shape_;

    float mass_kg_ = Defaults::PARTICLE_MASS_KG;
    float lifetime_secs_ = Defaults::PARTICLE_LIFETIME_S;
    float radius_meters_ = Defaults::PARTICLE_RADIUS_M;
};