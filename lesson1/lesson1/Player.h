#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "InputHandler.h"
#include <iostream>
#include "playerType.cpp"
class Player
{
public:
	Player();
	Player(PlayerType type);
	~Player();
	sf::Vector2f getDirection();
	void handleInput(InputHandler& input);
	void update(float dt);
	void loadTexture();
	bool isMoving();
	void render(sf::RenderWindow& window);
	void setPosition(float x, float y);
	void hide();

	private:
		const int frameWidth = 200;
		const int frameHeight = 207;
		sf::IntRect m_cell;
		sf::Sprite m_sprite;
		sf::Vector2f m_velocity = sf::Vector2f(0, 0);
		sf::Keyboard::Key m_controls[4];//fix
		const float speed = 200.f;
		float rotation = 0.f;
		PlayerType m_type;
		const float sprintMultiplier = 1.5f;
		float m_animationTimer = 0.f;
		int frame = 0;
		const int columns = 4;
		const int totalFrames = 8;
		bool isHidden = false;
		
		const int playerSize = 200;




};

