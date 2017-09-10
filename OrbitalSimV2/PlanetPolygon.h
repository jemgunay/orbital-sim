#pragma once
#include <SFML\Graphics.hpp>
#include "Misc\MiscRand.h"
#include "Misc\MiscMath.h"
#include <iostream>
#include "TextureManager.h"

class PlanetPolygon: public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray vertices;
	std::string planetTextureName;
	sf::Sprite glowSprite;

public:
	PlanetPolygon() {}
	PlanetPolygon(const float& radius);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray getShape();
	std::string getTexture();
	
	std::string textureName;
};