#ifndef __BOSS_F1_H__
#define __BOSS_F1_H__

#include "Enemy.h"
#include "Path.h"

class Boss_F1 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Boss_F1(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	bool bossdied;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step

	Path path;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies

	Animation walkforward;
	Animation walkbackward;
	Animation walkleft;
	Animation walkright;

	int cooldown = 0;
	int cooldownspawn = 0;
	int cooldownmor = 0;

	int random;
};

#endif // __BOSS_F1_H__
