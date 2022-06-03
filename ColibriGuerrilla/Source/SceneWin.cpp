#include "Win.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled)
{

}

SceneWin::~SceneWin()
{

}

// Load assets
bool SceneWin::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/winScreen.png");
	App->audio->PlayMusic("Assets/Music/12_Continue.ogg", 1.0f);
	App->player->cameraGameplay.x = 0;
	App->player->cameraGameplay.y = 0;

	return ret;
}

Update_Status SceneWin::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A])
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}