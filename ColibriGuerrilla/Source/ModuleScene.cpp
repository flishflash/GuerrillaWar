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
	//if (!(ret = App->audio->playMusic("stage1", 1.0f))) return false;
	App->player->collider = App->collisions->AddCollider({ App->player->position.x, App->player->position.y, 32, 14 }, Collider::Type::PLAYER, App->player);
	App->collisions->AddCollider({ 88, 4123, 302, 34 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 216, 4044, 81, 161 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 135, 4091, 32, 121 }, Collider::Type::WATER);
	return ret;
}
update_status ModuleScene::Update() {
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleScene::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}