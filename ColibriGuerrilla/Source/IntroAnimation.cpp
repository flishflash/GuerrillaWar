#include "IntroAnimation.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "Globals.h"
#include "ModuleWindow.h"


IntroAnimation::IntroAnimation(bool startEnabled) : Module(startEnabled) 
{

}

IntroAnimation::~IntroAnimation() 
{

}

// Load assets
bool IntroAnimation::Start()
{
	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/title_map.png");
	introAssets = App->textures->Load("Assets/Sprites/Guerrilla_War_Intro_Spritesheet.png");

	App->player->cameraGameplay.x = 0;
	App->player->cameraGameplay.y = 0;

	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);
	duration = 0;

	bombsAnim.PushBack({ 0 , 160, 16, 16 });
	bombsAnim.PushBack({ 16, 160, 16, 16 });
	bombsAnim.PushBack({ 32, 160, 16, 16 });
	bombsAnim.PushBack({ 48, 160, 16, 16 });
	bombsAnim.PushBack({ 64, 160, 16, 16 });
	bombsAnim.PushBack({ 80, 160, 16, 16 });
	bombsAnim.PushBack({ 96, 160, 16, 16 });
	bombsAnim.PushBack({ 0  , 176, 32, 64 });
	bombsAnim.PushBack({ 32 , 176, 32, 64 });
	bombsAnim.PushBack({ 64 , 176, 32, 64 });
	bombsAnim.PushBack({ 96 , 176, 32, 64 });
	bombsAnim.PushBack({ 128, 176, 32, 64 });
	bombsAnim.PushBack({ 160, 176, 32, 64 });
	bombsAnim.PushBack({ 192, 176, 32, 64 });
	bombsAnim.speed = 0.15f;
	bombsAnim.loop = false;

	planesAnim.PushBack({ 224, 112, 128, 128 });
	planesAnim.loop = false;

	playerMiniAnim.PushBack({ 0  , 0, 32, 32 });
	playerMiniAnim.PushBack({ 32 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 64 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 96 , 0, 32, 32 });
	playerMiniAnim.PushBack({ 128, 0, 32, 32 });
	playerMiniAnim.PushBack({ 160, 0, 32, 32 });
	playerMiniAnim.PushBack({ 192, 0, 32, 32 });
	playerMiniAnim.PushBack({ 224, 0, 32, 32 });
	playerMiniAnim.PushBack({ 256, 0, 32, 32 });
	playerMiniAnim.PushBack({ 288, 0, 32, 32 });
	playerMiniAnim.PushBack({ 320, 0, 32, 32 });
	playerMiniAnim.PushBack({ 352, 0, 32, 32 });
	playerMiniAnim.loop = false;
	playerMiniAnim.speed = 0.21f;

	boatAnim.PushBack({ 0 , 64, 32, 96 });
	boatAnim.PushBack({ 32, 64, 32, 96 });
	boatAnim.PushBack({ 64, 64, 32, 96 });
	boatAnim.PushBack({ 96, 64, 32, 96 });
	boatAnim.loop = true;
	boatAnim.speed = 0.1f;

	assetsPoint[0] = &boat;
	assetsPoint[1] = &playerMini;
	assetsPoint[2] = &bombs[0];
	assetsPoint[3] = &bombs[1];
	assetsPoint[4] = &bombs[2];
	assetsPoint[5] = &bombs[3];
	assetsPoint[6] = &bombs[4];
	assetsPoint[7] = &bombs[5];
	assetsPoint[8] = &bombs[6];
	assetsPoint[9] = &bombs[7];
	assetsPoint[10] = &planes[0];
	assetsPoint[11] = &planes[1];
	assetsPoint[12] = &planes[2];


	assetsAnim[0] = boatAnim;
	assetsAnim[1] = playerMiniAnim;
	assetsAnim[2] = bombsAnim;
	assetsAnim[3] = bombsAnim;
	assetsAnim[4] = bombsAnim;
	assetsAnim[5] = bombsAnim;
	assetsAnim[6] = bombsAnim;
	assetsAnim[7] = bombsAnim;
	assetsAnim[8] = bombsAnim;
	assetsAnim[9] = bombsAnim;
	assetsAnim[10] = planesAnim;
	assetsAnim[11] = planesAnim;
	assetsAnim[12] = planesAnim;


	return ret;
}

Update_Status IntroAnimation::Update() {

	bool button_press = false;
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
		if (App->input->controllers[0].buttons[i] == KEY_DOWN)
		{
			button_press = true; break;
		}

	if (App->input->keys[SDL_SCANCODE_SPACE]|| duration >= 500 || button_press)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 0);
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE]) {
		return Update_Status::UPDATE_STOP;
	}

	if (duration < 360) {
		App->player->cameraGameplay.y -= 4 * SCREEN_SIZE;
	}
	if (duration < 400 && duration >= 360) {
		App->player->cameraGameplay.y -= 2 * SCREEN_SIZE;
	}
	if (duration < 360) {
		boat.y -= 4;
	}
	if (duration < 405 && duration >= 360) {
		boat.y -= 2;
	}

	if (duration == 180) {
		assetsAnim[2].Reset();
		bombs[0].x = (SCREEN_WIDTH / 2) - 8;
		bombs[0].y = -528; 
	}
	if (duration == 185) {
		assetsAnim[3].Reset();
		bombs[1].x = (SCREEN_WIDTH / 2) - 8;
		bombs[1].y = -588; 
	}
	if (duration == 200) {
		assetsAnim[4].Reset();
		bombs[2].x = (SCREEN_WIDTH / 2) - 8;
		bombs[2].y = -648; 
	}
	if (duration == 210) {
		assetsAnim[5].Reset();
		bombs[3].x = (SCREEN_WIDTH / 2) - 8;
		bombs[3].y = -708; 
	}
	if (duration == 220) {
		assetsAnim[6].Reset();
		bombs[4].x = (SCREEN_WIDTH / 2) - 8;
		bombs[4].y = -768; 
	}
	if (duration == 230) {
		assetsAnim[7].Reset();
		bombs[5].x = (SCREEN_WIDTH / 2) - 8;
		bombs[5].y = -828; 
	}
	if (duration == 240) {
		assetsAnim[8].Reset();
		bombs[6].x = (SCREEN_WIDTH / 2) - 8;
		bombs[6].y = -888; 
	}
	if (duration == 250) {
		assetsAnim[9].Reset();
		bombs[7].x = (SCREEN_WIDTH / 2) - 8;
		bombs[7].y = -948; 
	}
	if (duration == 425) {
		assetsAnim[1].Reset();
		playerMini.x = boat.x;
		playerMini.y = boat.y + 16;
	}

	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) {
			if (assetsAnim[i + 2].GetCurrentFrame().x < 6) {
				bombs[i].x += 1;
				bombs[i].y -= 4;
			}
		}
		else {
			if (assetsAnim[i + 2].GetCurrentFrame().x < 6) {
				bombs[i].x -= 1;
				bombs[i].y -= 4;
			}
		}
	}

	if (assetsAnim[1].GetCurrentFrame().x < 8) {
		playerMini.x -= 1;
		playerMini.y -= 1;
	}

	planes[0].y -= 6;
	planes[1].y -= 6;
	planes[2].y -= 6;

	for (int i = 0; i < MAX_ASSETS_TITLE; ++i) {
		assetsAnim[i].Update();
	}

	++duration;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status IntroAnimation::PostUpdate()
{
	App->render->Blit(bgTexture, SCREEN_WIDTH/2 - 112, SCREEN_HEIGHT - 1904, NULL);

	for (int i = 0; i < MAX_ASSETS_TITLE; ++i) {
		SDL_Rect rect = assetsAnim[i].GetCurrentFrame();
		App->render->Blit(introAssets, assetsPoint[i]->x, assetsPoint[i]->y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool IntroAnimation::CleanUp() {
	App->textures->Unload(bgTexture);
	App->textures->Unload(introAssets);
	bgTexture = nullptr;
	introAssets = nullptr;
	return true;
}