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

	currentAnim = &greenWalkbackward;
	currentAnim = &greenWalkswimforward;
	currentAnim = &greenWalkswimbackward;

	greenWalkshot.PushBack({ 0, 237, 27, 55 });
	greenWalkshot.PushBack({ 32, 237, 26, 55 });
	greenWalkshot.PushBack({ 64, 237, 26, 55 });
	greenWalkshot.PushBack({ 96, 237, 26, 55 });
	greenWalkshot.PushBack({ 126, 237, 26, 55 });
	greenWalkshot.loop = true;
	greenWalkshot.speed = 0.1f;

	currentAnim = &greenWalkshot;
	currentAnim = &greenWalk;


	path.PushBack({ 0, -1.2f }, 150, &greenWalkshot);
	path.PushBack({ 0, 1.2f }, 150, &greenWalkforward);

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void greenSoldier::Update() 
{
	path.Update();
	positionenemy = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();
	//if (currentAnim == &greenWalkforward && (cooldown>=10))
	//{
	//	cooldown--;
	//	App->particles->AddParticle(App->particles->bulletS, positionenemy.x, positionenemy.y + 20, Collider::Type::ENEMY_SHOT, 20);

	//}
	//if (currentAnim == &greenWalkshot)
	//{
	//	cooldown = 20;
	//}


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
