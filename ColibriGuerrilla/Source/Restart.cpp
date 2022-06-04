#include "Restart.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"


Restart::Restart(bool startEnabled) : Module(startEnabled)
{

}

Restart::~Restart()
{

}

// Load assets
bool Restart::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/titleScreen.png");
	App->audio->PlayMusic("Assets/Music/01_Demo.ogg", 1.0f);
	App->player->cameraGameplay.x = 0;
	App->player->cameraGameplay.y = 0;

	return ret;
}

Update_Status Restart::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A])
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 60);

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status Restart::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}