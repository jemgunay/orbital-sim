#include "MainManager.h"

MainManager::MainManager()
	: stepTick(1.f/60.f),
	window(sf::RenderWindow(sf::VideoMode(800, 700), "OrbitalSimV2")),
	hasFocus(true),
	zoom(14.0f)
{
	// init window & view
	window.setFramerateLimit(60);
	view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
	view.setSize(sf::Vector2f(window.getSize()));
	view.zoom(zoom);
	MiscRand::seedRandom();

	mainLoop();
}

// simulation loop
void MainManager::mainLoop() {
	while (window.isOpen()) {
		// poll events
		handleInput();

		// limit update rate to 30 times/s
		if (clock.getElapsedTime().asMilliseconds() >= stepTick) {
			clock.restart();
			handleKeyboard();
			sim.update();
		}
		// draw objects
		view.setCenter(sim.rocket->getPosition());
		view.setRotation(sim.rocket->getRotation() + 90.f);
		window.setView(view);
		window.clear(sf::Color::Color(2, 0, 0, 255));
		sim.draw(window);
		window.display();
	}
}

// on event handling
void MainManager::handleInput() {
	sf::Event e;
	
	while (window.pollEvent(e)) {
		// window events
		if (e.type == sf::Event::Closed) {
			window.close();
		}
		else if(e.type == sf::Event::GainedFocus)
			hasFocus = true;
		else if(e.type == sf::Event::LostFocus)
			hasFocus = false;
		// input events
		else if (e.type == sf::Event::KeyPressed) {
			if (e.key.code == sf::Keyboard::Space) {
				
			}
		}
		else if (e.type == sf::Event::MouseMoved) {

		}
		else if (e.type == sf::Event::Resized) {
			view.setSize(e.size.width, e.size.height);
			view.zoom(zoom);
		}
	}
}

// instant keyboard polling
void MainManager::handleKeyboard() {
	// window not in focus, ignore input
	if (hasFocus == false)
		return;
	
	// rocket movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sim.rocket->accelerate();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sim.rocket->decelerate();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sim.rocket->left();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sim.rocket->right();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		sim.rocket->accelerate();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		sim.rocket->decelerate();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		sim.rocket->left();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		sim.rocket->right();
	}

	// zoom
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		view.zoom(0.99f);
		zoom * 0.99f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		view.zoom(1.01f);
		zoom *= 1.01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
	}
}