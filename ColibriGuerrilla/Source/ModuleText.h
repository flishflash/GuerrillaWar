#pragma once
#include <map>
#include <string>
#include "Globals.h"
#include "Module.h"
#include "SDL_ttf/include/SDL_ttf.h"
class ModuleText : public Module {
	public:
		bool Init() override;
		update_status Update() override;
		update_status PostUpdate() override;
		bool CleanUp() override;
		TTF_Font* get(std::string name, int size) { return fonts[name][size]; }
	protected:
		std::map<std::string, std::map<int, TTF_Font*>> fonts;
};

