#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleImatges.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleMusica.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL_scancode.h"
#include "ModuleFonts.h"

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

	southEastAnim.PushBack({ 0, 172, 31, 59 });
	southEastAnim.PushBack({ 31, 172, 32, 57 });
	southEastAnim.PushBack({ 64, 171, 28, 57 });
	southEastAnim.PushBack({ 96, 172, 29, 56 });
	southEastAnim.PushBack({ 127, 172, 31, 56 });
	southEastAnim.loop = true;
	southEastAnim.speed = 0.1f;

	southAnim.PushBack({ 0, 233, 28, 59 });
	southAnim.PushBack({ 28, 233, 31, 59 });
	southAnim.PushBack({ 60, 232, 29, 56 });
	southAnim.PushBack({ 92, 233, 31, 55 });
	southAnim.PushBack({ 123, 233, 32, 59 });
	southAnim.loop = true;
	southAnim.speed = 0.1f;

	southWestAnim.PushBack({ 0, 296, 28, 58 });
	southWestAnim.PushBack({ 35, 296, 24, 57 });
	southWestAnim.PushBack({ 67, 295, 23, 58 });
	southWestAnim.PushBack({ 99, 296, 24, 58 });
	southWestAnim.PushBack({ 132, 296, 37, 60 });
	southWestAnim.loop = true;
	southWestAnim.speed = 0.1f;

	westAnim.PushBack({ 0, 357, 30, 58 });
	westAnim.PushBack({ 35, 357, 28, 58 });
	westAnim.PushBack({ 74, 356, 17, 60 });
	westAnim.PushBack({ 101, 356, 25, 59 });
	westAnim.PushBack({ 129, 356, 30, 59 });
	westAnim.loop = true;
	westAnim.speed = 0.1f;

	northWestAnim.PushBack({ 0, 419, 28, 56 });
	northWestAnim.PushBack({ 34, 419, 26, 55 });
	northWestAnim.PushBack({ 68, 418, 23, 55 });
	northWestAnim.PushBack({ 101, 419, 21, 54 });
	northWestAnim.PushBack({ 130, 419, 29, 55 });
	northWestAnim.loop = true;
	northWestAnim.speed = 0.1f;
}
ModulePlayer::~ModulePlayer() {}
bool ModulePlayer::Start() {
	bool ret = false;
	ret = App->imatges->get("sprites_caminant", texture);
	currentAnimation = &idleAnim;
	position.x = 235;
	position.y = 3950;
	char lookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/Text/numeros.png", lookupTable, 1);
	return ret;
}

void ModulePlayer::ShootLasers() {
	switch (direction) {
		case 1:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletN, position.x, position.y - 20, Collider::Type::PLAYER_SHOT);
			break;
		case 2:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletNE, position.x + 10, position.y - 10, Collider::Type::PLAYER_SHOT);
			break;
		case 3:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletE, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
			break;
		case 4:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletSE, position.x + 10, position.y + 10, Collider::Type::PLAYER_SHOT);
			break;
		case 5:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletS, position.x, position.y + 20, Collider::Type::PLAYER_SHOT);
			break;
		case 6:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletSW, position.x - 10, position.y + 10, Collider::Type::PLAYER_SHOT);
			break;
		case 7:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletW, position.x - 10, position.y, Collider::Type::PLAYER_SHOT);
			break;
		case 8:
			App->audio->playSFX("laser", 2);
			App->particles->AddParticle(App->particles->bulletNW, position.x - 10, position.y - 10, Collider::Type::PLAYER_SHOT);
			break;
	}
	
}

update_status ModulePlayer::Update() {
	
	collider->rect.x = position.x;
	collider->rect.y = position.y;
	//Como hay 8 direcciones les pondremos las numeraremos en sentido del reloj, siendo el norte 1 hasta el noroeste 8.

	if (App->input->keyboard[SDL_SCANCODE_W]) {
		direction = 1;
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_D]) {
		direction = 3;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S]) {
		direction = 5;
		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A]) {
		direction = 7;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] && App->input->keyboard[SDL_SCANCODE_D]) {
		direction = 2;
		position.y -= speed / 2;
		position.x += speed / 2;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] && App->input->keyboard[SDL_SCANCODE_D]) {
		direction = 4;
		position.y += speed / 2;
		position.x += speed / 2;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] && App->input->keyboard[SDL_SCANCODE_A]) {
		direction = 8;
		position.y -= speed / 2;
		position.x -= speed / 2;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] && App->input->keyboard[SDL_SCANCODE_A]) {
		direction = 6;
		position.y += speed / 2;
		position.x -= speed / 2;
	}

	switch (direction) {
		case 1:
			currentAnimation = &northAnim;
			break;
		case 2:
			currentAnimation = &northEastAnim;
			break;
		case 3:
			currentAnimation = &eastAnim;
			break;
		case 4:
			currentAnimation = &southEastAnim;
			break;
		case 5:
			currentAnimation = &southAnim;
			break;
		case 6:
			currentAnimation = &southWestAnim;
			break;
		case 7:
			currentAnimation = &westAnim;
			break;
		case 8:
			currentAnimation = &northWestAnim;
			break;
	}
	
	if (!App->input->keyboard[SDL_SCANCODE_S] && !App->input->keyboard[SDL_SCANCODE_W] && !App->input->keyboard[SDL_SCANCODE_D] && !App->input->keyboard[SDL_SCANCODE_A]) currentAnimation->loop = false;
	else currentAnimation->loop = true;
	currentAnimation->Update();
	if (destroyed) {
		destroyedCountdown--;
		if (destroyedCountdown <= 0) return update_status::UPDATE_STOP;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate() {
	if (!destroyed) {
		App->render->Blit(texture, position.x, position.y, &currentAnimation->GetCurrentFrame());
	}

	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(0, 0, scoreFont, scoreText);

	App->fonts->BlitText(250, 4000, scoreFont, "0000");
	App->scene->pintarPalmeras();
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (!destroyed && c2->type != Collider::Type::WATER && c2->type != Collider::Type::WIN)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		destroyed = true;
	}

	else if (c2->type == Collider::Type::WIN) LOG("WIN") {
		destroyed = true;
	}
	if (c2->type == Collider::Type::WATER) {
		
		destroyed = false;
	}

}