#include "StarsManager.h"

StarsManager::StarsManager() {
    std::random_device rd;
    m_gen = std::mt19937(rd());
	for (int i = 0; i < numberOfStars; ++i) {
		m_stars.emplace_back(Star(windowWidth, windowHeight, m_gen));
	}
}


StarsManager::~StarsManager() {}

void StarsManager::render(sf::RenderWindow& window) {
	for (Star& star : m_stars)
		window.draw(star);
}

void StarsManager::update(float dt, sf::Vector2f playerDirection) {
    float parallaxFactor = 0.5f;
    std::uniform_real_distribution<float> disX(0.f, windowWidth);
    std::uniform_real_distribution<float> disY(0.f, windowHeight);

    for (Star& star : m_stars) {

        star.starMove(playerDirection, dt);

        sf::Vector2f pos = star.getPosition();
        bool outOfBounds = false;

        // Left edge -> Respawn on the Right edge, random Y
        if (pos.x < 0) {
            pos.x = windowWidth;
            pos.y = disY(m_gen);
            outOfBounds = true;
        }
        // Right edge -> Respawn on the Left edge, random Y
        else if (pos.x > windowWidth) {
            pos.x = 0;
            pos.y = disY(m_gen);
            outOfBounds = true;
        }

        // Top edge -> Respawn on the Bottom edge, random X
        if (pos.y < 0) {
            pos.x = disX(m_gen);
            pos.y = windowHeight;
            outOfBounds = true;
        }
        // Bottom edge -> Respawn on the Top edge, random X
        else if (pos.y > windowHeight) {
            pos.x = disX(m_gen);
            pos.y = 0;
            outOfBounds = true;
        }

        // Apply the new position if it went off screen
        if (outOfBounds) {
            star.setPosition(pos.x, pos.y);
        }
    }
}