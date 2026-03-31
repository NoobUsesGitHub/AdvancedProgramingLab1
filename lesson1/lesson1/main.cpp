#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <iostream>
#include "Star.h" 
int main()
{
	const int windowWidth = 1400;
	const int windowHeight = 1000;
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
    std::uniform_real_distribution<float> disX(0.f, windowWidth);
    std::uniform_real_distribution<float> disY(0.f, windowHeight);
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

            //std::cout << "Star move delta: (" << direction.x << ", " << direction.y << ")\n";

            for (Star& star : stars) {
                star.starMove(direction, dt);

                sf::Vector2f pos = star.getPosition();
                bool outOfBounds = false;

                // Left edge -> Respawn on the Right edge, random Y
                if (pos.x < 0) {
                    pos.x = windowWidth;
                    pos.y = disY(gen);
                    outOfBounds = true;
                }
                // Right edge -> Respawn on the Left edge, random Y
                else if (pos.x > windowWidth) {
                    pos.x = 0;
                    pos.y = disY(gen);
                    outOfBounds = true;
                }

                // Top edge -> Respawn on the Bottom edge, random X
                if (pos.y < 0) {
                    pos.x = disX(gen);
                    pos.y = windowHeight;
                    outOfBounds = true;
                }
                // Bottom edge -> Respawn on the Top edge, random X
                else if (pos.y > windowHeight) {
                    pos.x = disX(gen);
                    pos.y = 0;
                    outOfBounds = true;
                }

                // Apply the new position if it went off screen
                if (outOfBounds) {
                    star.setPosition(pos.x, pos.y);
                }
            }
        }
        // Collision checking and position update
        if (isMoving) {
            rocketPlayer.move(rocketPlayerPos);

            // Calculate half the width/height to account for your centered origin
            float halfWidth = rocketPlayer.getLocalBounds().width / 2.f;
            float halfHeight = rocketPlayer.getLocalBounds().height / 2.f;
            sf::Vector2f currentPos = rocketPlayer.getPosition();

            // Left Wall
            if (currentPos.x - halfWidth < 0)
                rocketPlayer.setPosition(halfWidth, currentPos.y);

            // Right Wall
            if (currentPos.x + halfWidth > windowWidth)
                rocketPlayer.setPosition(windowWidth - halfWidth, currentPos.y);

            // Top Wall
            if (currentPos.y - halfHeight < 0)
                rocketPlayer.setPosition(currentPos.x, halfHeight);

            // Bottom Wall
            if (currentPos.y + halfHeight > windowHeight)
                rocketPlayer.setPosition(currentPos.x, windowHeight - halfHeight);
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