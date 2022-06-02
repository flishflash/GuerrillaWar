#include "Boss_Soldiers.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


Boss_Soldiers::Boss_Soldiers(int x, int y) : Enemy(x, y)
{
	cooldown = 0;
	cooldown2 = 0;
	
	//die
	greenWalkL.PushBack({ 0, 368, 30, 51 });
	greenWalkL.PushBack({ 35, 369, 28, 50 });
	greenWalkL.PushBack({ 67, 368, 25, 52 });
	greenWalkL.PushBack({ 99, 368, 27, 52 });
	greenWalkL.PushBack({ 129, 367, 30, 51 });
	greenWalkL.loop = false;
	greenWalkL.speed = 0.2f;
	
	greenWalkR.PushBack({ 0, 115, 29, 52 });
	greenWalkR.PushBack({ 35, 116, 25, 51 });
	greenWalkR.PushBack({ 68, 115, 23, 53 });
	greenWalkR.PushBack({ 99, 116, 25, 52 });
	greenWalkR.PushBack({ 129, 117, 27, 50 });
	greenWalkR.loop = false;
	greenWalkR.speed = 0.2f;

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

	if (cooldown2 >= 50)
	{
		App->particles->AddParticle(App->particles->enemyBullet, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);
		cooldown2 = 0;
	}
	cooldown++;
	if (cooldown < 150)
	{
		currentAnim = &greenWalkR;
		positionenemy.x += 1;
		cooldown++;
	}
	else if (cooldown < 450)
	{
		currentAnim = &greenWalkL;
		positionenemy.x -= 1;
		cooldown++;

	}
	else if (cooldown < 730)
	{
		currentAnim = &greenWalkR;
		positionenemy.x += 1;
		cooldown++;
	}
	else
	{
		cooldown2 = 150;
	}

	Enemy::Update();
}
