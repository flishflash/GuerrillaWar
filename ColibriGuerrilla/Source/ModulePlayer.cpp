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
	idleAnim.PushBack({ 64, 0, 25, 54 });
	northAnim.PushBack({ 0, 1, 26, 56 });
	northAnim.PushBack({ 33, 1, 26, 56 });
	northAnim.PushBack({ 64, 0, 25, 54 });
	northAnim.PushBack({ 94, 1, 28, 56 });
	northAnim.PushBack({ 128, 1, 26, 56 });
	northAnim.loop = true;
	northAnim.speed = 0.1f;

	northEastAnim.PushBack({ 0, 58, 28, 53 });
	northEastAnim.PushBack({ 35, 58, 25, 53 });
	northEastAnim.PushBack({ 68, 58, 22, 54 });
	northEastAnim.PushBack({ 99, 58, 23, 54 });
	northEastAnim.PushBack({ 130, 58, 22, 54 });
	northEastAnim.loop = true;
	northEastAnim.speed = 0.1f;

	eastAnim.PushBack({ 0, 114, 28, 54 });
	eastAnim.PushBack({ 32, 114, 28, 54 });
	eastAnim.PushBack({ 64, 113, 28, 56 });
	eastAnim.PushBack({ 96, 114, 28, 55 });
	eastAnim.PushBack({ 127, 114, 29, 54 });
	eastAnim.loop = true;
	eastAnim.speed = 0.1f;

	southAnim.PushBack({ 0, 233, 28, 59 });
	southAnim.PushBack({ 28, 233, 31, 59 });
	southAnim.PushBack({ 60, 232, 29, 56 });
	southAnim.PushBack({ 92, 233, 31, 55 });
	southAnim.PushBack({ 123, 233, 32, 59 });
	southAnim.loop = true;
	southAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer() {}

bool ModulePlayer::Start() {
	bool ret = false;
	ret = App->imatges->get("sprites caminant", texture);
	currentAnimation = &idleAnim;
	position.x = 250;
	position.y = 4000;
	return ret;
}

void ModulePlayer::ShootLasers() {
	App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
	App->audio->playSFX("laser");
}

update_status ModulePlayer::Update() {
	
	collider->rect.x = position.x;
	collider->rect.y = position.y;
	if (App->input->keyboard[SDL_SCANCODE_A]) position.x -= speed;
	if (App->input->keyboard[SDL_SCANCODE_D]) {
		position.x += speed;
		if (currentAnimation != &eastAnim) {
			eastAnim.Reset();
			currentAnimation = &eastAnim;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S]) {
		position.y += speed;
		if (currentAnimation != &southAnim) {
			southAnim.Reset();
			currentAnimation = &southAnim;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W]) {
		position.y -= speed;
		if (currentAnimation != &northAnim) {
			northAnim.Reset();
			currentAnimation = &northAnim;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W]&& App->input->keyboard[SDL_SCANCODE_D]) {
		position.y -= speed/2;
		position.x += speed/2;
		if (currentAnimation != &northEastAnim) {
			northEastAnim.Reset();
			currentAnimation = &northEastAnim;
		}
	}
	if (!App->input->keyboard[SDL_SCANCODE_S] && !App->input->keyboard[SDL_SCANCODE_W] && !App->input->keyboard[SDL_SCANCODE_D] && !App->input->keyboard[SDL_SCANCODE_A]) currentAnimation = &idleAnim;
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
	/*if (c1 == Collider::Type::WATER || c2 == Collider::Type::) {
		
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 7);
		App->render->cameraSpeed = 0;
		speed = 0;
		App->audio->playSFX("explosion");
	}*/
}