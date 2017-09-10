#include "Rocket.h"

Rocket::Rocket(Planet* originPlanet)
	: Physics(50.f, TVector(0, 0), 10.f, true)
	, originPlanet(originPlanet)
{
	// visuals
	rocketSprite.setTexture(*TextureManager::getTexture("rocket"));
	rocketSprite.setScale(0.1f, 0.1f);
	rocketSprite.setOrigin(575, 1270);
	rocketSprite.setRotation(90);
	setTPosition(TVector(-10000, 10000));
}

void Rocket::update() {
	// set sfml position to physics position
	setPosition(Physics::getTPosition().x, Physics::getTPosition().y);
	Physics::update();

	// rotate shape
	setRotation(MiscMath::radToDeg(getVelocity().getArcTangent()));
}

// rotate rocket counter-clockwise
void Rocket::left() {
	angle = MiscMath::degToRad(getRotation());
	vel.x = cos(angle - MiscMath::getPI()/2.f) * (getVelocity().mag() / 60.f);
	vel.y = sin(angle - MiscMath::getPI()/2.f) * (getVelocity().mag() / 60.f);
	setVelocity(getVelocity() + vel);
}

// rotate rocket clockwise
void Rocket::right() {
	angle = MiscMath::degToRad(getRotation());
	vel.x = cos(angle - MiscMath::getPI()/2.f) * -1.f * (getVelocity().mag() / 60.f);
	vel.y = sin(angle - MiscMath::getPI()/2.f) * -1.f * (getVelocity().mag() / 60.f);
	setVelocity(getVelocity() + vel);
}

// accelerate rocket forwards
void Rocket::accelerate() {
	angle = MiscMath::degToRad(getRotation());
	vel.x = cos(angle) * 0.7f;
	vel.y = sin(angle) * 0.7f;
	if (getVelocity().mag() < 20.f)
		setVelocity(getVelocity() + vel);
}

// decelerate rocket
void Rocket::decelerate() {
	angle = getVelocity().getAngle();
	vel.x = cos(angle) * -0.3f;
	vel.y = sin(angle) * -0.3f;
	if (getVelocity().mag() > 0.5f)
		setVelocity(getVelocity() + vel);
}

// inherit sfml-based functionality
void Rocket::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply transform; getTransform() is defined by sf::Transformable
	states.transform *= getTransform();

	// draw the vertex array
	target.draw(rocketSprite, states);
}