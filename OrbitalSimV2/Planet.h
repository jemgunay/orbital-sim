#pragma once
#include <SFML\Graphics.hpp>
#include "Misc\TVector.h"
#include "PlanetPolygon.h"
#include "Physics.h"

class Planet : public PlanetPolygon,  public Physics
{
private:

public:
	Planet(float radius, float density, TVector pos);
	Planet(float radius, float density, TVector pos, bool dynamic);

	void update();
};