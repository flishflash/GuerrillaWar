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
					if (event.key.keysym.sym == SDLK_F1) {
						App->state->god = !App->state->god;
					}
					if (event.key.keysym.sym == SDLK_F2) {
						App->state->debug = !App->state->debug;
					}
					if (event.key.keysym.sym == SDLK_F3) {
						App->scene->curScene = App->scene->winScreen;
						App->render->camera.y = 0;
						App->render->camera.x = 0;
						App->player->position.x = 0;
						App->player->position.y = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_F4) {
						App->scene->curScene = App->scene->loseScreen;
						App->render->camera.y = 0;
						App->render->camera.x = 0;
						App->player->position.x = 0;
						App->player->position.y = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_SPACE) {
						if(App->scene->curScene == App->scene->bgTexture) App->player->ShootLasers();
						if (App->scene->curScene == App->scene->credits ) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->hailHeroes;
							break;
						}
						if (App->scene->curScene == App->scene->hailHeroes) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->titleScreen;
							break;
						}
						if (App->scene->curScene == App->scene->winScreen) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->titleScreen;
							break;
						}
						if (App->scene->curScene == App->scene->loseScreen) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->titleScreen;
							break;
						}
						if (App->scene->curScene == App->scene->titleScreen) {
							App->scene->curScene = App->scene->bgTexture;
							App->render->camera.x = 125;
							App->render->camera.y = 3700;
							App->player->position.x = 235;
							App->player->position.y = 3950;
							// TO DO
						}
					}
					if (event.key.keysym.sym == SDLK_RETURN) {
						if (App->scene->curScene == App->scene->credits) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->hailHeroes;
							break;
						}
						if (App->scene->curScene == App->scene->hailHeroes) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->titleScreen;
							break;
						}
						if (App->scene->curScene == App->scene->winScreen) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->titleScreen;
							break;
						}
						if (App->scene->curScene == App->scene->loseScreen) {
							App->render->camera.y = 0;
							App->render->camera.x = 0;
							App->player->position.x = 0;
							App->player->position.y = 0;
							App->scene->curScene = App->scene->titleScreen;
							break;
						}
						if (App->scene->curScene == App->scene->titleScreen) {
							App->scene->curScene = App->scene->bgTexture;

							App->render->camera.x = 125;
							App->render->camera.y = 3700;
							App->player->position.x = 235;
							App->player->position.y = 3950;
							// TO DO
						}
					}
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
				if (App->scene->curScene == App->scene->credits) {
					App->render->camera.y = 0;
					App->render->camera.x = 0;
					App->player->position.x = 0;
					App->player->position.y = 0;
					App->scene->curScene = App->scene->hailHeroes;
					break;
				}
				if (App->scene->curScene == App->scene->hailHeroes) {
					App->render->camera.y = 0;
					App->render->camera.x = 0;
					App->player->position.x = 0;
					App->player->position.y = 0;
					App->scene->curScene = App->scene->titleScreen;
					break;
				}
				if (App->scene->curScene == App->scene->winScreen) {
					App->render->camera.y = 0;
					App->render->camera.x = 0;
					App->player->position.x = 0;
					App->player->position.y = 0;
					App->scene->curScene = App->scene->titleScreen;
					break;
				}
				if (App->scene->curScene == App->scene->loseScreen) {
					App->render->camera.y = 0;
					App->render->camera.x = 0;
					App->player->position.x = 0;
					App->player->position.y = 0;
					App->scene->curScene = App->scene->titleScreen;
					break;
				}
				if (App->scene->curScene == App->scene->titleScreen) {
					App->scene->curScene = App->scene->bgTexture;

					App->render->camera.x = 125;
					App->render->camera.y = 3700;
					App->player->position.x = 235;
					App->player->position.y = 3950;
					// TO DO
				}
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