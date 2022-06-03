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

	front.PushBack({631, 628, 25, 46});
	front.PushBack({631, 628, 25, 46});
	front.PushBack({634, 566, 25, 46});
	front.loop = true;
	front.speed = 0.1f;
	currentAnim = &front;

	right.PushBack({ 582, 629, 26, 45 });
	right.PushBack({ 582, 629, 26, 45 });
	right.PushBack({ 581, 567, 28, 42 });
	right.loop = true;
	right.speed = 0.1f;


	left.PushBack({ 685, 630, 27, 45 });
	left.PushBack({ 685, 630, 27, 45 });
	left.PushBack({ 681, 567, 29, 43 });
	left.loop = true;
	left.speed = 0.1f;

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


	switch (compo)
	{
		case 0:

			currentAnim = &left;

			if (cooldown >= 70)
			{
				if (cooldown2 == 5)
				{
					App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 10, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 8)
				{
					App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 10, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 11)
				{
					App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 10, Collider::Type::ENEMY_SHOT, 20);
					cooldown = 0;
					cooldown2 = 0;
					compo = 1;
				}

				cooldown2++;
			}
			cooldown++;
			
			break;
		case 1:

			currentAnim = &front;

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
				if (cooldown2 == 11)
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

			currentAnim = &right;

			if (cooldown >= 70)
			{
				if (cooldown2 == 5)
				{
					App->particles->AddParticle(App->particles->enemyBulletR, positionenemy.x + 10, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 8)
				{
					App->particles->AddParticle(App->particles->enemyBulletR, positionenemy.x + 10, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				}
				if (cooldown2 == 11)
				{
					App->particles->AddParticle(App->particles->enemyBulletR, positionenemy.x + 10, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
					cooldown = 0;
					cooldown2 = 0;
					compo = 0;
				}

				cooldown2++;
			}
			cooldown++;
			break;
	}


	Enemy::Update();
}
