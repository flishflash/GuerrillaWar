#include "greenSoldiergranada.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"


greenSoldiergranada::greenSoldiergranada(int x, int y) : Enemy(x, y)
{

	//walk forward
	granadaWalkforward.PushBack({0, 0, 27, 55});
	granadaWalkforward.PushBack({32, 0, 26, 55});
	granadaWalkforward.PushBack({64, 0, 26, 55});
	granadaWalkforward.PushBack({96, 0, 26, 55});
	granadaWalkforward.PushBack({126, 0, 26, 55});
	granadaWalkforward.loop = true;
	granadaWalkforward.speed = 0.1f;

	//walk backward

	granadaWalkbackward.PushBack({ 0, 237, 27, 55 });
	granadaWalkbackward.PushBack({ 32, 237, 26, 55 });
	granadaWalkbackward.PushBack({ 64, 237, 26, 55 });
	granadaWalkbackward.PushBack({ 96, 237, 26, 55 });
	granadaWalkbackward.PushBack({ 126, 237, 26, 55 });
	granadaWalkbackward.loop = true;
	granadaWalkbackward.speed = 0.1f;

	currentAnim = &granadaWalkbackward;

	//path.PushBack({ 0, -1.2f }, 150, &greenWalkbackward);
	//path.PushBack({ 0, 1.2f }, 50, &greenWalkforward);

	collider = App->collisions->AddCollider({ x, y, 28, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}
void greenSoldiergranada::OnCollision(Collider* collider) {

	App->particles->AddParticle(App->particles->deathgreenAnim, positionenemy.x, positionenemy.y, Collider::Type::NONE);

	SetToDelete();
}
void greenSoldiergranada::Update()
{
	/*path.Update();
	positionenemy = spawnPos + path.GetRelativePosition();*/
	//currentAnim = path.GetCurrentAnimation();
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
