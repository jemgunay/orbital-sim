#include "Physics.h"

Physics::Physics(const float& radius, const TVector& pos, const float& density, const bool& dynamic)
	: radius(radius), density(density), pos(pos), dynamic(dynamic), vel(0.f, 0.f), angularVel(0.f)
{
	mass = radius * density;
}

void Physics::update() {
	pos += vel;
}

void Physics::applyImpulse(TVector force) {
	if (force.x != 0) vel.x += (force.x / mass);
	if (force.y != 0) vel.y += (force.y / mass);
}

// accessor methods
float Physics::getRadius() {
	return radius;
}

float Physics::getMass() {
	return mass;
}

float Physics::getDensity() {
	return density;
}

// return physics based pos, not sfml pos
TVector Physics::getTPosition() {
	return pos;
}

void Physics::setTPosition(TVector& pos) {
	this->pos = pos;
}

// vel accessors
TVector Physics::getVelocity() {
	return vel;
}

void Physics::setVelocity(TVector& vel) {
	this->vel = vel;
}

float Physics::getAngularVelocity() {
	return this->angularVel;
}

void Physics::setAngularVelocity(float angularVelocity) {
	this->angularVel = angularVelocity;
}

void Physics::handleCollision(Physics* other) {
	TVector distance = this->getTPosition() - other->getTPosition();
	float mag = distance.mag();

	if (mag < (this->getRadius() + other->getRadius())) {
		// get angle
		float theta = distance.getArcTangent();
		float sine = sin(theta);
		float cosine = cos(theta);

		TVector bTemp[2];
		bTemp[1].x  = cosine * distance.x + sine * distance.y;
		bTemp[1].y  = cosine * distance.y - sine * distance.x;

		TVector vTemp[2];
		vTemp[0].x = cosine * this->getVelocity().x + sine * this->getVelocity().y;
		vTemp[0].y = cosine * this->getVelocity().y - sine * this->getVelocity().x;
		vTemp[1].x = cosine * other->getVelocity().x + sine * other->getVelocity().y;
		vTemp[1].y = cosine * other->getVelocity().y - sine * other->getVelocity().x;

		TVector vFinal[2];
		// final rotated velocity for b[0]
		vFinal[0].x = ((this->getMass() - other->getMass()) * vTemp[0].x + 2.f * other->getMass() * vTemp[1].x) / (this->getMass() + other->getMass());
		vFinal[0].y = vTemp[0].y;

		// final rotated velocity for b[0]
		vFinal[1].x = ((other->getMass() - this->getMass()) * vTemp[1].x + 2.f * this->getMass() * vTemp[0].x) / (this->getMass() + other->getMass());
		vFinal[1].y = vTemp[1].y;

		// hack to avoid clumping
		bTemp[0].x += vFinal[0].x;
		bTemp[1].x += vFinal[1].x;

		TVector bFinal1, bFinal2;
		bFinal1.x = cosine * bTemp[0].x - sine * bTemp[0].y;
		bFinal1.y = cosine * bTemp[0].y + sine * bTemp[0].x;
		bFinal2.x = cosine * bTemp[1].x - sine * bTemp[1].y;
		bFinal2.y = cosine * bTemp[1].y + sine * bTemp[1].x;

		// update balls to screen position
		TVector newPosition;
		newPosition.x = this->getTPosition().x + bFinal2.x;
		newPosition.y = this->getTPosition().y + bFinal2.y;
		other->setTPosition(newPosition);

		this->setTPosition(this->getTPosition() + bFinal1);

		// update velocities
		TVector newVelocity;
		newVelocity.x = cosine * vFinal[0].x - sine * vFinal[0].y;
		newVelocity.y = cosine * vFinal[0].y + sine * vFinal[0].x;
		this->setVelocity(newVelocity);
				
		TVector newVelocity2;
		newVelocity2.x = cosine * vFinal[1].x - sine * vFinal[1].y;
		newVelocity2.y = cosine * vFinal[1].y + sine * vFinal[1].x;
		other->setVelocity(newVelocity2);
	}
}

// apply gravitational pull between objects
void Physics::handleGravitation(Physics* other) {
	if (this->dynamic == false) return;

	TVector distance = this->getTPosition() - other->getTPosition();
	float mag = distance.mag();
	TVector direction = distance;
	direction.normalise();

	// strength of gravitational pull f = m1 * m2 / r^2
	float strength = (other->getMass() * this->getMass()) / pow(distance.mag(), 2) * 4.5f;
	this->applyImpulse(direction * strength);
}