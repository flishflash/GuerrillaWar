#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
struct SDL_Texture;
struct Collider;
class ModuleCamera : public Module {
public:
	ModuleCamera();
	~ModuleCamera();
	bool Start() override;
	update_status Update() override;
	update_status PostUpdate() override;
	iPoint position;
	int speed = 1;
	SDL_Texture* texture = nullptr;
	Animation* currentAnimation = nullptr;
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Collider* collider = nullptr;
	bool destroyed = false;
	uint destroyedCountdown = 120;
};
#endif //!__MODULE_PLAYER_H__