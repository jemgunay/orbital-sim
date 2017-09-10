#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class TextureManager
{
public:
	TextureManager();
	static bool addTexture(std::string fileName, std::string imageName);
	static sf::Texture* getTexture(std::string imageName);
	static void removeTexture(std::string imageName);

private:
	static std::map<std::string, sf::Texture*> textures;
	static std::map<std::string, sf::Texture*>::iterator it;

};