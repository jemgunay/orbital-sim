#pragma once
#include <SFML\Graphics.hpp>
#include "Planet.h"
#include "Rocket.h"
#include <vector>
#include "TextureManager.h"

class Simulation
{
private:
	std::vector<Planet*> planets;
	sf::Sprite skySprite;
	
public:
	Simulation();
	~Simulation();

	void createGalaxy(TVector centrePos);
	void update();
	void draw(sf::RenderWindow& window);

	Rocket* rocket;
};