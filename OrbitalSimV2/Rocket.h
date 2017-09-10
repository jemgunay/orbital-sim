#pragma once
#include <SFML\Graphics.hpp>
#include "Misc\TVector.h"
#include "Misc\MiscMath.h"
#include "Physics.h"
#include "TextureManager.h"
#include "Planet.h"

class Rocket : public Physics, public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite rocketSprite;
	TVector vel;
	float angle;

public:
	Planet* originPlanet;

	Rocket();
	Rocket(Planet* originPlanet);

	void left();
	void right();
	void accelerate();
	void decelerate();

	void launch();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
};