#include "Enemy_GreenSoldiers.h"

#include "Application.h"
#include "ModuleImatges.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusica.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL_scancode.h"

Enemy_GreenSoldiers::Enemy_GreenSoldiers(int x, int y) : Enemy(x, y) {
	southAnimGreen.PushBack({ 6, 4, 32, 58 });
	southAnimGreen.PushBack({ 40, 5, 28, 57 });
	southAnimGreen.PushBack({ 71, 5, 29, 56 });
	southAnimGreen.PushBack({ 100, 4, 32, 58 });
	southAnimGreen.PushBack({ 133, 4, 32, 60 });
	southAnimGreen.loop = false;
	southAnimGreen.speed = 0.1f;

	currentAnim = &southAnimGreen;
	collider = App->collisions->AddCollider({ 235, 4000, 32, 60 }, Collider::Type::ENEMY, (Module*)App->enemies);
	App->imatges->get("greenEnemies", texture);
}
void Enemy_GreenSoldiers::Update()
{

	Enemy::Update();
}