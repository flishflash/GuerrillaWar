#include "Boss_F2.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"


Boss_F2::Boss_F2(int x, int y) : Enemy(x, y)
{
	cooldown = 0;
	cooldownshot = 0;
	cooldown2 = 0;
	cooldownspawn = 0;

	hits = 0;


	fase1.PushBack({0, 853, 59, 128});
	fase1.PushBack({61, 853, 65, 128 });
	fase1.loop = true;
	fase1.speed = 0.3f;
	currentAnim = &fase1;

	dead.PushBack({125, 853, 64, 128});
	dead.PushBack({192, 853, 59, 128 });
	dead.loop = true;
	dead.speed = 0.3f;

	collider = App->collisions->AddCollider({ x, y, 59, 120 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Boss_F2::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::EXPLOSION)
	{
		hits++;
	}
	if (hits == 30)
	{
		App->particles->AddParticle(App->particles->explosion, positionenemy.x + 20, positionenemy.y + 50);
		App->particles->AddParticle(App->particles->explosion, positionenemy.x + 60, positionenemy.y - 20);
		App->particles->AddParticle(App->particles->explosion, positionenemy.x - 10, positionenemy.y + 30);
		App->particles->AddParticle(App->particles->explosion, positionenemy.x + 50, positionenemy.y + 10);
		App->particles->AddParticle(App->particles->explosion, positionenemy.x + 30, positionenemy.y);
		App->particles->AddParticle(App->particles->explosion, positionenemy.x, positionenemy.y + 70);
		//Win collider
		App->collisions->AddCollider({ 705, 128, 167, 64 }, Collider::Type::WIN);
		SetToDelete();
	}
	if (hits == 15)
	{
		currentAnim = &dead;
	}
}

void Boss_F2::Update()
{
	spawn = rand() % 2;
	path.Update();

	if (cooldownspawn==230)
	{
		switch (spawn)
		{
		case 0:
			App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, positionenemy.x + 80, positionenemy.y + 50);
			App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, positionenemy.x - 40, positionenemy.y + 50);
			break;
		case 1:
			App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, positionenemy.x + 80, positionenemy.y + 50);
			break;
		}
		
	}
	else if (cooldownspawn>230)
	{
		cooldownspawn = 0;
	}
	if (cooldown <= 40)
	{
		positionenemy.y += 1;
		cooldown++;
	}
	if (App->player->position.x < 678 && App->player->position.x > 640 && positionenemy.x > 666)
	{
		positionenemy.x -= 2;
	}
	else if (App->player->position.x < 777 && App->player->position.x > 745)
	{
		if (positionenemy.x != 749 || positionenemy.x != 748)
		{
			if (positionenemy.x > 777)
			{
				positionenemy.x -= 2;
			}
			else
			{
				positionenemy.x += 2;
			}
		}
	}
	else if (App->player->position.x < 840 && App->player->position.x > 790 && positionenemy.x < 840)
	{
		positionenemy.x += 1;
	}
		if (cooldown <= 120)
		{
			positionenemy.y += 1;
			cooldown++;
		}
		else if (cooldown <= 200)
		{
			positionenemy.y -= 1;
			cooldown++;
		}
		else
		{
			cooldown = 40;
		}

	if (cooldownshot >= 120)
	{
			App->particles->AddParticle(App->particles->BulletBoss, positionenemy.x + 30, positionenemy.y + 70, Collider::Type::ENEMY_SHOT);
	
			App->particles->AddParticle(App->particles->BulletBossL, positionenemy.x + 40, positionenemy.y + 70, Collider::Type::ENEMY_SHOT);
	
			App->particles->AddParticle(App->particles->BulletBossR, positionenemy.x , positionenemy.y + 70, Collider::Type::ENEMY_SHOT);
			cooldownshot = 0;			
	}
	cooldownshot++;
	cooldownspawn++;
	Enemy::Update();
}