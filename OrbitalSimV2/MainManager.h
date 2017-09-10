#pragma once
#include <iostream>
#include "Simulation.h"

class MainManager
{
private:
	// window/rates
	sf::RenderWindow window;
	sf::View view;
	float zoom;
	bool hasFocus;
	sf::Clock clock;
	float stepTick;

	void mainLoop();
	void handleInput();
	void handleKeyboard();

public:
	Simulation sim;

	MainManager();

};