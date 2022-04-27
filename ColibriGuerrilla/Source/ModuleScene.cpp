#include "ModuleScene.h"
#include "Application.h"
#include "ModuleImatges.h"
#include "ModuleRender.h"
#include "ModuleMusica.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
ModuleScene::ModuleScene() {}
ModuleScene::~ModuleScene() {}
bool ModuleScene::Start() {
	bool ret = false;
	if (!(ret = App->imatges->get("background", bgTexture))) return false;
	if (!(ret = App->audio->playMusic("04_Advance-_Area-1_-4_-5_", 1.0f))) return false;
	App->player->collider = App->collisions->AddCollider({ App->player->position.x-2, App->player->position.y-2, 20, 50 }, Collider::Type::PLAYER, App->player);
	
	App->collisions->AddCollider({ 88, 4123, 302, 34 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 216, 3964, 81, 161 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 135, 4091, 32, 121 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 153, 4061, 205, 38 }, Collider::Type::WATER);

	App->collisions->AddCollider({452, 4015, 74, 200}, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 4005, 54, 155 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 421, 4033, 54, 93 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 41, 4000, 52, 65 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 389, 3986, 60, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 48, 3942, 71, 85 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 83, 3864, 73, 133 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 359, 3936, 40, 94 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 326, 3883, 50, 83 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 114, 3637, 72, 267 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 299, 3642, 54, 300 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 54, 4147, 423, 13 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 329, 3436, 50, 211 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 169, 3699, 44, 165 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 73, 3614, 95, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 74, 3446, 40, 156 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 103, 3383, 49, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 289, 3219, 67, 237 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 92, 3119, 88, 273 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 299, 3113, 125, 130 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 175, 3188, 40, 162 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 137, 2975, 171, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 97, 3098, 53, 33 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 81, 2937, 32, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 93, 2876, 60, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 147, 2850, 253, 53 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 401, 3090, 60, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 429, 3072, 48, 21 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 447, 3051, 88, 21 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 526, 2908, 38, 148 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 405, 2588, 35, 285 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 436, 2682, 32, 151 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 557, 2621, 39, 286 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 377, 2483, 30, 91 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 575, 2603, 26, 23 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 585, 2552, 29, 61 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 555, 2348, 212, 202 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 261, 2349, 175, 138 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 240, 2109, 16, 252 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 768, 2118, 30, 238 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 255, 2081, 182, 23 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 557, 2080, 212, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 258, 2291, 131, 25 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 605, 2296, 162, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 451, 2081, 88, 36 }, Collider::Type::WIN);
	
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 235, 4000);
	

	return ret;
}
update_status ModuleScene::Update() {
	
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleScene::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}