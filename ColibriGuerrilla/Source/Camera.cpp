#include "Camera.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "Globals.h"

bool Camera::Start() {
	SDL_UnionRect(rectCamara, rectPlayer, sumRect);
	return false;
}

update_status Camera::Update() {

	SDL_UnionRect(rectCamara, rectPlayer, sumRect);

	while (sumRect->h > rectCamara->h || sumRect->w > rectCamara->w)
	{
		if (App->input->keyboard[SDL_SCANCODE_A]) App->render->camera.x -= App->render->cameraSpeed;
		if (App->input->keyboard[SDL_SCANCODE_D]) App->render->camera.x += App->render->cameraSpeed;
		if (App->input->keyboard[SDL_SCANCODE_S]) {
			App->render->camera.y += App->render->cameraSpeed;
		}
		if (App->input->keyboard[SDL_SCANCODE_S]) {
			App->render->camera.y += App->render->cameraSpeed;
		}
	}
	return update_status::UPDATE_CONTINUE;
}
