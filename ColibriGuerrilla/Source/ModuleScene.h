#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL/include/SDL_Render.h"
class ModuleScene : public Module {
	public:
		ModuleScene();
		~ModuleScene();
		bool Start() override;
		update_status Update() override;
		update_status PostUpdate() override;
		void pintarPalmeras();
		SDL_Texture* bgTexture;
		SDL_Texture* palmeras;
};
#endif