#include "redSoldier.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePickUp.h"



redSoldier::redSoldier(int x, int y) : Enemy(x, y)
{
	compo = 0;
	cooldown = 0;
	cooldown2 = 0;

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

	//path.PushBack({ 0, -1.2f }, 150, &back);
	//path.PushBack({ 0, 1.2f }, 150, &front);

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void redSoldier::OnCollision(Collider* collider) {

	if (collider->type == Collider::Type::PLAYER_SHOT) {
		
		App->picks->AddPick(Pick_Type::FUSIL, positionenemy.x, positionenemy.y);
	}

	App->particles->AddParticle(App->particles->deathredAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);

	SetToDelete();
}

void redSoldier::Update()
{
	path.Update();
	//positionenemy = spawnPos + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation();
	switch (compo)
	{
		case 0:
			if (cooldown >= 70)
			{
				if (cooldown2 == 5)
				{
					App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 8)
				{
					App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 10)
				{
					App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
					cooldown = 0;
					cooldown2 = 0;
					compo = 1;
				}

				cooldown2++;
			}
			cooldown++;
			
			break;
		case 1:
			if (cooldown >= 70)
			{
				if (cooldown2 == 5)
				{
					App->particles->AddParticle(App->particles->enemyBulletL, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 8)
				{
					App->particles->AddParticle(App->particles->enemyBulletL, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 10)
				{
					App->particles->AddParticle(App->particles->enemyBulletL, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
					cooldown = 0;
					cooldown2 = 0;
					compo = 2;
				}

				cooldown2++;
			}
			cooldown++;
			break;
		case 2:
			if (cooldown >= 70)
			{
				if (cooldown2 == 5)
				{
					App->particles->AddParticle(App->particles->enemyBulletR, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 8)
				{
					App->particles->AddParticle(App->particles->enemyBulletR, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 10)
				{
					App->particles->AddParticle(App->particles->enemyBulletR, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
					cooldown = 0;
					cooldown2 = 0;
					compo = 0;
				}

				cooldown2++;
			}
			cooldown++;
			break;
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
