#include "greenSoldier.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


greenSoldier::greenSoldier(int x, int y) : Enemy(x, y)
{
	cooldown = 0;
	cooldown2 = 0;
	cooldown3 = 0;

	//walk forward
	greenWalk.PushBack({0, 0, 27, 55});
	greenWalk.PushBack({32, 0, 26, 55});
	greenWalk.PushBack({64, 0, 26, 55});
	greenWalk.PushBack({96, 0, 26, 55});
	greenWalk.PushBack({126, 0, 26, 55});
	greenWalk.loop = true;
	greenWalk.speed = 0.1f;

	currentAnim = &greenWalk;

	//walk backward

	greenWalkshot.PushBack({ 493, 932, 25, 48 });
	greenWalkshot.PushBack({ 493, 932, 25, 48 });
	greenWalkshot.PushBack({ 493, 932, 25, 48 });
	greenWalkshot.PushBack({ 493, 932, 25, 48 });
	greenWalkshot.PushBack({ 493, 932, 25, 48 });
	greenWalkshot.PushBack({ 409, 864, 27, 46});
	greenWalkshot.loop = true;
	greenWalkshot.speed = 0.2f;


	greenWalkbackward.PushBack({ 0, 237, 27, 55 });
	greenWalkbackward.PushBack({ 32, 237, 26, 55 });
	greenWalkbackward.PushBack({ 64, 237, 26, 55 });
	greenWalkbackward.PushBack({ 96, 237, 26, 55 });
	greenWalkbackward.PushBack({ 126, 237, 26, 55 });
	greenWalkbackward.loop = true;
	greenWalkbackward.speed = 0.1f;

	comp = rand() % 2;

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void greenSoldier::OnCollision(Collider* collider) {

	App->particles->AddParticle(App->particles->deathgreenAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);

	SetToDelete();
}

void greenSoldier::Update() 
{
	path.Update();
	switch (comp)
	{
	case 0:
		if (cooldown < 50)
		{
			currentAnim = &greenWalk;
			positionenemy.y += 1;
			cooldown++;
		}
		else if (cooldown >= 50 && cooldown <= 150)
		{
			currentAnim = &greenWalkshot;
			if (cooldown2 == 13)
			{
				App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
				cooldown2 = 0;
			}
			cooldown++;
			cooldown2++;
		}
		else
		{
			cooldown = 0;
		}
		break;

	case 1:
		if (cooldown3 < 300)
		{
			if (cooldown < 50)
			{
				currentAnim = &greenWalk;
				positionenemy.y += 1;
				cooldown++;
			}
			else if (cooldown >= 50 && cooldown <= 150)
			{
				currentAnim = &greenWalkshot;
				if (cooldown2 == 13)
				{
					App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
					cooldown2 = 0;
				}
				cooldown++;
				cooldown2++;
			}
			else
			{
				cooldown = 0;
			}
		}else
		{
			currentAnim = &greenWalkbackward;
			positionenemy.y -= 1;
		}
		cooldown3++;
		break;
	}
	Enemy::Update();
}
