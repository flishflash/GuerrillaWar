#include "recluso.h"

#include "Application.h"
#include "ModuleCollisions.h"

recluso::recluso(int x, int y) : pickUp(x, y)
{
	//walk forward
	normalAnim.PushBack({ 8, 0, 19, 56 });
	normalAnim.PushBack({ 40, 0, 19, 56 });
	normalAnim.PushBack({ 72, 0, 20, 56 });
	normalAnim.PushBack({ 103, 0, 20, 56 });
	normalAnim.loop = true;
	normalAnim.speed = 0.1f;

	currentAnim = &normalAnim;

	rescuedAnim.PushBack({ 5, 74, 26, 45 });
	rescuedAnim.PushBack({ 38, 69, 24, 50 });
	rescuedAnim.PushBack({ 65, 63, 31, 58 });
	rescuedAnim.speed = 0.1f;

	deathAnim.PushBack({ 0, 237, 27, 55 });
	deathAnim.PushBack({ 32, 237, 26, 55 });
	deathAnim.PushBack({ 64, 237, 26, 55 });
	deathAnim.PushBack({ 64, 237, 26, 55 });
	deathAnim.speed = 0.1f;

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::RECLUSO);
}

void recluso::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();
	
	pickUp::Update();
}

bool recluso::AddRecluso(int x, int y)
{
	bool ret = false;
	for (uint i = 0; i < MAX_RECLUSOS; ++i)
	{
		spawnQueueR[i].x = x;
		spawnQueueR[i].y = y;
		ret = true;
		break;
	}

	return ret;
}

void recluso::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::PLAYER)
	{
		currentAnim = &rescuedAnim;
	}
	if (c2->type == Collider::Type::PLAYER_SHOT || c2->type == Collider::Type::ENEMY_SHOT)
	{
		currentAnim = &deathAnim;
	}
}