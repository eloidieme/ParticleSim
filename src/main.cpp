#include <vector>

#include <SFML/Graphics.hpp>

#include "ParticleSystem.hpp"
#include "World.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "ParticleSim");
    window.setFramerateLimit(144);

    sf::Clock clock;
    ParticleSystem system;

    while (window.isOpen())
    {
        sf::Vector2f mousePos_pixels = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f mousePos_meters = World::toMeters(mousePos_pixels);
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                system.emit(mousePos_meters);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
            {
                system.setAttractorStrength(system.attractorStrength() + 1.0f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
            {
                system.setAttractorStrength(system.attractorStrength() - 1.0f);
            }
        }

        float dt = clock.restart().asSeconds();
        system.update(dt, mousePos_meters);

        window.clear();
        system.draw(window);
        window.display();
    }
}
