#pragma once // This prevents the file from being included multiple times
#include <SFML/Graphics.hpp>

class Star : public sf::Drawable, public sf::Transformable {
public:
    // We only DECLARE the constructor here
    Star();
	Star(float windowWidth, float windowHeight, std::mt19937& gen);
	virtual void starMove(sf::Vector2f direction, float dt) { sf::Transformable::move(direction ); }
	virtual void setSpeed(float newSpeed) { speed = newSpeed; }
	virtual void setRotation(float newRotation) { rotation = newRotation; }
	virtual void setSize(float newWidth, float newHeight) {
		width = newWidth;
		height = newHeight;
		m_verticalBar.setSize(sf::Vector2f(width, height));
		m_horizontalBar.setSize(sf::Vector2f(height, width));
	}
private:
    sf::RectangleShape m_verticalBar;
    sf::RectangleShape m_horizontalBar;
	float rotation = 0.f;
	float speed = 50.f;
	float width = 6.f;
	float height = 18.f;

    // We only DECLARE the draw function here
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};
