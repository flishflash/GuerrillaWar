#include "ModuleImatges.h"
#include "Application.h"
#include "SDL_image/include/SDL_image.h"
bool ModuleImatges::CleanUp() {
	for (std::map<std::string, SDL_Texture*>::iterator iterador = mapa.begin(); iterador != mapa.end(); iterador++) {
		SDL_DestroyTexture(iterador->second);
		mapa[iterador->first] = nullptr;
	}
	IMG_Quit();
	return true;
}
bool ModuleImatges::Init() {
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		LOG("Image displaying library has not been initialized.\n");
		LOG(SDL_GetError());
		LOG("\n");
		return false;
	}
	return true;
}
bool ModuleImatges::loadIMGs() {
	for (const auto& entry : std::filesystem::directory_iterator("./Assets")) {
		if (entry.is_regular_file() && !entry.path().extension().compare(".png")) {
			mapa[entry.path().stem().string()] = SDL_CreateTextureFromSurface(App->render->renderer, IMG_Load(entry.path().string().c_str()));
			LOG(entry.path().string().c_str());
			if (mapa[entry.path().stem().string()] == NULL) {
				LOG(" has not been loaded.\n");
				LOG(SDL_GetError());
				LOG("\n");
				return false;
			}
			LOG(" has been loaded.\n");
		}
	}
	return true;
}
bool ModuleImatges::get(std::string name, SDL_Texture*& p) {
	LOG("Image: ");
	LOG(name.c_str());
	if (mapa[name] == nullptr) {
		LOG(" cannot be found\n");
		return false;
	}
	LOG(" could be found\n");
	return (p = mapa[name]) == mapa[name];
}
SDL_Texture* ModuleImatges::get(std::string name) {
	LOG("Image: ");
	LOG(name.c_str());
	LOG(mapa[name] == nullptr ? " cannot be found\n" : " could be found\n");
	return mapa[name];
}