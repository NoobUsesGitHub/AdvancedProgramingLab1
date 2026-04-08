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
	sf::RectangleShape m_pauseBackground;
	sf::Text m_pauseText;
	InputHandler m_inputHandler;
	StarsManager m_starsManager;
	bool pause= false;
	bool twoPlayerGame = false;
	sf::Font m_font;
};

