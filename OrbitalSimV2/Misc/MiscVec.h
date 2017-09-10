// collection of sf::Vector2 based methods
#include <SFML\System\Vector2.hpp>
#include <SFML\Window.hpp>
#include "MiscRand.h"
#include "TVector.h"

class MiscVec
{
public:
	/* Random vector methods */
	// get random vector
	static sf::Vector2f getRandomVector(int x, int x2, int y, int y2) {
		return sf::Vector2f(float(MiscRand::getRandomRange(x, x2)), float(MiscRand::getRandomRange(y, y2)));
	}
	// get random vector point from a rect area
	static sf::Vector2f getRandomWindowPoint(const sf::Window& w) {
		return sf::Vector2f(float(MiscRand::getRandomRange(0, w.getSize().x)), float(MiscRand::getRandomRange(0, w.getSize().y)));
	}
	static TVector toTVector(const sf::Vector2f& vec) {
		return TVector(vec.x, vec.y);
	}
};