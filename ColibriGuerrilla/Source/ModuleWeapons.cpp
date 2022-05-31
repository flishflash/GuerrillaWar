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
	idleAnim.PushBack({ 64, 0, 25, 63 });

	// north animation
	northAnim.PushBack({ 0, 8, 26, 66 });
	northAnim.PushBack({ 50, 8, 27, 66 });
	northAnim.PushBack({ 101, 8, 25, 63 });
	northAnim.PushBack({ 150, 8, 29, 65 });
	northAnim.PushBack({ 203, 8, 29, 66 });
	northAnim.loop = true;
	northAnim.speed = 0.1f;

	//northeast animation
	northEastAnim.PushBack({ 0, 105, 33, 56 });
	northEastAnim.PushBack({ 57, 105, 30, 56 });
	northEastAnim.PushBack({ 111, 105, 32, 56 });
	northEastAnim.PushBack({ 167, 105, 32, 56 });
	northEastAnim.PushBack({ 223, 105, 33, 56 });
	northEastAnim.loop = true;
	northEastAnim.speed = 0.1f;

	// East animation
	eastAnim.PushBack({ 0, 207, 28, 54 });
	eastAnim.PushBack({ 52, 207, 27, 56 });
	eastAnim.PushBack({ 103, 207, 27, 57 });
	eastAnim.PushBack({ 154, 207, 27, 58 });
	eastAnim.PushBack({ 205, 207, 30, 57 });
	eastAnim.loop = true;
	eastAnim.speed = 0.1f;

	//southeasst animation
	southEastAnim.PushBack({ 0, 290, 29, 57 });
	southEastAnim.PushBack({ 46, 290, 29, 56 });
	southEastAnim.PushBack({ 99, 290, 24, 55 });
	southEastAnim.PushBack({ 146, 290, 25, 55 });
	southEastAnim.PushBack({ 194, 290, 26, 56 });
	southEastAnim.loop = true;
	southEastAnim.speed = 0.1f;

	//south animation
	southAnim.PushBack({ 0, 379, 29, 58 });
	southAnim.PushBack({ 50, 379, 28, 58 });
	southAnim.PushBack({ 99, 379, 26, 55 });
	southAnim.PushBack({ 149, 379, 27, 57 });
	southAnim.PushBack({ 200, 379, 28, 58 });
	southAnim.loop = true;
	southAnim.speed = 0.1f;

	// southwest animation
	southWestAnim.PushBack({ 0, 487, 29, 57 });
	southWestAnim.PushBack({ 54, 487, 28, 56 });
	southWestAnim.PushBack({ 106, 487, 27, 56 });
	southWestAnim.PushBack({ 157, 487, 29, 57 });
	southWestAnim.PushBack({ 210, 487, 31, 57 });
	southWestAnim.loop = true;
	southWestAnim.speed = 0.1f;

	// west animation
	westAnim.PushBack({ 0, 583, 37, 56 });
	westAnim.PushBack({ 61, 583, 39, 55 });
	westAnim.PushBack({ 124, 583, 36, 57 });
	westAnim.PushBack({ 184, 583, 39, 56 });
	westAnim.PushBack({ 247, 583, 39, 55 });
	westAnim.loop = true;
	westAnim.speed = 0.1f;

	//northwest animation
	northWestAnim.PushBack({ 0, 677, 30, 56 });
	northWestAnim.PushBack({ 54, 677, 29, 56 });
	northWestAnim.PushBack({ 107, 677, 28, 55 });
	northWestAnim.PushBack({ 159, 677, 27, 55 });
	northWestAnim.PushBack({ 210, 677, 31, 56 });
	northWestAnim.loop = true;
	northWestAnim.speed = 0.1f;



	// Water anims//
	WidleAnim.PushBack({ 64, 0, 25, 63 });

	// north animation
	WnorthAnim.PushBack({ 256, 8, 25, 43 });
	WnorthAnim.PushBack({ 305, 8, 24, 43 });
	WnorthAnim.PushBack({ 353, 8, 25, 42 });
	WnorthAnim.PushBack({ 402, 8, 27, 43 });
	WnorthAnim.PushBack({ 453, 8, 26, 43 });
	WnorthAnim.loop = true;
	WnorthAnim.speed = 0.1f;

	//northeast animation
	WnorthEastAnim.PushBack({ 280, 105, 30, 42 });
	WnorthEastAnim.PushBack({ 334, 105, 31, 43 });
	WnorthEastAnim.PushBack({ 389, 105, 32, 42 });
	WnorthEastAnim.PushBack({ 445, 105, 33, 43 });
	WnorthEastAnim.PushBack({ 502, 105, 33, 42 });
	WnorthEastAnim.loop = true;
	WnorthEastAnim.speed = 0.1f;

	// East animation
	WeastAnim.PushBack({ 259, 207, 27, 43 });
	WeastAnim.PushBack({ 310, 207, 27, 43 });
	WeastAnim.PushBack({ 361, 207, 27, 43 });
	WeastAnim.PushBack({ 412, 207, 27, 43 });
	WeastAnim.PushBack({ 463, 207, 27, 44 });
	WeastAnim.loop = true;
	WeastAnim.speed = 0.1f;

	//southeasst animation
	WsouthEastAnim.PushBack({ 240, 290, 25, 43 });
	WsouthEastAnim.PushBack({ 289, 290, 26, 43 });
	WsouthEastAnim.PushBack({ 339, 290, 23, 43 });
	WsouthEastAnim.PushBack({ 386, 290, 24, 44 });
	WsouthEastAnim.PushBack({ 434, 290, 23, 44 });
	WsouthEastAnim.loop = true;
	WsouthEastAnim.speed = 0.1f;

	//south animation
	WsouthAnim.PushBack({ 252, 379, 26, 43 });
	WsouthAnim.PushBack({ 302, 379, 25, 43 });
	WsouthAnim.PushBack({ 351, 379, 26, 42 });
	WsouthAnim.PushBack({ 401, 379, 27, 43 });
	WsouthAnim.PushBack({ 452, 379, 28, 42 });
	WsouthAnim.loop = true;
	WsouthAnim.speed = 0.1f;

	// southwest animation
	WsouthWestAnim.PushBack({ 265, 487, 28, 41 });
	WsouthWestAnim.PushBack({ 317, 487, 28, 43 });
	WsouthWestAnim.PushBack({ 369, 487, 27, 42 });
	WsouthWestAnim.PushBack({ 420, 487, 29, 43 });
	WsouthWestAnim.PushBack({ 473, 487, 30, 43 });
	WsouthWestAnim.loop = true;
	WsouthWestAnim.speed = 0.1f;

	// west animation
	WwestAnim.PushBack({ 310, 583, 37, 43 });
	WwestAnim.PushBack({ 371, 583, 39, 42 });
	WwestAnim.PushBack({ 434, 583, 36, 43 });
	WwestAnim.PushBack({ 494, 583, 39, 43 });
	WwestAnim.PushBack({ 557, 583, 39, 43 });
	WwestAnim.loop = true;
	WwestAnim.speed = 0.1f;

	//northwest animation
	WnorthWestAnim.PushBack({ 261, 677, 30, 42 });
	WnorthWestAnim.PushBack({ 315, 677, 29, 43 });
	WnorthWestAnim.PushBack({ 368, 677, 28, 42 });
	WnorthWestAnim.PushBack({ 420, 677, 29, 43 });
	WnorthWestAnim.PushBack({ 473, 677, 28, 42 });
	WnorthWestAnim.loop = true;
	WnorthWestAnim.speed = 0.1f;


	// wEAPON 2 Animations//
	TnorthAnim.PushBack({ 870, 0, 25, 63 });

	// north animation
	TnorthAnim.PushBack({ 769, 0, 26, 66 });
	TnorthAnim.PushBack({ 816, 0, 27, 66 });
	TnorthAnim.PushBack({ 870, 0, 25, 63 });
	TnorthAnim.PushBack({ 919, 0, 29, 65 });
	TnorthAnim.PushBack({ 972, 0, 29, 66 });
	TnorthAnim.loop = true;
	TnorthAnim.speed = 0.1f;

	//northeast animation
	TnorthEastAnim.PushBack({ 844, 105, 40, 55 });
	TnorthEastAnim.PushBack({ 908, 105, 36, 56 });
	TnorthEastAnim.PushBack({ 968, 105, 37, 56 });
	TnorthEastAnim.PushBack({ 1029, 105, 38, 57 });
	TnorthEastAnim.PushBack({ 1091, 105, 39, 57 });
	TnorthEastAnim.loop = true;
	TnorthEastAnim.speed = 0.1f;

	// East animation
	eastAnim.PushBack({ 0, 207, 28, 54 });
	eastAnim.PushBack({ 52, 207, 27, 56 });
	eastAnim.PushBack({ 103, 207, 27, 57 });
	eastAnim.PushBack({ 154, 207, 27, 58 });
	eastAnim.PushBack({ 205, 207, 30, 57 });
	eastAnim.loop = true;
	eastAnim.speed = 0.1f;

	//southeasst animation
	southEastAnim.PushBack({ 0, 290, 29, 57 });
	southEastAnim.PushBack({ 46, 290, 29, 56 });
	southEastAnim.PushBack({ 99, 290, 24, 55 });
	southEastAnim.PushBack({ 146, 290, 25, 55 });
	southEastAnim.PushBack({ 194, 290, 26, 56 });
	southEastAnim.loop = true;
	southEastAnim.speed = 0.1f;

	//south animation
	southAnim.PushBack({ 0, 379, 29, 58 });
	southAnim.PushBack({ 50, 379, 28, 58 });
	southAnim.PushBack({ 99, 379, 26, 55 });
	southAnim.PushBack({ 149, 379, 27, 57 });
	southAnim.PushBack({ 200, 379, 28, 58 });
	southAnim.loop = true;
	southAnim.speed = 0.1f;

	// southwest animation
	southWestAnim.PushBack({ 0, 487, 29, 57 });
	southWestAnim.PushBack({ 54, 487, 28, 56 });
	southWestAnim.PushBack({ 106, 487, 27, 56 });
	southWestAnim.PushBack({ 157, 487, 29, 57 });
	southWestAnim.PushBack({ 210, 487, 31, 57 });
	southWestAnim.loop = true;
	southWestAnim.speed = 0.1f;

	// west animation
	westAnim.PushBack({ 0, 583, 37, 56 });
	westAnim.PushBack({ 61, 583, 39, 55 });
	westAnim.PushBack({ 124, 583, 36, 57 });
	westAnim.PushBack({ 184, 583, 39, 56 });
	westAnim.PushBack({ 247, 583, 39, 55 });
	westAnim.loop = true;
	westAnim.speed = 0.1f;

	//northwest animation
	northWestAnim.PushBack({ 0, 677, 30, 56 });
	northWestAnim.PushBack({ 54, 677, 29, 56 });
	northWestAnim.PushBack({ 107, 677, 28, 55 });
	northWestAnim.PushBack({ 159, 677, 27, 55 });
	northWestAnim.PushBack({ 210, 677, 31, 56 });
	northWestAnim.loop = true;
	northWestAnim.speed = 0.1f;



	// Water weapon 2 anims//
	WidleAnim.PushBack({ 64, 0, 25, 63 });

	// north animation
	WnorthAnim.PushBack({ 1025, 8, 25, 43 });
	WnorthAnim.PushBack({ 305, 8, 24, 43 });
	WnorthAnim.PushBack({ 353, 8, 25, 42 });
	WnorthAnim.PushBack({ 402, 8, 27, 43 });
	WnorthAnim.PushBack({ 453, 8, 26, 43 });
	WnorthAnim.loop = true;
	WnorthAnim.speed = 0.1f;

	//northeast animation
	WnorthEastAnim.PushBack({ 280, 105, 30, 42 });
	WnorthEastAnim.PushBack({ 334, 105, 31, 43 });
	WnorthEastAnim.PushBack({ 389, 105, 32, 42 });
	WnorthEastAnim.PushBack({ 445, 105, 33, 43 });
	WnorthEastAnim.PushBack({ 502, 105, 33, 42 });
	WnorthEastAnim.loop = true;
	WnorthEastAnim.speed = 0.1f;

	// East animation
	WeastAnim.PushBack({ 259, 207, 27, 43 });
	WeastAnim.PushBack({ 310, 207, 27, 43 });
	WeastAnim.PushBack({ 361, 207, 27, 43 });
	WeastAnim.PushBack({ 412, 207, 27, 43 });
	WeastAnim.PushBack({ 463, 207, 27, 44 });
	WeastAnim.loop = true;
	WeastAnim.speed = 0.1f;

	//southeasst animation
	WsouthEastAnim.PushBack({ 240, 290, 25, 43 });
	WsouthEastAnim.PushBack({ 289, 290, 26, 43 });
	WsouthEastAnim.PushBack({ 339, 290, 23, 43 });
	WsouthEastAnim.PushBack({ 386, 290, 24, 44 });
	WsouthEastAnim.PushBack({ 434, 290, 23, 44 });
	WsouthEastAnim.loop = true;
	WsouthEastAnim.speed = 0.1f;

	//south animation
	WsouthAnim.PushBack({ 252, 379, 26, 43 });
	WsouthAnim.PushBack({ 302, 379, 25, 43 });
	WsouthAnim.PushBack({ 351, 379, 26, 42 });
	WsouthAnim.PushBack({ 401, 379, 27, 43 });
	WsouthAnim.PushBack({ 452, 379, 28, 42 });
	WsouthAnim.loop = true;
	WsouthAnim.speed = 0.1f;

	// southwest animation
	WsouthWestAnim.PushBack({ 265, 487, 28, 41 });
	WsouthWestAnim.PushBack({ 317, 487, 28, 43 });
	WsouthWestAnim.PushBack({ 369, 487, 27, 42 });
	WsouthWestAnim.PushBack({ 420, 487, 29, 43 });
	WsouthWestAnim.PushBack({ 473, 487, 30, 43 });
	WsouthWestAnim.loop = true;
	WsouthWestAnim.speed = 0.1f;

	// west animation
	WwestAnim.PushBack({ 310, 583, 37, 43 });
	WwestAnim.PushBack({ 371, 583, 39, 42 });
	WwestAnim.PushBack({ 434, 583, 36, 43 });
	WwestAnim.PushBack({ 494, 583, 39, 43 });
	WwestAnim.PushBack({ 557, 583, 39, 43 });
	WwestAnim.loop = true;
	WwestAnim.speed = 0.1f;

	//northwest animation
	WnorthWestAnim.PushBack({ 261, 677, 30, 42 });
	WnorthWestAnim.PushBack({ 315, 677, 29, 43 });
	WnorthWestAnim.PushBack({ 368, 677, 28, 42 });
	WnorthWestAnim.PushBack({ 420, 677, 29, 43 });
	WnorthWestAnim.PushBack({ 473, 677, 28, 42 });
	WnorthWestAnim.loop = true;
	WnorthWestAnim.speed = 0.1f;

}

ModuleWeapons::~ModuleWeapons()
{

}

bool ModuleWeapons::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	textureW = App->textures->Load("Assets/Sprites/Sprites_Player.png");
	WcurrentAnimation = &northAnim;

	spritep.x = 240;
	spritep.y = 4000;

	options = 1;

	destroyed = false;
	return ret;
}


Update_Status ModuleWeapons::Update()
{ 
	switch (options)
	{
	case  1:
			if (App->input->keys[SDL_SCANCODE_W]) {
				direction = 1;
				spritep.y = App->player->position.y;
			}
			if (App->input->keys[SDL_SCANCODE_D]) {
				direction = 3;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_S]) {
				direction = 5;
				spritep.y = App->player->position.y;
			}
			if (App->input->keys[SDL_SCANCODE_A]) {
				direction = 7;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D]) {
				direction = 2;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D]) {
				direction = 4;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A]) {
				direction = 8;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A]) {
				direction = 6;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}


			switch (direction) {
			case 1:
				WcurrentAnimation = &northAnim;
				break;
			case 2:
				WcurrentAnimation = &northEastAnim;
				break;
			case 3:
				WcurrentAnimation = &eastAnim;
				break;
			case 4:
				WcurrentAnimation = &southEastAnim;
				break;
			case 5:
				WcurrentAnimation = &southAnim;
				break;
			case 6:
				WcurrentAnimation = &southWestAnim;
				break;
			case 7:
				WcurrentAnimation = &westAnim;
				break;
			case 8:
				WcurrentAnimation = &northWestAnim;
				break;
			}
			if (!App->input->keys[SDL_SCANCODE_S] && !App->input->keys[SDL_SCANCODE_W] && !App->input->keys[SDL_SCANCODE_D] && !App->input->keys[SDL_SCANCODE_A]) WcurrentAnimation->loop = false;
			else WcurrentAnimation->loop = true;
			WcurrentAnimation->Update();
		//Como hay 8 direcciones les pondremos las numeraremos en sentido del reloj, siendo el norte 1 hasta el noroeste 8.
	case 2:
		
			if (App->input->keys[SDL_SCANCODE_W]) {
				direction = 1;
				spritep.y = App->player->position.y;
			}
			if (App->input->keys[SDL_SCANCODE_D]) {
				direction = 3;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_S]) {
				direction = 5;
				spritep.y = App->player->position.y;
			}
			if (App->input->keys[SDL_SCANCODE_A]) {
				direction = 7;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_D]) {
				direction = 2;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_D]) {
				direction = 4;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_W] && App->input->keys[SDL_SCANCODE_A]) {
				direction = 8;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}
			if (App->input->keys[SDL_SCANCODE_S] && App->input->keys[SDL_SCANCODE_A]) {
				direction = 6;
				spritep.y = App->player->position.y;
				spritep.x = App->player->position.x;
			}


			switch (direction) {
			case 1:
				WcurrentAnimation = &WnorthAnim;
				break;
			case 2:
				WcurrentAnimation = &WnorthEastAnim;
				break;
			case 3:
				WcurrentAnimation = &WeastAnim;
				break;
			case 4:
				WcurrentAnimation = &WsouthEastAnim;
				break;
			case 5:
				WcurrentAnimation = &WsouthAnim;
				break;
			case 6:
				WcurrentAnimation = &WsouthWestAnim;
				break;
			case 7:
				WcurrentAnimation = &WwestAnim;
				break;
			case 8:
				WcurrentAnimation = &WnorthWestAnim;
				break;
			}
			if (!App->input->keys[SDL_SCANCODE_S] && !App->input->keys[SDL_SCANCODE_W] && !App->input->keys[SDL_SCANCODE_D] && !App->input->keys[SDL_SCANCODE_A]) WcurrentAnimation->loop = false;
			else WcurrentAnimation->loop = true;
			WcurrentAnimation->Update();
		
	}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleWeapons::PostUpdate()
{

	return Update_Status::UPDATE_CONTINUE;
}

