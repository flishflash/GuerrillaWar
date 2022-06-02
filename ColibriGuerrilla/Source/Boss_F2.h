#ifndef __BOSS_F2_H__
#define __BOSS_F2_H__

#include "Enemy.h"
#include "Path.h"
class Boss_F2 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Boss_F2(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	Path path;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies

	int cooldown = 0;
};

#endif // __BOSS_F2_H__
