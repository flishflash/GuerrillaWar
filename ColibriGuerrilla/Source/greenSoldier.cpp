#include "greenSoldier.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


greenSoldier::greenSoldier(int x, int y) : Enemy(x, y)
{

	//walk forward
	greenWalkforward.PushBack({0, 0, 27, 55});
	greenWalkforward.PushBack({32, 0, 26, 55});
	greenWalkforward.PushBack({64, 0, 26, 55});
	greenWalkforward.PushBack({96, 0, 26, 55});
	greenWalkforward.PushBack({126, 0, 26, 55});
	greenWalkforward.loop = true;
	greenWalkforward.speed = 0.1f;

	currentAnim = &greenWalkforward;

	//walk backward

	greenWalkbackward.PushBack({ 0, 237, 27, 55 });
	greenWalkbackward.PushBack({ 32, 237, 26, 55 });
	greenWalkbackward.PushBack({ 64, 237, 26, 55 });
	greenWalkbackward.PushBack({ 96, 237, 26, 55 });
	greenWalkbackward.PushBack({ 126, 237, 26, 55 });
	greenWalkbackward.loop = true;
	greenWalkbackward.speed = 0.1f;

	//die

	greenDie.PushBack({256, 498, 27, 49});
	greenDie.PushBack({289, 499, 27, 49});
	//greenDie.PushBack({});
	//greenDie.PushBack({});
	greenDie.loop = false;
	greenDie.speed = 0.2f;

	//path.PushBack({ 0, -1.2f }, 150, &greenWalkbackward);
	/*path.PushBack({ 0, 1.2f }, 10, &greenWalkforward);*/

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void greenSoldier::OnCollision(Collider* collider) {

	App->particles->AddParticle(App->particles->deathgreenAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);

	SetToDelete();
}

void greenSoldier::Update() 
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
