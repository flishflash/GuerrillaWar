#include "redSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

redSoldier::redSoldier(int x, int y) : Enemy(x, y)
{
	
}

void redSoldier::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
