#include "ModuleWeapons.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "Lose.h"
#include "Win.h"
#include <stdio.h>

ModuleWeapons::ModuleWeapons(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	

	// north animation
	northWeapon.PushBack({ 0, 15, 4, 16 });
	

	//northeast animation
	northEastWeapon.PushBack({ 15, 12, 15, 15 });
	
	// East animation
	eastWeapon.PushBack({ 44, 14, 20, 14 });

	//southeasst animation
	southEastWeapon.PushBack({ 75, 4, 15, 19 });

	//south animation
	southWeapon.PushBack({115, 0, 4, 20 });

	// southwest animation
	southWestWeapon.PushBack({154, 4, 12, 16 });

	// west animation
	westWeapon.PushBack({184, 17, 18, 13 });

	//northwest animation
	northWestWeapon.PushBack({ 220, 11, 13, 15 });

}

ModuleWeapons::~ModuleWeapons()
{

}

bool ModuleWeapons::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	textureW = App->textures->Load("Assets/Sprites/Weapons_GW.png");
	currentAnimation = &northWeapon;


	positionWeapon.x = 235;
	positionWeapon.y = 4000;

	destroyed = false;
	return ret;
}


Update_Status ModuleWeapons::Update()
{
	



	//Como hay 8 direcciones les pondremos las numeraremos en sentido del reloj, siendo el norte 1 hasta el noroeste 8.

	if (App->input->keys[SDL_SCANCODE_W]) {
		direction = 1;
		positionWeapon.y -= App->player->speed;
	}
	if (App->input->keys[SDL_SCANCODE_D]) {
		direction = 3;
		positionWeapon.x += App->player->speed;
	}
	if (App->input->keys[SDL_SCANCODE_S]) {
		direction = 5;
		positionWeapon.y += App->player->speed;
	}
	if (App->input->keys[SDL_SCANCODE_A]) {
		direction = 7;
		positionWeapon.x -= App->player->speed;
	}
	if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D]) {
		direction = 2;
		positionWeapon.y -= App->player->speed / 2;
		positionWeapon.x += App->player->speed / 2;
	}
	if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D]) {
		direction = 4;
		positionWeapon.y += App->player->speed / 2;
		positionWeapon.x += App->player->speed / 2;
	}
	if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A]) {
		direction = 8;
		positionWeapon.y -= App->player->speed / 2;
		positionWeapon.x -= App->player->speed / 2;
	}
	if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A]) {
		direction = 6;
		positionWeapon.y += App->player->speed / 2;
		positionWeapon.x -= App->player->speed / 2;
	}



	switch (direction) {
	case 1:
		currentAnimation = &northWeapon;
		break;
	case 2:
		currentAnimation = &northEastWeapon;
		break;
	case 3:
		currentAnimation = &eastWeapon;
		break;
	case 4:
		currentAnimation = &southEastWeapon;
		break;
	case 5:
		currentAnimation = &southWeapon;
		break;
	case 6:
		currentAnimation = &southWestWeapon;
		break;
	case 7:
		currentAnimation = &westWeapon;
		break;
	case 8:
		currentAnimation = &northWestWeapon;
		break;
	}

	if (!App->input->keys[SDL_SCANCODE_S] && !App->input->keys[SDL_SCANCODE_W] && !App->input->keys[SDL_SCANCODE_D] && !App->input->keys[SDL_SCANCODE_A]) currentAnimation->loop = false;
	else currentAnimation->loop = true;
	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleWeapons::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(textureW, positionWeapon.x, positionWeapon.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

