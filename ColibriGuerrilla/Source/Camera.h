#pragma once

#include <SDL/include/SDL_rect.h>
#include "Globals.h"
class Camera {
	SDL_Rect* rectCamara = new SDL_Rect({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 200, 200 });
	SDL_Rect* rectPlayer = new SDL_Rect({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, 20 });
	SDL_Rect* sumRect;
	virtual bool Start();
	update_status Update();

};

