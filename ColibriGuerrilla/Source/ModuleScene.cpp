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
	App->render->camera.y = 2000;
	ret = App->imatges->get("background", bgTexture);
	//ret = App->audio->playMusic("stage1", 1.0f);
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);
	App->player->collider = App->collisions->AddCollider({ App->player->position.x, App->player->position.y, 32, 14 }, Collider::Type::PLAYER, App->player);
	App->collisions->AddCollider({ 1376, 240 - 96, 112, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1376, 0, 112, 96 }, Collider::Type::WALL);
	return ret;
}
update_status ModuleScene::Update() {
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleScene::PostUpdate() {
	App->render->Blit(bgTexture, 0, 0, NULL);
	return update_status::UPDATE_CONTINUE;
}