#include "greenSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

greenSoldier::greenSoldier(int x, int y) : Enemy(x, y)
{
	//walk forward
	greenWalk.PushBack({});
}

void greenSoldier::Update()
{
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
