#include "PlanetPolygon.h"

PlanetPolygon::PlanetPolygon(const float& radius) {
	int vertexCount = MiscRand::getRandomRange(10, 15);
	float angleSize = (MiscMath::getPI() * 2.f) / vertexCount;
	
	vertices = sf::VertexArray(sf::TrianglesFan, vertexCount);

	float radiusVariation;
	// create warped shape for planet
	for (int i = 0; i < vertexCount; i++) {
		radiusVariation = MiscRand::getRandomRange(radius * 0.8f, radius * 1.2f);
		// shape position
		vertices[i].position = sf::Vector2f(radius, radius) + sf::Vector2f(cos(angleSize * i) * radiusVariation, sin(angleSize * i) * radiusVariation);
		vertices[i].texCoords = vertices[i].position;// + sf::Vector2f(20, 20);
	}
	setOrigin(sf::Vector2f(radius, radius));

	int imageNum = MiscRand::getRandomRange(1, 5);
	planetTextureName = "planet_terrain_" + std::to_string(imageNum);

	glowSprite.setTexture(*TextureManager::getTexture("glow"));
	glowSprite.setScale(sf::Vector2f(radius, radius) * 0.01f);
	glowSprite.setOrigin(sf::Vector2f(radius, radius));

}

// accessors
sf::VertexArray PlanetPolygon::getShape() { return vertices; }

std::string PlanetPolygon::getTexture() { return planetTextureName; }

// inherit sfml-based functionality
void PlanetPolygon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply transform; getTransform() is defined by sf::Transformable
	states.transform *= getTransform();

	//target.draw(glowSprite, states);

	// apply the texture
	states.texture = TextureManager::getTexture(planetTextureName);
	// draw the vertex array
	target.draw(vertices, states);


}