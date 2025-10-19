#include "ParticleSystem.hpp"

#include <algorithm>

ParticleSystem::ParticleSystem() : particles_({})
{
}

void ParticleSystem::update(float dt, sf::Vector2f mousePosition_meters)
{
    applyForces(mousePosition_meters);
    integrate(dt);
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