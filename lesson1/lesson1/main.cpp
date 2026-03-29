#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <iostream>
#include "Star.h" 
int main()
{
	const int windowWidth = 1400;
	const int windowHeight = 1600;
	const int frameWidth = 200;
	const int frameHeight = 207;
    sf::Texture texture;
    //texture.loadFromFile("D:/study/colman/APL1/textures/rokcetSpritesheet.png");
    texture.loadFromFile("C:/oz/APL1/AdvancedProgramingLab1/lesson1/lesson1/textures/rokcetSpritesheet.png");
	const int numberOfStars = 500;

	int frame = 0;
	const int columns = 4;
	const int totalFrames = 8; 


    //to do - change size and wall colission

	int rocketPlayerSize = 200;
    sf::IntRect cell(0, 0, frameWidth,frameHeight);
	sf::Sprite rocketPlayer(texture, cell);
    std::vector<Star> stars;
    std::random_device rd;
    std::mt19937 gen(rd());
	for (int i = 0; i < numberOfStars; ++i)
	    stars.push_back(Star(windowWidth*1.5, windowHeight*1.5,gen ));

	rocketPlayer.setPosition(windowWidth / 2.f, windowHeight / 2.f);
    sf::FloatRect bounds = rocketPlayer.getLocalBounds();
    rocketPlayer.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML lesson1");
    
	float rotation = 0.f;
	sf::Clock clock;
    sf::Clock animateClock;
	bool colursOn = false;
    float dt;
	float speed = 200.f;
	sf::Vector2f rocketPlayerPos = rocketPlayer.getPosition();
	bool isMoving = false;

	sf::Vector2f direction = sf::Vector2f(0, 0);
    sf::Vector2f rocketPlayerOrigin = rocketPlayer.getPosition();

	while (window.isOpen())
    {
        // --- Event handling ---
        sf::Event event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {//quick close
            window.close();
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		// --- Update ---

		isMoving = false;
        sf::Vector2f rocketPlayerPos= sf::Vector2f(0,0);
        rocketPlayerOrigin = rocketPlayer.getPosition();
        sf::Color color(0, 0, 0);
		dt = clock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {//right
			rocketPlayerPos.x = speed * dt;
            isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {//up
            rocketPlayerPos.y = -1 * speed * dt;
            if (colursOn)
            {
                color.b = 0;
            }
            isMoving = true;
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {//down
            rocketPlayerPos.y = speed * dt;
            if (colursOn)
            {
                color.b = 255;
            }
            isMoving = true;
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {//left
            rocketPlayerPos.x = speed * dt* -1;
            if(colursOn)
            {
                color.r = 0;
            }
            isMoving = true;
        }
        if (isMoving) {
            // 1. The direction the rocket is going is simply its movement delta.
            // 2. To create parallax, stars move opposite to the rocket.
            // 3. Multiply by a parallax factor (e.g., 0.5f) so the background moves slower than the foreground.

            float parallaxFactor = 0.5f;

            // Reverse the vector and scale it down
            direction.x = -rocketPlayerPos.x * parallaxFactor;
            direction.y = -rocketPlayerPos.y * parallaxFactor;

            std::cout << "Star move delta: (" << direction.x << ", " << direction.y << ")\n";

            // Now actually move the stars!
			for (Star& star : stars)
                star.starMove(direction,dt);
        }

		//colision checking and position update
        if (isMoving) {
            rocketPlayer.move(rocketPlayerPos);
			//std::cout << "rocketPlayer position: (" << rocketPlayer.getPosition().x << ", " << rocketPlayer.getPosition().y << ")/n"<< std::endl;

            if (rocketPlayer.getPosition().x < 0)
                rocketPlayer.setPosition(0, rocketPlayer.getPosition().y);

            if (rocketPlayer.getPosition().y < 0)
                rocketPlayer.setPosition(rocketPlayer.getPosition().x, 0);

            if (rocketPlayer.getPosition().y + (rocketPlayerSize / 2) > windowHeight)
                rocketPlayer.setPosition(rocketPlayer.getPosition().x, windowHeight - (rocketPlayerSize / 2));
            
            if (rocketPlayer.getPosition().x + (rocketPlayerSize / 2) > windowWidth)
                rocketPlayer.setPosition(windowWidth - (rocketPlayerSize / 2), rocketPlayer.getPosition().y);
        }
        
        if (rocketPlayerPos.x != 0.f || rocketPlayerPos.y != 0.f)
        {
            rotation = std::atan2(rocketPlayerPos.y, rocketPlayerPos.x) * 180.f / 3.14159265f;
        }

        if (animateClock.getElapsedTime().asSeconds() > 0.12f) {
            frame = (frame + 1) % totalFrames;

            int col = frame % columns;
            int row = frame / columns;

            cell.left = col * frameWidth;
            cell.top = row * frameHeight;
            
            
            rocketPlayer.setTextureRect(cell);
            sf::FloatRect bounds = rocketPlayer.getLocalBounds();
            rocketPlayer.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            rocketPlayer.setRotation(rotation+90.f);
            animateClock.restart();
        }
		//--- Render ---
        window.clear(color);
		for (Star& star : stars)
            window.draw(star);
        window.draw(rocketPlayer);
        window.display();
    }

    return 0;
}