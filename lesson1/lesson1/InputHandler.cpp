#include "InputHandler.h"


//input: event from the game loop, we check if it's a key press or release and update the state of that key in our map
void InputHandler::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		m_keyStates[event.key.code] = true;
	} else if(event.type == sf::Event::KeyReleased) {
		m_keyStates[event.key.code] = false;
	}
}

bool InputHandler::isKeyPressed(sf::Keyboard::Key key) {
	auto it = m_keyStates.find(key);
	return it != m_keyStates.end() && it->second;
}
