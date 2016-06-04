#include "TextureHandler.h"
#include <iostream>

std::map<std::string, SDL_Texture*> TextureHandler::texturesMap;// = std::map<std::string, SDL_Texture*>();

void TextureHandler::registerTexture(std::string textureID, SDL_Texture* texture)
{
	TextureHandler::getTexturesMap()[textureID] = texture;
}

std::map<std::string, SDL_Texture*>& TextureHandler::getTexturesMap()
{
	return texturesMap;
}