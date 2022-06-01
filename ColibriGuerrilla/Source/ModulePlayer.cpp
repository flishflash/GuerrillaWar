#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleWeapons.h"
#include "Lose.h"
#include "Win.h"
#include <stdio.h>
#include <math.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//// idle animation - just one sprite
	//idleAnim.PushBack({ 64, 0, 25, 54 });

	//// north animation
	//northAnim.PushBack({ 0, 1, 26, 56 });
	//northAnim.PushBack({ 33, 1, 26, 56 });
	//northAnim.PushBack({ 64, 0, 25, 54 });
	//northAnim.PushBack({ 94, 1, 28, 56 });
	//northAnim.PushBack({ 128, 1, 26, 56 });
	//northAnim.loop = true;
	//northAnim.speed = 0.1f;

	////northeast animation
	//northEastAnim.PushBack({ 0, 58, 28, 53 });
	//northEastAnim.PushBack({ 35, 58, 25, 53 });
	//northEastAnim.PushBack({ 68, 58, 22, 54 });
	//northEastAnim.PushBack({ 99, 58, 23, 54 });
	//northEastAnim.PushBack({ 130, 58, 22, 54 });
	//northEastAnim.loop = true;
	//northEastAnim.speed = 0.1f;

	//// East animation
	//eastAnim.PushBack({ 0, 114, 28, 54 });
	//eastAnim.PushBack({ 32, 114, 28, 54 });
	//eastAnim.PushBack({ 64, 113, 28, 56 });
	//eastAnim.PushBack({ 96, 114, 28, 55 });
	//eastAnim.PushBack({ 127, 114, 29, 54 });
	//eastAnim.loop = true;
	//eastAnim.speed = 0.1f;

	////southeasst animation
	//southEastAnim.PushBack({ 0, 172, 31, 59 });
	//southEastAnim.PushBack({ 31, 172, 32, 57 });
	//southEastAnim.PushBack({ 64, 171, 28, 57 });
	//southEastAnim.PushBack({ 96, 172, 29, 56 });
	//southEastAnim.PushBack({ 127, 172, 31, 56 });
	//southEastAnim.loop = true;
	//southEastAnim.speed = 0.1f;

	////south animation
	//southAnim.PushBack({ 0, 233, 28, 59 });
	//southAnim.PushBack({ 28, 233, 31, 59 });
	//southAnim.PushBack({ 60, 232, 29, 56 });
	//southAnim.PushBack({ 92, 233, 31, 55 });
	//southAnim.PushBack({ 123, 233, 32, 59 });
	//southAnim.loop = true;
	//southAnim.speed = 0.1f;

	//// southwest animation
	//southWestAnim.PushBack({ 0, 296, 28, 58 });
	//southWestAnim.PushBack({ 35, 296, 24, 57 });
	//southWestAnim.PushBack({ 67, 295, 23, 58 });
	//southWestAnim.PushBack({ 99, 296, 24, 58 });
	//southWestAnim.PushBack({ 132, 296, 37, 60 });
	//southWestAnim.loop = true;
	//southWestAnim.speed = 0.1f;

	//// west animation
	//westAnim.PushBack({ 0, 357, 30, 58 });
	//westAnim.PushBack({ 35, 357, 28, 58 });
	//westAnim.PushBack({ 74, 356, 17, 60 });
	//westAnim.PushBack({ 101, 356, 25, 59 });
	//westAnim.PushBack({ 129, 356, 30, 59 });
	//westAnim.loop = true;
	//westAnim.speed = 0.1f;

	////northwest animation
	//northWestAnim.PushBack({ 0, 419, 28, 56 });
	//northWestAnim.PushBack({ 34, 419, 26, 55 });
	//northWestAnim.PushBack({ 68, 418, 23, 55 });
	//northWestAnim.PushBack({ 101, 419, 21, 54 });
	//northWestAnim.PushBack({ 130, 419, 29, 55 });
	//northWestAnim.loop = true;
	//northWestAnim.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{
	
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/sprites_caminant.png");
	trees = App->textures->Load("Assets/Sprites/palmerasMapaless.png");
	currentAnimation = &idleAnim;


	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 240;
	position.y = 4000;

	cameraGameplay = { 135, 3800, RES_WIDTH, RES_HEIGHT };

	destroyed = false;
	destroyedCountdown = 60;
	gana = false;
	agua = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 22, 30 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "0123456789abcdefghijklmnopqrstuvwxyz. @'&-" };
	scoreFont = App->fonts->Load("Assets/Fonts/ui_font_.png", lookupTable, 1);

	return ret;
}

void ModulePlayer::shootNormalBullet()
{
	switch (direction)
	{
	case 1:
		App->particles->AddParticle(App->particles->bulletN, position.x +20, position.y, Collider::Type::PLAYER_SHOT);
		break;
	case 2:
		App->particles->AddParticle(App->particles->bulletNE, position.x + 30, position.y , Collider::Type::PLAYER_SHOT);
		break;
	case 3:
		App->particles->AddParticle(App->particles->bulletE, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
		break;
	case 4:
		App->particles->AddParticle(App->particles->bulletSE, position.x + 15, position.y + 30, Collider::Type::PLAYER_SHOT);
		break;
	case 5:
		App->particles->AddParticle(App->particles->bulletS, position.x + 5, position.y + 25, Collider::Type::PLAYER_SHOT);
		break;
	case 6:
		App->particles->AddParticle(App->particles->bulletSW, position.x - 7, position.y + 27, Collider::Type::PLAYER_SHOT);
		break;
	case 7:
		App->particles->AddParticle(App->particles->bulletW, position.x - 20, position.y + 20, Collider::Type::PLAYER_SHOT);
		break;
	case 8:
		App->particles->AddParticle(App->particles->bulletNW, position.x - 5, position.y, Collider::Type::PLAYER_SHOT);
		break;
	}
}

void ModulePlayer::launchGranade()
{
	switch (direction)
	{
	case 1:
		App->particles->AddParticle(App->particles->granade, position.x + 20, position.y, Collider::Type::EXPLOSION);
		App->particles->granade.speed.y = -1;
		break;
	case 2:
		App->particles->AddParticle(App->particles->granade, position.x + 30, position.y, Collider::Type::EXPLOSION);
		App->particles->granade.speed.y = -1;
		App->particles->granade.speed.x = 1;
		break;
	case 3:
		App->particles->AddParticle(App->particles->granade, position.x + 20, position.y + 20, Collider::Type::EXPLOSION);
		App->particles->granade.speed.x = 1;
		break;
	case 4:
		App->particles->AddParticle(App->particles->granade, position.x + 15, position.y + 30, Collider::Type::EXPLOSION);
		App->particles->granade.speed.y = 1;
		App->particles->granade.speed.x = 1;
		break;
	case 5:
		App->particles->AddParticle(App->particles->granade, position.x + 5, position.y + 25, Collider::Type::EXPLOSION);
		App->particles->granade.speed.y = 1;
		break;
	case 6:
		App->particles->AddParticle(App->particles->granade, position.x - 7, position.y + 27, Collider::Type::EXPLOSION);
		App->particles->granade.speed.y = 1;
		App->particles->granade.speed.x = -1;
		break;
	case 7:
		App->particles->AddParticle(App->particles->granade, position.x - 20, position.y + 20, Collider::Type::EXPLOSION);
		App->particles->granade.speed.x = -1;
		break;
	case 8:
		App->particles->AddParticle(App->particles->granade, position.x - 5, position.y, Collider::Type::EXPLOSION);
		App->particles->granade.speed.y = 1;
		App->particles->granade.speed.x = -1;
		break;
	}
}

Update_Status ModulePlayer::Update()
{

	collider->rect.x = position.x;
	collider->rect.y = position.y + 25;
	//Camara
	if (position.x - cameraGameplay.x < RES_WIDTH - 150)
	{
		cameraGameplay.x -= speed;
	}
	if (position.x - cameraGameplay.x > RES_WIDTH - 90)
	{
		cameraGameplay.x += speed;
	}
	if (position.y - cameraGameplay.y > RES_HEIGHT - 120)
	{
		cameraGameplay.y += speed;
	}
	if (position.y - cameraGameplay.y < RES_HEIGHT - 180)
	{
		cameraGameplay.y -= speed;
	}

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

	/*
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
	currentAnimation->Update();*/
	if (destroyed) {
		destroyedCountdown--;
		if (destroyedCountdown <= 0) App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 60);
	}
	if (gana)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 60);
	}
	if (App->input->keys[SDL_SCANCODE_G])
	{
		launchGranade();
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
		SDL_Rect rectW = App->weapon->WcurrentAnimation->GetCurrentFrame();
		App->render->Blit(App->weapon->textureW, App->weapon->spritep.x, App->weapon->spritep.y, &rectW);
		/*SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);*/
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(HighscoreText, 10, "%7d", highscore);

	App->render->Blit(trees, 0, 0, NULL);
	// TODO 3: Blit the text of the score in at the bottom of the screen

	App->fonts->BlitText(position.x, position.y, scoreFont, scoreText);

	App->fonts->BlitText(75, 35, scoreFont, "hi");

	//highscore
	if(score > highscore)
	{
		highscore = score;
	}
	App->fonts->BlitText(107, 35, scoreFont, HighscoreText);

	App->fonts->BlitText(25, 43, scoreFont, "1 up");
	App->fonts->BlitText(165, 43, scoreFont, "2 up");

	//score player 1
	App->fonts->BlitText(40, 51, scoreFont, scoreText);

	//score player 2
	App->fonts->BlitText(204, 51, scoreFont, "0");


	App->fonts->BlitText(115, 315, scoreFont, "insert coin");
	App->fonts->BlitText(155, 330, scoreFont, "credit 0");



	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(!App->collisions->godmode)
	{

		if (c1 == collider && destroyed == false && c2->type != Collider::Type::WIN && c2->type != Collider::Type::WATER && c2->type != Collider::Type::WALL && c2->type != Collider::Type::PICK && c2->type != Collider::Type::RECLUSO)
		{
		/*	App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
			App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
			App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
			App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
			App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);*/

			pendingToDelete = true;
			if (collider != nullptr)
				collider->pendingToDelete = true;

			App->audio->PlayFx(explosionFx);
			destroyed = true;
		}
	}
		if (c2->type == Collider::Type::WALL || c2->type == Collider::Type::DESTROY)
		{
			switch (direction)
			{
			case 1:
				position.y = position.y + 1;
				break;
			case 2:
				position.x = position.x - 1;
				position.y = position.y + 1;
				break;
			case 3:
				position.x = position.x - 1;
				break;
			case 4:
				position.x = position.x - 1;
				position.y = position.y - 1;
				break;
			case 5:
				position.y = position.y - 1;
				break;
			case 6:
				position.x = position.x + 1;
				position.y = position.y - 1;
				break;
			case 7:
				position.x = position.x + 1;
				break;
			case 8:
				position.x = position.x + 1;
				position.y = position.y + 1;
				break;
			}
		}
		
		if (c2->type == Collider::Type::RECLUSO)
		{
			score += 1000;

		}
		if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::RECLUSO)
		{
			score -= 500;
		}
		if (c2->type == Collider::Type::WIN)
		{
			gana = true;
			pendingToDelete = true;
			if (collider != nullptr)
				collider->pendingToDelete = true;

			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 60);
		}
		if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
		{
			score += 100;
		}
		
}