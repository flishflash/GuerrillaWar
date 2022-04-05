#include "ModuleWindow.h"
#include "Globals.h"
#include <string>
#include "SDL/include/SDL.h"

bool ModuleWindow::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		LOG("SDL Initialization has failed.\n");
		LOG(SDL_GetError());
		LOG("\n");
		return false;
	};
	SDL_GetCurrentDisplayMode(0, &displayMode);
	if ((window = SDL_CreateWindow(
		"Chicken Flock",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		displayMode.w, displayMode.h,
		//SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE,
		SDL_WINDOW_HIDDEN
	)) == NULL) {
		LOG("Creation of the window has failed.\n");
		LOG(SDL_GetError());
		LOG("\n");
		return false;
	}
	LOG("Window fullscreen created with resolution: ");
	LOG(std::to_string(displayMode.w).c_str());
	LOG("px width - ");
	LOG(std::to_string(displayMode.h).c_str());
	LOG("px height.\n");
	SDL_ShowWindow(window);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//SDL_SetWindowOpacity(window, 0.5f);
	return true;
}
bool ModuleWindow::CleanUp() {
	SDL_DestroyWindow(window);
	LOG("Window destroyed.\n");
	SDL_Quit();
	LOG("SDL terminated.\n");
	return true;
}