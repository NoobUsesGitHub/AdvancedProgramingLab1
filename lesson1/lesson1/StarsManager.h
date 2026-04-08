#pragma once

#include <cmath>
#include <random>
#include <vector>
#include "Globals.h"
#include "Star.h"
class StarsManager
{
	public:
		StarsManager();
		~StarsManager();
		void update(float dt, sf::Vector2f playerDirection);
		void render(sf::RenderWindow& window);
	private:
		std::vector<Star> m_stars;
		std::mt19937 m_gen;
};

