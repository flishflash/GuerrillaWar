#pragma once
#include "Module.h"
#include "SDL/include/SDL_events.h"
class ModuleInput : public Module {
	public:
		bool Init() override;
		update_status PreUpdate() override;
		bool CleanUp() override;
		const Uint8* keyboard;
		SDL_Event event;
};