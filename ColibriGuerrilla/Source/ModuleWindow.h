#ifndef __MODULE_WINDOW_H__
#define __MODULE_WINDOW_H__
#include "Module.h"
#include "SDL/include/SDL_video.h"

class ModuleWindow : public Module {
	public:
		SDL_Window* window = nullptr;
		SDL_DisplayMode displayMode;
		bool Init() override;
		bool CleanUp() override;
};

#endif // !__MODULE_WINDOW_H__