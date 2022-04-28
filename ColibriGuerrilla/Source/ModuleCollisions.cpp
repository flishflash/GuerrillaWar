#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions() {
	for (uint i = 0; i < MAX_COLLIDERS; ++i) colliders[i] = nullptr;
	//SOMETHING
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::WATER] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WATER] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WATER] = true;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WATER] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WATER] = false;

	matrix[Collider::Type::WATER][Collider::Type::WALL] = false;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::WATER] = false;
}
ModuleCollisions::~ModuleCollisions(){}
update_status ModuleCollisions::PreUpdate() {
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	Collider* c1;
	Collider* c2;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if ((c1 = colliders[i]) == nullptr) continue;
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k) {
			if ((c2 = colliders[k]) == nullptr) continue;
			if (c1->Intersects(c2->rect)) {
				if (matrix[c1->type][c2->type] && c1->listener) c1->listener->OnCollision(c1, c2);
				if (matrix[c2->type][c1->type] && c2->listener)	c2->listener->OnCollision(c2, c1);
			}
		}
	}
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleCollisions::Update() {
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleCollisions::PostUpdate() {
	if (App->state->debug) DebugDraw();
	return update_status::UPDATE_CONTINUE;
}
void ModuleCollisions::DebugDraw() {
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) 	{
		if (colliders[i] == nullptr) continue;
		switch (colliders[i]->type)	{
			case Collider::Type::NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::PLAYER_SHOT: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY_SHOT: // magenta
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::WATER: //black
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
				break;
			case Collider::Type::WIN: //pink
				App->render->DrawQuad(colliders[i]->rect, 248, 12, 181, alpha);
				break;
		}
	}
}
//COLORS
bool ModuleCollisions::CleanUp() {
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] != nullptr) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	return true;
}
Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener) {
	Collider* ret = nullptr;
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr) {
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}
	return ret;
}
