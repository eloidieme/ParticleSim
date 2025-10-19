#include "ParticleSystem.hpp"

#include <algorithm>

ParticleSystem::ParticleSystem(sf::Vector2f worldSize_meters) : particles_({}), worldSize_meters_(worldSize_meters)
{
}

void ParticleSystem::update(float dt, sf::Vector2f mousePosition_meters)
{
    applyForces(mousePosition_meters);
    integrate(dt);
    constrainParticles();
    cleanDeadParticles();
}

void ParticleSystem::applyForces(sf::Vector2f mousePosition_meters)
{
    for (auto &p : particles_)
    {
        p.clearForces();

        sf::Vector2f forceVector = mousePosition_meters - p.position_meters();
        float distance_meters = forceVector.length();
        if (distance_meters < minAttractorDistance_meters_)
        {
            distance_meters = minAttractorDistance_meters_;
        }
        sf::Vector2f forceDirection = forceVector / distance_meters;
        float forceMagnitude = attractorStrength_ / (distance_meters * distance_meters);
        p.applyForce(forceMagnitude * forceDirection);
    }
}

void ParticleSystem::constrainParticles()
{
    for (auto &p : particles_)
    {
        sf::Vector2f position = p.position_meters();
        sf::Vector2f velocity = p.velocity_meters_per_sec();

        // Left/Right wall
        if (position.x < 0.f || position.x > worldSize_meters_.x)
        {
            if (position.x < 0.f)
                position.x = 0.01f;
            else
                position.x = worldSize_meters_.x - 0.01f;
            p.setPosition_m(position);
            velocity.x *= -Defaults::BOUNCINESS;
            p.setVelocity_m(velocity);
        }

        // Top/Bottom wall
        if (position.y < 0.f || position.y > worldSize_meters_.y)
        {
            if (position.y < 0.f)
                position.y = 0.01f;
            else
                position.y = worldSize_meters_.y - 0.01f;
            velocity.y *= -Defaults::BOUNCINESS;
            p.setVelocity_m(velocity);
        }
    }
}

void ParticleSystem::integrate(float dt)
{
    for (auto &p : particles_)
    {
        p.update(dt);
    }
}

void ParticleSystem::draw(sf::RenderWindow &window)
{
    for (auto &p : particles_)
    {
        p.draw(window);
    }
}

void ParticleSystem::emit(sf::Vector2f position_meters)
{
    particles_.push_back(Particle(position_meters));
}

void ParticleSystem::cleanDeadParticles()
{
    particles_.erase(
        std::remove_if(
            particles_.begin(),
            particles_.end(),
            [](const Particle &p)
            { return p.isDead(); }),
        particles_.end());
}