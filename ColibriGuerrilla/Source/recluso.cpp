#include "recluso.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePickUp.h"
#include "ModuleParticles.h"

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

	collider = App->collisions->AddCollider({ x, y, 24, 55 }, Collider::Type::RECLUSO, (Module*)App->picks);
}

void recluso::OnCollision(Collider* collider) {
	path.Update();

	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::ENEMY_SHOT || collider->type == Collider::Type::EXPLOSION) {

		App->particles->AddParticle(App->particles->deathAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);
	}
	else
	{
		App->particles->AddParticle(App->particles->rescuedAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);
	}

		SetToDelete();

}

void recluso::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	pickUp::Update();
}
