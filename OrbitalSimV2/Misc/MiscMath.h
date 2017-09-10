// collection of useful functions
#pragma once
#include <string>

class MiscMath
{
public:
	/* Angle based methods */
	// get pi as a float
	static float getPI() {
		return 3.14159265358979f;
	}
	// convert radians to degrees
	static float radToDeg(float radians) {
		return radians * (180.f / getPI());
	}
	// convert degrees to radians
	static float degToRad(float degrees) {
		return degrees * (getPI() / 180.f);
	}
};