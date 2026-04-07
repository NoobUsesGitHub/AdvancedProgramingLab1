#pragma once
#include <SFML/Window.hpp>
#include <unordered_map>
class InputHandler
{
public:
	void handleEvent(sf::Event& event);
	bool isKeyPressed(sf::Keyboard::Key key);

private:
	std::unordered_map<sf::Keyboard::Key, bool> m_keyStates;
};

