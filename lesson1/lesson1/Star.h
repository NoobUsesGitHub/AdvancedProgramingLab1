#pragma once // This prevents the file from being included multiple times
#include <SFML/Graphics.hpp>

class Star : public sf::Drawable, public sf::Transformable {
public:
    // We only DECLARE the constructor here
    Star();

private:
    sf::RectangleShape m_verticalBar;
    sf::RectangleShape m_horizontalBar;

    // We only DECLARE the draw function here
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
