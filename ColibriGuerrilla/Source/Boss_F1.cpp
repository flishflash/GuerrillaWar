#include "Boss_F1.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"


Boss_F1::Boss_F1(int x, int y) : Enemy(x, y)
{
	cooldown = 0;
	cooldownspawn = 0;
	cooldownmor = 0;
	random = 0;

	walkforward.PushBack({ 0, 573, 28, 59 });
	walkforward.PushBack({ 30, 573, 30, 59 });
	walkforward.PushBack({ 65, 573, 27, 55 });
	walkforward.PushBack({ 97, 573, 27, 58 });
	walkforward.PushBack({ 128, 573, 28, 59 });
	walkforward.loop = true;
	walkforward.speed = 0.1f;
	currentAnim = &walkforward;

	walkbackward.PushBack({ 0, 639, 31, 58 });
	walkbackward.PushBack({ 33, 639, 30, 58 });
	walkbackward.PushBack({ 65, 639, 30, 55 });
	walkbackward.PushBack({ 96, 639, 31, 57 });
	walkbackward.PushBack({ 129, 639, 30, 58 });
	walkbackward.loop = true;
	walkbackward.speed = 0.1f;

	walkright.PushBack({ 0, 712, 27, 57 });
	walkright.PushBack({ 32, 712, 27, 57 });
	walkright.PushBack({ 62, 712, 28, 58 });
	walkright.PushBack({ 92, 712, 31, 58 });
	walkright.PushBack({ 127, 712, 28, 56 });
	walkright.PushBack({ 159, 712, 27, 58 });
	walkright.loop = true;
	walkright.speed = 0.1f;

	walkleft.PushBack({ 0, 774, 30, 54 });
	walkleft.PushBack({ 35, 774, 28, 54 });
	walkleft.PushBack({ 65, 774, 27, 55 });
	walkleft.PushBack({ 95, 774, 31, 55 });
	walkleft.PushBack({ 129, 774, 30, 54 });
	walkleft.PushBack({ 162, 774, 27, 55 });
	walkleft.loop = true;
	walkleft.speed = 0.1f;

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::BOSS, (Module*)App->enemies);
}
void Boss_F1::OnCollision(Collider* collider)
{

}

void Boss_F1::Update()
{
	path.Update();
	random = rand() % 3;

	if (cooldownspawn > 120)
	{
		switch (random)
		{
		case 0:
			App->enemies->AddEnemy(Enemy_Type::SOLDIERSBOSS, 745, positionenemy.y + 50);
			App->enemies->AddEnemy(Enemy_Type::SOLDIERSBOSS, 765, positionenemy.y + 100);

			break;
		case 1:
			App->enemies->AddEnemy(Enemy_Type::SOLDIERSBOSS, 720, positionenemy.y + 50);
			App->enemies->AddEnemy(Enemy_Type::SOLDIERSBOSS, 780, positionenemy.y + 80);
			App->enemies->AddEnemy(Enemy_Type::SOLDIERSBOSS, 765, positionenemy.y + 120);

			break;
		case 2:
			App->enemies->AddEnemy(Enemy_Type::SOLDIERSBOSS, 765, positionenemy.y + 50);

			break;
		}
		cooldownspawn = 0;
	}

	if (cooldownmor > 1000)
	{
		if (positionenemy.x != 765)
		{
			if (positionenemy.x < 765)
			{
				currentAnim = &walkright;
				positionenemy.x += 1;

			}else
			{
				currentAnim = &walkleft;
				positionenemy.x -= 1;
			}
		}
		else
		{
			currentAnim = &walkbackward;
			positionenemy.y -= 1;
		}
		if (cooldownmor > 1500)
		{
			App->enemies->AddEnemy(Enemy_Type::BOSSF2, 765, 40);
			SetToDelete();
		}
	}
	else {

		if (cooldown < 120)
		{
			positionenemy.y += 1;
			cooldown++;
		}
		else if (cooldown < 270)
		{
			currentAnim = &walkright;
			positionenemy.x += 1;
			cooldown++;
		}
		else if (cooldown < 570)
		{
			currentAnim = &walkleft;
			positionenemy.x -= 1;
			cooldown++;

		}
		else if (cooldown < 850)
		{
			currentAnim = &walkright;
			positionenemy.x += 1;
			cooldown++;
		}
		else
		{
			cooldown = 270;
		}
	}
	cooldownspawn++;
	cooldownmor++;

	Enemy::Update();
}
