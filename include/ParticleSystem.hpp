#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Particle.hpp"
#include "Defaults.hpp"

class ParticleSystem
{
public:
    ParticleSystem(sf::Vector2f worldSize_meters);

    void update(float dt, sf::Vector2f mousePosition_meters);
    void draw(sf::RenderWindow &window);
    void emit(sf::Vector2f position_meters);
    void constrainParticles();

    void setAttractorStrength(float strength) { attractorStrength_ = strength; }
    float attractorStrength() { return attractorStrength_; }

private:
    std::vector<Particle> particles_;
    sf::Vector2f worldSize_meters_;
    float attractorStrength_ = Defaults::ATTRACTOR_STRENGTH;
    float minAttractorDistance_meters_ = Defaults::MIN_ATTRACTOR_DISTANCE_M;

    void applyForces(sf::Vector2f mousePosition_meters);
    void integrate(float dt);
    void cleanDeadParticles();
};