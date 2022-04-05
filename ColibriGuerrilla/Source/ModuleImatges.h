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
		SDL_Texture* get(std::string name) { return mapa[name]; }
	protected:
		std::map<std::string, SDL_Texture*> mapa;
};

