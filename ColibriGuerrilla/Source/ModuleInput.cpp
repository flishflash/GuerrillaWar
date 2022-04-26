#include "ModuleInput.h"
#include "Application.h"
#include "ModulePlayer.h"
bool ModuleInput::Init() {
    keyboard = SDL_GetKeyboardState(NULL);
    return true;
}
update_status ModuleInput::PreUpdate() {
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			case SDL_QUIT:
				return update_status::UPDATE_STOP;
			case SDL_KEYDOWN:
				if (!event.key.repeat) {
					if (event.key.keysym.sym == SDLK_ESCAPE){}
					/*if (event.key.keysym.sym == SDL_SCANCODE_F1) App->state->god = !App->state->god;*/
					if (event.key.keysym.sym == SDLK_SPACE) App->player->ShootLasers();
					//if (event.key.keysym.sym == SDLK_b) App->player->SpawnExplosions();
				}
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_LEAVE) {}
				if (event.window.event == SDL_WINDOWEVENT_ENTER) {}
				break;
			case SDL_MOUSEMOTION:
				//SDL_GetMouseState(&mouse->x, &mouse->y);
				break;
			case SDL_MOUSEBUTTONUP:
				//isClicking = true;
				break;
		}
		if (keyboard[SDL_SCANCODE_ESCAPE]) return update_status::UPDATE_STOP;
	}
    return update_status::UPDATE_CONTINUE;
}
bool ModuleInput::CleanUp() {
    keyboard = nullptr;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return true;
}