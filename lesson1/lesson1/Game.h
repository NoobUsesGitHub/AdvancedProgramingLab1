#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StarsManager.h" 
#include "InputHandler.h" 
#include "Player.h" 
#include "Globals.h" 
class Game
{
public:
	Game();
	~Game();
public:
	void Run();

private:
	void processEvents();
	void update(float dt);
	void render();

private: //members
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	Player m_player;
	InputHandler m_inputHandler;
	StarsManager m_starsManager;
};

