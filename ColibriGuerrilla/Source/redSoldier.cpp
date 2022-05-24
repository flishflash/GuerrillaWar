#include "redSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"

redSoldier::redSoldier(int x, int y) : Enemy(x, y)
{
	front.PushBack({577,0,27,54});
	front.PushBack({607,1,30,54});
	front.PushBack({640,0,28,54});
	front.PushBack({674,0,25,54});
	front.loop = true;
	front.speed = 0.1f;
	currentAnim = &front;

	back.PushBack({ 577,237,27,54 });
	back.PushBack({ 607,238,30,54 });
	back.PushBack({ 640,237,28,54 });
	back.PushBack({ 674,237,25,54 });
	back.loop = true;
	back.speed = 0.1f;

	path.PushBack({ 0, -1.2f }, 150, &back);
	path.PushBack({ 0, 1.2f }, 150, &front);

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void redSoldier::Update()
{
	path.Update();
	positionenemy = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
