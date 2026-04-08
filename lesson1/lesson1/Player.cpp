#include "Player.h"


Player::Player() :Player(PlayerType::Arrows) {
}
Player::Player(PlayerType type) :m_cell(0, 0, frameWidth, frameHeight), m_controls{} {
	m_type = type;
	if (type==PlayerType::WASD)
	{
		m_controls[0] = sf::Keyboard::W;//up
		m_controls[1] = sf::Keyboard::S;//down
		m_controls[2] = sf::Keyboard::A;//left
		m_controls[3] = sf::Keyboard::D;//right

		//WASD controls
	}
	else {
		m_controls[0] = sf::Keyboard::Up;//up
		m_controls[1] = sf::Keyboard::Down;//down
		m_controls[2] = sf::Keyboard::Left;//left
		m_controls[3] = sf::Keyboard::Right;//right
	}
}

Player::~Player() {}

void Player::loadTexture() {
	m_sprite.setTexture(rocketTexture);
	m_sprite.setTextureRect(m_cell);

	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	if(m_type==PlayerType::WASD)
	{
		m_sprite.setColor(sf::Color(100, 100, 100));
	}
}

void Player::handleInput(InputHandler& input) {
	m_velocity = sf::Vector2f(0, 0);
	if (input.isKeyPressed(m_controls[3])) {//right
		m_velocity.x = speed;
	}
	if (input.isKeyPressed(m_controls[0])) {//up
		m_velocity.y = -1 * speed;
	}
	if (input.isKeyPressed(m_controls[1])) {//down
		m_velocity.y = speed;
	}
	if (input.isKeyPressed(m_controls[2])) {//left
		m_velocity.x = speed * -1;
	}
	if (input.isKeyPressed(sf::Keyboard::LShift)) {//sprint
		m_velocity *= sprintMultiplier;
	}
}

bool Player::isMoving()
{
	return (m_velocity != sf::Vector2f(0.f, 0.f));
}

void Player::update(float dt) {
	//std::cout << "Player Position - X: " << m_sprite.getPosition().x << " | Y: " << m_sprite.getPosition().y << std::endl;
	//if moving
	if (isMoving()) {
		m_sprite.move(m_velocity * dt);

		// Calculate half the width/height to account for your centered origin
		float halfWidth = m_sprite.getLocalBounds().width / 2.f;
		float halfHeight = m_sprite.getLocalBounds().height / 2.f;
		sf::Vector2f currentPos = m_sprite.getPosition();

		// Left Wall
		if (currentPos.x - halfWidth < 0)
			currentPos.x = halfWidth;
		// Right Wall
		else if (currentPos.x + halfWidth > windowWidth)
			currentPos.x = windowWidth - halfWidth;

		// Top Wall
		if (currentPos.y - halfHeight < 0)
			currentPos.y = halfHeight;
		// Bottom Wall
		else if (currentPos.y + halfHeight > windowHeight)
			currentPos.y = windowHeight - halfHeight;

		// Apply the corrected position once at the end!
		m_sprite.setPosition(currentPos);
	}

	if (m_velocity.x != 0.f || m_velocity.y != 0.f)
	{
		rotation = std::atan2(m_velocity.y, m_velocity.x) * 180.f / 3.14159265f;
	}
	
	m_animationTimer += dt;

	if (m_animationTimer >= 0.12f)
	 {
	 	frame = (frame + 1) % totalFrames;

	 	int col = frame % columns;
	 	int row = frame / columns;

	 	m_cell.left = col * frameWidth;
	 	m_cell.top = row * frameHeight;

	 	m_sprite.setTextureRect(m_cell);
	 	sf::FloatRect bounds = m_sprite.getLocalBounds();
	 	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	 	m_sprite.setRotation(rotation + 90.f);
	 	m_animationTimer = 0.f;
	 }
}
void Player::hide() {
	isHidden = true;
}
	
void Player::render(sf::RenderWindow& window) {
	if (!isHidden)
	{
		window.draw(m_sprite);
	}
}

sf::Vector2f Player::getDirection() {
	float angleRad = rotation * 3.14159265f / 180.f;
	return sf::Vector2f(std::cos(angleRad), std::sin(angleRad));
}

void Player::setPosition(float x, float y) {
	m_sprite.setPosition(x, y);
}