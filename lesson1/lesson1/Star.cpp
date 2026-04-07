#include <SFML/Graphics.hpp>
#include <random>
#include "Star.h" 

Star::Star() {
    // Vertical Bar
    m_verticalBar.setSize(sf::Vector2f(width, height));
    m_verticalBar.setFillColor(sf::Color::White);
    m_verticalBar.setOrigin(m_verticalBar.getSize() / 2.f); // Centers it!

    // Horizontal Bar
    m_horizontalBar.setSize(sf::Vector2f(height, width));
    m_horizontalBar.setFillColor(sf::Color::White);
    m_horizontalBar.setOrigin(m_horizontalBar.getSize() / 2.f); // Centers it!
}
Star::Star(float windowWidth, float windowHeight, std::mt19937& gen) {

    // Vertical Bar
    m_verticalBar.setSize(sf::Vector2f(width, height));
    m_verticalBar.setFillColor(sf::Color::White);
    m_verticalBar.setOrigin(m_verticalBar.getSize() / 2.f); // Centers it!

    // Horizontal Bar
    m_horizontalBar.setSize(sf::Vector2f(height, width));
    m_horizontalBar.setFillColor(sf::Color::White);
    m_horizontalBar.setOrigin(m_horizontalBar.getSize() / 2.f); // Centers it!
    // Randomize position within the window
    std::uniform_real_distribution<float> disX(0.f, windowWidth);
    std::uniform_real_distribution<float> disY(0.f, windowHeight);
    setPosition(disX(gen), disY(gen));
}


void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Combine the position/rotation of the whole class with the internal shapes
    states.transform *= getTransform();

    // Draw the internal pieces using those combined states
    target.draw(m_verticalBar, states);
    target.draw(m_horizontalBar, states);
}