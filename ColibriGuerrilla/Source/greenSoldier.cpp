#include "greenSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

greenSoldier::greenSoldier(int x, int y) : Enemy(x, y)
{
	//walk forward
	greenWalk.PushBack({0, 0, 26, 55});
	greenWalk.PushBack({32, 0, 26, 55});
	greenWalk.PushBack({64, 0, 26, 55});
	greenWalk.PushBack({96, 0, 26, 55});
	greenWalk.PushBack({126, 0, 26, 55});
	greenWalk.loop = true;
	greenWalk.speed = 0.1f;

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY);
}

void greenSoldier::Update()
{
	currentAnim = &greenWalk;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
