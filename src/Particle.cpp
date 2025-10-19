#include "Particle.hpp"
#include "World.hpp"

Particle::Particle(sf::Vector2f position_m)
    : position_meters_(position_m),
      velocity_meters_per_sec_(0.0f, 0.0f),
      acceleration_meters_per_sec2_(0.0f, 0.0f),
      forceAccumulator_(0.0f, 0.0f),
      shape_(0.0f)
{
    shape_.setFillColor(sf::Color::Red);
    shape_.setRadius(radius_meters_ * World::PIXELS_PER_METER);
}

void Particle::update(float dt)
{
    acceleration_meters_per_sec2_ = forceAccumulator_ / mass_kg_;
    velocity_meters_per_sec_ += acceleration_meters_per_sec2_ * dt;
    position_meters_ += velocity_meters_per_sec_ * dt;

    lifetime_secs_ -= dt;
}

void Particle::clearForces()
{
    forceAccumulator_.x = 0.f;
    forceAccumulator_.y = 0.f;
}

void Particle::draw(sf::RenderWindow &window)
{
    shape_.setPosition(World::toPixels(position_meters_));
    window.draw(shape_);
}

void Particle::applyForce(sf::Vector2f force)
{
    forceAccumulator_ += force;
}