#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
struct SDL_Texture;
struct Collider;
class ModulePlayer : public Module {
	public:
		ModulePlayer();
		~ModulePlayer();
		bool Start() override;
		update_status Update() override;
		update_status PostUpdate() override;
		void OnCollision(Collider* c1, Collider* c2) override;
		void ShootLasers();
		iPoint position;
		int speed = 1;
		SDL_Texture* texture = nullptr;
		Animation* currentAnimation = nullptr;
		Animation idleAnim;
		Animation northAnim;
		Animation southAnim;
		Animation eastAnim;
		Animation westAnim;
		Animation northEastAnim;
		Animation northWestAnim;
		Animation southEastAnim;
		Animation southWestAnim;
		Animation downAnim;
		Animation WidleAnim;
		Animation WnorthAnim;
		Animation WsouthAnim;
		Animation WeastAnim;
		Animation WwestAnim;
		Animation WnorthEastAnim;
		Animation WnorthWestAnim;
		Animation WsouthEastAnim;
		Animation WsouthWestAnim;
		Animation WdownAnim;
		Collider* collider = nullptr;
		bool destroyed = false;
		uint destroyedCountdown = 60;
		int direction;
		uint score = 000;
		int scoreFont = -1;
		char scoreText[10] = { "\0" };
};
#endif //!__MODULE_PLAYER_H__