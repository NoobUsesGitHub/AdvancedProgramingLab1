#include "Game.h"
//const char* filePath = "C:/oz/APL1/AdvancedProgramingLab1/lesson1/lesson1/textures/rocketSpritesheet.png";
const char* filePath = "D:/study/colman/APL1/textures/rokcetSpritesheet.png";
sf::Texture rocketTexture;
Game::Game() : m_player(PlayerType::Arrows), m_player2(PlayerType::WASD), m_window(sf::VideoMode(windowWidth, windowHeight), "SFML lesson1"), m_pauseText("PAUSED", m_font, 50), m_pauseBackground(sf::Vector2f(300,200))
	{
		createPauseText();
		rocketTexture.loadFromFile(filePath);
		m_player.setPosition(windowWidth / 2.f -100, windowHeight / 2.f);
		m_player2.setPosition(windowWidth / 2.f +100, windowHeight / 2.f);
		if (!twoPlayerGame)
		{
			m_player2.hide();
		}
		m_player.loadTexture();

		m_player2.loadTexture();

	}
	Game::~Game() {}

	void Game::createPauseText() {
		//m_font.loadFromFile("C:/oz/APL1/AdvancedProgramingLab1/lesson1/lesson1/textures/arial.ttf");
		m_font.loadFromFile("D:/study/colman/APL1/textures/arial.ttf");
		m_pauseText.setFillColor(sf::Color::White);
		m_pauseBackground.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black
		m_pauseBackground.setPosition(windowWidth / 2.f - m_pauseBackground.getSize().x / 2.f, windowHeight / 2.f - m_pauseBackground.getSize().y / 2.f);
		m_pauseText.setPosition(windowWidth / 2.f - m_pauseText.getLocalBounds().width / 2.f, windowHeight / 2.f - m_pauseText.getLocalBounds().height / 2.f);
	}
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
			m_player2.setPosition(windowWidth / 2.f + 100, windowHeight / 2.f);
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
			sf::Vector2f combinedStarDirection(0.f, 0.f);
			int playersMoving = 0;
			if(twoPlayerGame){
				m_player2.handleInput(m_inputHandler);
				m_player2.update(dt);

				if (m_player2.isMoving())
				{
					combinedStarDirection += -m_player2.getDirection();
					playersMoving++;
				}
			}
			if (m_player.isMoving())
			{
				combinedStarDirection += -m_player.getDirection();
				playersMoving++;
			}
			if (playersMoving > 0) {
				combinedStarDirection.x /= playersMoving;
				combinedStarDirection.y /= playersMoving;

				m_starsManager.update(dt, combinedStarDirection);
			}
		}
	}
	void Game::render() {
		m_window.clear(sf::Color::Black);
		m_starsManager.render(m_window);
		m_player.render(m_window);
		m_player2.render(m_window);
		if(pause){
			// Draw pause text
			m_window.draw(m_pauseBackground);
			m_window.draw(m_pauseText);
		}
		m_window.display();
	}

