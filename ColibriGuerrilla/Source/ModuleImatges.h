#pragma once
#include "Module.h"
#include <string>
#include <map>
#include "SDL/include/SDL_Render.h"
class ModuleImatges : public Module {
	public:
		bool CleanUp() override;
		bool loadIMGs();
		bool Init() override;
		bool get(std::string, SDL_Texture*&);
		SDL_Texture* get(std::string);
	protected:
		std::map<std::string, SDL_Texture*> mapa;
};

