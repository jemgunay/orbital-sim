#include "Planet.h"

Planet::Planet(float radius, float density, TVector pos) {
	// default dynamic to true
	Planet(radius, density, pos, true);
}

Planet::Planet(float radius, float density, TVector pos, bool dynamic)
	: PlanetPolygon(radius),
	Physics(radius, pos, density, dynamic)
{
	// visuals
	setAngularVelocity(MiscRand::getRandomRange(0.f, 1.f));
	
}

void Planet::update() {
	// set sfml Pos to physics Pos
	PlanetPolygon::setPosition(Physics::getTPosition().x, Physics::getTPosition().y);
	Physics::update();
	// TODO: rotate shape
	PlanetPolygon::setRotation(getRotation() + getAngularVelocity());
}