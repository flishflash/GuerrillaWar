#ifndef __REDSOLDIER_H__
#define __REDSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class redSoldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	redSoldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//colllisions
	void OnCollision(Collider* collider) override;


private:
	// The path that will define the position in the world
	Path path;
	int cooldown = 0;
	int cooldown2 = 0;
	// Enemy animations
	Animation front, back;
};

#endif // __ENEMY_MECH_H__