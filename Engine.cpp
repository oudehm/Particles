#include "Engine.h"
#include <iostream>


Engine::Engine() {
    // Create the SFML window with the desktop resolution
    m_Window.create(sf::VideoMode::getDesktopMode(), "SFML Window");
   
}

void Engine::run() {
    sf::Clock clock;

    while (m_Window.isOpen()) {
        sf::Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
    // Starting Particle unit tests
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { static_cast<int>(m_Window.getSize().x / 2), static_cast<int>(m_Window.getSize().y / 2) });
    p.unitTests();
    cout << "Unit tests complete. Starting engine..." << endl;
}

void Engine::input() {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            m_Window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int numPoints = rand() % 26 + 25;
            sf::Vector2i mouseClickPosition = { event.mouseButton.x, event.mouseButton.y };
            m_particles.emplace_back(m_Window, numPoints, mouseClickPosition);
        }
    }
}

void Engine::update(float dtAsSeconds) {
    for (auto it = m_particles.begin(); it != m_particles.end();) {
        if (it->getTTL() > 0.0) {
            it->update(dtAsSeconds);
            ++it;
        }
        else {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw() {
    m_Window.clear();

    for (const auto& particle : m_particles) {
        m_Window.draw(particle);
    }

    m_Window.display();
}