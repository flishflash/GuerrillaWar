#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "Lose.h"
#include "Win.h"
#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 66, 1, 32, 14 });

	// move upwards


	// Move down

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/sprites_caminant.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = 4000;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	
	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.'" };
	scoreFont = App->fonts->Load("Assets/Fonts/UI_font.png", lookupTable, 3);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	collider->rect.x = position.x;
	collider->rect.y = position.y;
	//Como hay 8 direcciones les pondremos las numeraremos en sentido del reloj, siendo el norte 1 hasta el noroeste 8.

	if (App->input->keys[SDL_SCANCODE_W]) {
		direction = 1;
		position.y -= speed;
	}
	if (App->input->keys[SDL_SCANCODE_D]) {
		direction = 3;
		position.x += speed;
	}
	if (App->input->keys[SDL_SCANCODE_S]) {
		direction = 5;
		position.y += speed;
	}
	if (App->input->keys[SDL_SCANCODE_A]) {
		direction = 7;
		position.x -= speed;
	}
	if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D]) {
		direction = 2;
		position.y -= speed / 2;
		position.x += speed / 2;
	}
	if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D]) {
		direction = 4;
		position.y += speed / 2;
		position.x += speed / 2;
	}
	if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A]) {
		direction = 8;
		position.y -= speed / 2;
		position.x -= speed / 2;
	}
	if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A]) {
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

	if (!App->input->keys[SDL_SCANCODE_S] && !App->input->keys[SDL_SCANCODE_W] && !App->input->keys[SDL_SCANCODE_D] && !App->input->keys[SDL_SCANCODE_A]) currentAnimation->loop = false;
	else currentAnimation->loop = true;
	currentAnimation->Update();
	if (destroyed) {
		destroyedCountdown--;
		if (destroyedCountdown <= 0) return Update_Status::UPDATE_STOP;
	}

	//change scene

	if (App->input->keys[SDL_SCANCODE_F3]) App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 60);
	if (App->input->keys[SDL_SCANCODE_F4]) App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 60);

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(58, 248, scoreFont, scoreText);

	App->fonts->BlitText(150, 248, scoreFont, "this is just a font test");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}