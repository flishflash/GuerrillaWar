#pragma once
#include "Enemy.h"
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
struct SDL_Texture;
struct Collider;

class Enemy_GreenSoldiers : public Enemy
{
public:
	/* Constructor
	 Saves the spawn position for later movement calculations*/
	Enemy_GreenSoldiers(int x, int y);

	int speed = 1;
	void Update() override;

	Animation* currentAnimation = nullptr;
	Animation idleAnimGreen;
	Animation northAnimGreen;
	Animation southAnimGreen;
	Animation eastAnimGreen;
	Animation westAnimGreen;
	Animation northEastAnimGreen;
	Animation northWestAnimGreen;
	Animation southEastAnimGreen;
	Animation southWestAnimGreen;
	Animation downAnimGreen;
	Collider* collider = nullptr;
	bool destroyed = false;

	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

protected:

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};
