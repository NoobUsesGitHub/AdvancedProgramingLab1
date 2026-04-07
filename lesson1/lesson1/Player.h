#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "InputHandler.h"
#include <iostream>
class Player
{
public:
	Player();
	~Player();
	sf::Vector2f getDirection();
	void handleInput(InputHandler& input);
	void update(float dt);
	void loadTexture();
	bool isMoving();
	void render(sf::RenderWindow& window);
	void setPosition(float x, float y);

	private:
		sf::IntRect m_cell;
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_velocity = sf::Vector2f(0, 0);
		const int frameWidth = 200;
		const int frameHeight = 207;
		const float speed = 200.f;
		float rotation = 0.f;
		const float sprintMultiplier = 1.5f;
		float m_animationTimer = 0.f;
		int frame = 0;
		const int columns = 4;
		const int totalFrames = 8;
		const char* filePath = "C:/oz/APL1/AdvancedProgramingLab1/lesson1/lesson1/textures/rokcetSpritesheet.png";
		//const char* filePath = "D:/study/colman/APL1/textures/rokcetSpritesheet.png";
		const int playerSize = 200;




};

