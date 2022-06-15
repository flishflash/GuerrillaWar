#ifndef __GREENSOLDIER_H__
#define __GREENSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class greenSoldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	greenSoldier(int x, int y);

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
	Animation greenWalkbackward;
	Animation greenWalkshot;
	Animation greenWalk;
	int cooldown = 0;
	int cooldown2 = 0;
	int cooldown3 = 0;
	int comp;
};

#endif // __GREENSOLDIER_H__