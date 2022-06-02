#ifndef __BOSS_SOLDIER_H__
#define __BOSS_SOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Boss_Soldiers : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Boss_Soldiers(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//colllisions
	void OnCollision(Collider* collider) override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	Path path;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies

	Animation greenshot;
	Animation greenWalkL;
	Animation greenWalkR;
	Animation greenDie;
	int cooldown = 0;
};

#endif // __BOSS_SOLDIER_H__