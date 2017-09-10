#include "Simulation.h"

Simulation::Simulation() {
	// background texture
	TextureManager::addTexture("images/sky.jpg", "sky");
	TextureManager::getTexture("sky")->setRepeated(true);
	skySprite.setTextureRect(sf::IntRect(0, 0, 100000, 100000));
	skySprite.setOrigin(sf::Vector2f(50000, 50000));

	// planet textures
	TextureManager::addTexture("images/glow.png", "glow");
	TextureManager::getTexture("glow")->setSmooth(true);

	for (int i = 1; i < 6; i++) {
		std::string imageName = "planet_terrain_" + std::to_string(i);
		TextureManager::addTexture("images/planet_terrain_" + std::to_string(i) + ".jpg", imageName);
		TextureManager::getTexture(imageName)->setRepeated(true);
		TextureManager::getTexture(imageName)->setSmooth(true);
	}

	// create galaxies and containing planets
	createGalaxy(TVector(12000.f, -8000.f));
	createGalaxy(TVector(-14000.f, 7000.f));
	createGalaxy(TVector(14000.f, 20000.f));
	
	// rocket
	TextureManager::addTexture("images/rocket.png", "rocket");
	rocket = new Rocket(planets[0]);
	// starting spin
	rocket->applyImpulse(TVector(500.f, -500.f));
}

void Simulation::createGalaxy(TVector centrePosition) {
	// spawn initial planets
	// large centre planet
	Planet* newPlanet = new Planet(500, 50, centrePosition, true);
	planets.push_back(newPlanet);

	// small planets
	for (int i = 0; i < 35; i++) {
		float angle = MiscRand::getRandomAngle();
		float distance = MiscRand::getRandomRange(6000, 16000);
		TVector pos(distance * sin(angle), distance * cos(angle));

		newPlanet = new Planet(MiscRand::getRandomRange(10, 100), 5, TVector(centrePosition.x - pos.x, centrePosition.y - pos.y), true);
		planets.push_back(newPlanet);
		TVector impulse(sqrt(distance) * sin(angle + MiscMath::degToRad(90)), sqrt(distance) * cos(angle + MiscMath::degToRad(90)));
		newPlanet->applyImpulse(impulse * newPlanet->getMass() * 0.05f);
	}
}

void Simulation::update() {
	for (int i = 0; i < planets.size(); i++) {
		// manage interactions between planets
		for (int j = 0; j < planets.size(); j++) {
			// cannot compare planet to itself
			if (i == j) continue;

			// check if physics objects are colliding, update based on collision
			planets[i]->handleCollision(planets[j]);
			// simulate gravitational pull between planets
			planets[i]->handleGravitation(planets[j]);
		}

		// manage collisions between planets & rocket
		planets[i]->handleCollision(rocket);
		rocket->handleCollision(planets[i]);
		// gravitational pull between rocket & planet
		planets[i]->handleGravitation(rocket);
		rocket->handleGravitation(planets[i]);
	
	}

	for (auto &p : planets) {
		p->update();
	}

	rocket->update();
}

void Simulation::draw(sf::RenderWindow& window) {
	// draw sky
	skySprite.setTexture(*TextureManager::getTexture("sky"));
	window.draw(skySprite);
	
	// draw planets and rocket
	for (auto &p : planets) {
		window.draw(*p);
	}

	window.draw(*rocket);
}

Simulation::~Simulation() {
	/*for (auto &it:planets) {
		delete it;
	}
	planets.clear();
	*/
	delete rocket;
}