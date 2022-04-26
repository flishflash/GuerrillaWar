#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleImatges.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusica.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL_scancode.h"

ModulePlayer::ModulePlayer() {
	idleAnim.PushBack({ 66, 1, 32, 14 });
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer() {}

bool ModulePlayer::Start() {
	bool ret = false;
	ret = App->imatges->get("ship", texture);
	currentAnimation = &idleAnim;
	position.x = 150;
	position.y = 120;
	return ret;
}

void ModulePlayer::ShootLasers() {
	App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
	App->audio->playSFX("laser");
}

update_status ModulePlayer::Update() {
	App->player->position.x += speed;
	collider->rect.x = position.x;
	collider->rect.y = position.y;
	if (App->input->keyboard[SDL_SCANCODE_A]) position.x -= speed;
	if (App->input->keyboard[SDL_SCANCODE_D]) position.x += speed;
	if (App->input->keyboard[SDL_SCANCODE_S]) {
		position.y += speed;
		if (currentAnimation != &downAnim) {
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W]) {
		position.y -= speed;
		if (currentAnimation != &upAnim) {
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
	if (!App->input->keyboard[SDL_SCANCODE_S] && !App->input->keyboard[SDL_SCANCODE_W]) currentAnimation = &idleAnim;
	currentAnimation->Update();
	if (destroyed) {
		destroyedCountdown--;
		if (destroyedCountdown <= 0) return update_status::UPDATE_STOP;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {
	if (!destroyed) {
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c1 == Collider::Type::WATER || c2 == Collider::Type::WATER) {
		
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 7);
		App->render->cameraSpeed = 0;
		speed = 0;
		App->audio->playSFX("explosion");
	}
}