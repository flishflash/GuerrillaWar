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
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_GreenSoldiers(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world

	// Enemy animations
	Animation southAnimGreen, back;
};
