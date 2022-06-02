#include "Boss_Soldiers.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


Boss_Soldiers::Boss_Soldiers(int x, int y) : Enemy(x, y)
{
	cooldown = 0;

	//die
	greenDie.PushBack({ 256, 498, 27, 49 });
	greenDie.PushBack({ 289, 499, 27, 49 });
	greenDie.loop = false;
	greenDie.speed = 0.2f;

	//path.PushBack({ 0, -1.2f }, 150, &greenWalkbackward);
	/*path.PushBack({ 0, 1.2f }, 10, &greenWalkforward);*/

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Boss_Soldiers::OnCollision(Collider* collider) {

	if (collider->type != Collider::Type::BOSS)
	{
		App->particles->AddParticle(App->particles->deathgreenAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);
		SetToDelete();
	}
}

void Boss_Soldiers::Update()
{
	path.Update();
	//positionenemy = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation();
	if (cooldown >= 50)
	{
		App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
		cooldown = 0;
	}
	cooldown++;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
