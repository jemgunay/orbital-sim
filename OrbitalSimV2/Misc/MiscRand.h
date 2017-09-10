// collection of random based methods
#include <random>
#include <SFML\Graphics\Color.hpp>
#include "MiscMath.h"

class MiscRand
{
public:
	/* Random methods */
	// seed PRNG
	static void seedRandom() {
		srand(time(0));
	}
	// get random integer between two values
	static int getRandomRange(int lowest, int highest) {
		return lowest + (rand() % (int)(highest - lowest + 1));
	}
	// get random float between two values
	static float getRandomRange(float lowest, float highest) {
		float random = ((float) rand()) / (float) RAND_MAX;
		return lowest + (random * (highest - lowest));
	}
	// get a random boolean
	static bool getRandomBool() {
		if (getRandomRange(0, 1) == 0) return false;
		else return true;
	}
	// get a random sf::color
	static sf::Color getRandomColor(int alpha) {
		return sf::Color(getRandomRange(0, 225), getRandomRange(0, 225), getRandomRange(0, 225), alpha);
	}

	// get a random angle as float
	static float getRandomAngle() {
		return getRandomRange(0.f, MiscMath::getPI()*2.f);
	}
};