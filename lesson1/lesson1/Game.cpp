#include "Game.h"

	Game::Game() : m_window(sf::VideoMode(windowWidth, windowHeight), "SFML lesson1")
	{
		m_player.setPosition(windowWidth / 2.f, windowHeight / 2.f);
		m_player.loadTexture();
	}
	Game::~Game() {}

	void Game::Run() {
		float dt;
		while (m_window.isOpen())
		{
			dt = m_clock.restart().asSeconds();
			processEvents();
			update(dt);
			render();
		}
	}

	void Game::processEvents() {

		// --- Event handling ---
		sf::Event event;
		if (m_inputHandler.isKeyPressed(sf::Keyboard::Escape)) {//quick close
			m_window.close();
		}
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			m_inputHandler.handleEvent(event);
		}

	}
	void Game::update(float dt) {
	
		m_player.handleInput(m_inputHandler);
		m_player.update(dt);
		if (m_player.isMoving())
		{
			m_starsManager.update(dt, m_player.getDirection());
		}
	}
	void Game::render() {
		m_window.clear(sf::Color::Black);
		m_starsManager.render(m_window);
		m_player.render(m_window);
		m_window.display();
	}

