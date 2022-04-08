#pragma once
#include "Module.h"
#include <vector>
#include <string>
#include "SDL/include/SDL_Render.h"
#include "SDL/include/SDL_Rect.h"
class ModuleRender : public Module {
	public:
		bool Init() override;
		update_status PreUpdate() override;
		update_status Update() override;
		update_status PostUpdate() override;
		bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section = nullptr, float speed = 1.0f);
		bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed = 1.0f);
		bool CleanUp() override;
		SDL_Renderer* renderer = nullptr;
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		// The speed at which the camera will be moving
		int cameraSpeed = 3;
};