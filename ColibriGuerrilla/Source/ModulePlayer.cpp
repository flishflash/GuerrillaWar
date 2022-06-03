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

	
}

ModulePlayer::~ModulePlayer()
{
	
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	vidas = 3;
	texture = App->textures->Load("Assets/Sprites/sprites_caminant.png");
	trees = App->textures->Load("Assets/Sprites/palmerasMapaless.png");
	currentAnimation = &idleAnim;


	NormalBulFx = App->audio->LoadFx("Assets/Fx/SFX_GWShoot.wav");
	Dead = App->audio->LoadFx("Assets/Fx/dead_player.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 240;
	position.y = 4000;

	cameraGameplay = { 135, 3800, RES_WIDTH, RES_HEIGHT };

	destroyed = false;
	destroyedCountdown = 60;
	gana = false;
	agua = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 22, 30 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "0123456789abcdefghijklmnopqrstuvwxyz.@'&- " };
	scoreFont = App->fonts->Load("Assets/Fonts/ui_font.png", lookupTable, 1);

	return ret;
}

void ModulePlayer::shootNormalBullet()
{
	switch (direction)
	{
	case 1:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletN, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletN, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		
		break;
	case 2:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletNE, position.x + 25, position.y + 5, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletNE, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		break;
	case 3:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletE, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletE, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		break;
	case 4:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletSE, position.x + 17, position.y + 30, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletSE, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		break;
	case 5:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletS, position.x + 5, position.y +40, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletS, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		break;
	case 6:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletSW, position.x + -5, position.y + 30, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletSW, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		break;
	case 7:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletW, position.x -7, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletW, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		break;
	case 8:
		if (App->weapon->options == 1 || App->weapon->options == 2)
		{
			App->particles->AddParticle(App->particles->bulletNW, position.x -5, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		else if (App->weapon->options == 3 || App->weapon->options == 4)
		{
			App->particles->AddParticle(App->particles->TbulletNW, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(NormalBulFx);
		}
		break;
	}
	if (App->weapon->options == 3 || App->weapon->options == 4)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE])
		{
			balitas -= 1;
		}
		if (balitas == 0 && App->weapon->options == 3)
		{
			App->weapon->options = 1;
		}
		else if (balitas == 0 && App->weapon->options == 4)
		{
			App->weapon->options = 2;
		}

	}
}

void ModulePlayer::launchGranade()
{

	switch (direction)
	{
	case 1:
		App->particles->AddParticle(App->particles->granadeN, position.x + 20, position.y - 20, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x - 5, position.y - 100, Collider::Type::EXPLOSION, 50);
		break;
	case 2:
		App->particles->AddParticle(App->particles->granadeNE, position.x + 30, position.y, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x + 55, position.y -75, Collider::Type::EXPLOSION, 50);
		break;
	case 3:
		App->particles->AddParticle(App->particles->granadeE, position.x + 20, position.y + 20, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x + 70, position.y , Collider::Type::EXPLOSION, 50);
		break;
	case 4:
		App->particles->AddParticle(App->particles->granadeSE, position.x + 15, position.y + 30, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x + 55, position.y + 75, Collider::Type::EXPLOSION, 50);
		break;
	case 5:
		App->particles->AddParticle(App->particles->granadeS, position.x + 5, position.y + 30, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x - 15, position.y + 55, Collider::Type::EXPLOSION, 50);
		break;
	case 6:
		App->particles->AddParticle(App->particles->granadeSW, position.x - 7, position.y + 27, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x - 70, position.y + 65, Collider::Type::EXPLOSION, 50);
		break;
	case 7:
		App->particles->AddParticle(App->particles->granadeW, position.x - 20, position.y + 20, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x - 80, position.y, Collider::Type::EXPLOSION, 50);
		break;
	case 8:
		App->particles->AddParticle(App->particles->granadeNW, position.x - 5, position.y, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosionG, position.x - 70, position.y - 75, Collider::Type::EXPLOSION, 50);
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
	currentAnimation->Update();
	*/

	if (destroyed) {
		destroyedCountdown--;
			if (destroyedCountdown <= 0) App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	}
	if (gana)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 60);
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

		if (c1 == collider && destroyed == false && c2->type != Collider::Type::WIN && c2->type != Collider::Type::WATER && c2->type != Collider::Type::WALL && c2->type != Collider::Type::PICK && c2->type != Collider::Type::RECLUSO && c2->type != Collider::Type::GROUND && c2->type != Collider::Type::DESTROY)
		{
			App->audio->PlayFx(Dead);

			if (vidas == 0)
			{
				App->particles->AddParticle(App->particles->playerdies, position.x, position.y, Collider::Type::NONE);

				pendingToDelete = true;
				if (collider != nullptr)
					collider->pendingToDelete = true;

				destroyed = true;
			}
			vidas--;
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
		if (c2->type == Collider::Type::WATER && App->weapon->options != 3)
		{
			App->weapon->options = 2;
		}
		if (c2->type == Collider::Type::WATER && App->weapon->options == 3)
		{
			App->weapon->options = 4;
		}
		if (c2->type == Collider::Type::GROUND && App->weapon->options != 4)
		{
			App->weapon->options = 1;
		}
		if (c2->type == Collider::Type::GROUND && App->weapon->options == 4)
		{
			App->weapon->options = 3;
		}
		if (c2->type == Collider::Type::PICK)
		{
			App->weapon->options = 3;
			balitas = 50;
		}
		
}