#include "SceneLose.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

SceneLose::SceneLose(bool startEnabled) : Module(startEnabled)
{

}

SceneLose::~SceneLose()
{

}

// Load assets
bool SceneLose::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/loseScreen.png");

	App->player->cameraGameplay.x = 0;
	App->player->cameraGameplay.y = 0;

	return ret;
}

Update_Status SceneLose::Update()
{
	if (vidas<0)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
	}
	else
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
			vidas--;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLose::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}