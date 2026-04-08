#include "Game.h"

Game::Game() : m_window(sf::VideoMode(windowWidth, windowHeight), "SFML lesson1"), m_pauseText("PAUSED", m_font, 50), m_pauseBackground(sf::Vector2f(300,200))
	{
		m_font.loadFromFile("C:/oz/APL1/AdvancedProgramingLab1/lesson1/lesson1/textures/arial.ttf");
		m_pauseText.setFillColor(sf::Color::White);
		m_pauseBackground.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black
		m_pauseBackground.setPosition(windowWidth / 2.f - m_pauseBackground.getSize().x / 2.f, windowHeight / 2.f - m_pauseBackground.getSize().y / 2.f);
		m_pauseText.setPosition(windowWidth / 2.f - m_pauseText.getLocalBounds().width / 2.f, windowHeight / 2.f - m_pauseText.getLocalBounds().height / 2.f);
		m_player.setPosition(windowWidth / 2.f, windowHeight / 2.f);
		if (!twoPlayerGame)
		{
			m_player2.hide();
		}
		m_player.loadTexture();
	}
	Game::~Game() {}

	void Game::Run() {
		float dt;
		m_clock.restart(); // FIX: Reset clock here to prevent massive first dt
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
		if(m_inputHandler.isKeyPressed(sf::Keyboard::R)) {//reset player position
			m_player.setPosition(windowWidth / 2.f, windowHeight / 2.f);
		}
		while (m_window.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					pause = !pause;
				}
			}
			if (event.type == sf::Event::Closed)
				m_window.close();
			m_inputHandler.handleEvent(event);
		}

	}
	void Game::update(float dt) {
		if(!pause){
			m_player.handleInput(m_inputHandler);
			m_player.update(dt);
			if (m_player.isMoving())
			{
				m_starsManager.update(dt, -m_player.getDirection());
			}
		}
	}
	void Game::render() {
		m_window.clear(sf::Color::Black);
		m_starsManager.render(m_window);
		m_player.render(m_window);
		if(pause){
			// Draw pause text
			m_window.draw(m_pauseBackground);
			m_window.draw(m_pauseText);
		}
		m_window.display();
	}

