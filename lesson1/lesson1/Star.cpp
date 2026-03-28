#include <SFML/Graphics.hpp>
#include "Star.h" // Include your own header file!

// IMPLEMENT the constructor using Star::
Star::Star() {
    // Vertical Bar
    m_verticalBar.setSize(sf::Vector2f(10.f, 60.f));
    m_verticalBar.setFillColor(sf::Color::White);
    m_verticalBar.setOrigin(m_verticalBar.getSize() / 2.f); // Centers it!

    // Horizontal Bar
    m_horizontalBar.setSize(sf::Vector2f(60.f, 10.f));
    m_horizontalBar.setFillColor(sf::Color::White);
    m_horizontalBar.setOrigin(m_horizontalBar.getSize() / 2.f); // Centers it!
}

// IMPLEMENT the draw function using Star::
void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Combine the position/rotation of the whole class with the internal shapes
    states.transform *= getTransform();

    // Draw the internal pieces using those combined states
    target.draw(m_verticalBar, states);
    target.draw(m_horizontalBar, states);
}