#include "Boss_F2.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


Boss_F2::Boss_F2(int x, int y) : Enemy(x, y)
{
	cooldown = 0;

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::BOSS, (Module*)App->enemies);
}

void Boss_F2::Update()
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