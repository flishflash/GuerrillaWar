#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "Application.h"
#include "Globals.h"
bool ModuleRender::Init() {
	renderer = SDL_CreateRenderer(App->window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		LOG("Renderer has not been created.\n");
		LOG(SDL_GetError());
		LOG("\n");
		return false;
	}
	SDL_RenderSetScale(renderer, 1, 1);
	SDL_RenderSetLogicalSize(renderer, RES_WIDTH, RES_HEIGHT);
	App->imatges->loadIMGs();
	return true;
}
update_status ModuleRender::PreUpdate() {
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderSetViewport(renderer, new SDL_Rect({ RES_WIDTH , 0, RES_WIDTH, RES_HEIGHT * 6/4 }));
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleRender::Update() {
	if (App->input->keyboard[SDL_SCANCODE_W]) /* if (camera.y < 0) */ camera.y -= cameraSpeed/2;
	if (App->input->keyboard[SDL_SCANCODE_S]) camera.y += cameraSpeed/2;
	if (App->input->keyboard[SDL_SCANCODE_A]) camera.x -= cameraSpeed/2;
	//if (camera.x < 0) camera.x = 0;
	if (App->input->keyboard[SDL_SCANCODE_D]) camera.x += cameraSpeed/2;
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleRender::PostUpdate() {
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}
bool ModuleRender::CleanUp() {
	SDL_DestroyRenderer(renderer);
	return true;
}
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed) {
	SDL_Rect rect{ (int)(-camera.x * speed) + x , (int)(-camera.y * speed) + y , 0, 0 };
	if (section != nullptr) {
		rect.w = section->w;
		rect.h = section->h;
	}
	else SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, 0, NULL, SDL_FLIP_NONE) != 0) {
		LOG("Cannot blit to screen. SDL_RenderCopyEx error: %s", SDL_GetError());
		return false;
	}
	return true;
}
bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed) {
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + rect.x,
		(int)(-camera.y * speed) + rect.y,
		rect.w, rect.h };

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
