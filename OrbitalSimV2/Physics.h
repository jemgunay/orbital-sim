#pragma once
#include "Misc\TVector.h"

class Physics
{
private:
	float radius, mass, density;
	TVector pos, vel;
	float angularVel;
	
public:
	bool dynamic;

	Physics() {}
	Physics(const float& radius, const TVector& pos, const float& density, const bool& dynamic);

	void update();
	void applyImpulse(TVector force);
	void handleCollision(Physics* other);
	void handleGravitation(Physics* other);

	float getRadius();
	float getMass();
	float getVolume();
	float getDensity();

	void setTPosition(TVector& pos);
	TVector getTPosition();

	void setVelocity(TVector& vel);
	TVector getVelocity();
	float getAngularVelocity();
	void setAngularVelocity(float angularVelocity);
};