#include "TextureManager.h"

std::map<std::string, sf::Texture*> TextureManager::textures;
std::map<std::string, sf::Texture*>::iterator TextureManager::it;

TextureManager::TextureManager() {
}

bool TextureManager::addTexture(std::string fileName, std::string imageName) {
	// check if texture already exists
	if (textures.find(imageName) != textures.end()) {
		std::cout << "ERROR '" + fileName + "' image already exists" << std::endl;
		return false;
	}

	// check if image successfully loaded
	sf::Texture* newTexture = new sf::Texture();
	if (!newTexture->loadFromFile(fileName)) {
		std::cout << "ERROR loading '" + fileName + "' image" << std::endl;
		return false;
	}
	textures[imageName] = newTexture;
	return true;
}

sf::Texture* TextureManager::getTexture(std::string imageName) {
	it = textures.find(imageName);
	if (it == textures.end()) {
		std::cout << "ERROR '" + imageName + "' image does not exist" << std::endl;
		return nullptr;
	}
	return it->second;
}

void TextureManager::removeTexture(std::string imageName) {
	textures.erase(imageName);
}