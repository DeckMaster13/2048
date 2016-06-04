#ifndef __TEXTUREHANDLER__
#define __TEXTUREHANDLER__

#include <map>
#include <string>
#include "SDL.h"

class TextureHandler {
public:
	static void registerTexture(std::string textureID, SDL_Texture* texture);
	static std::map<std::string, SDL_Texture*>& getTexturesMap();
private:
	static std::map<std::string, SDL_Texture*> texturesMap;
};

#endif