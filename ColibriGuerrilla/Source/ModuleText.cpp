#include "ModuleText.h"
#include "Application.h"
bool ModuleText::Init() {
	if (TTF_Init() == -1) {
		LOG("TTF has not been initialized");
		LOG(TTF_GetError());
		return false;
	}
	for (int i = 12; i <= 240; i += 12) {
		load("font", i);
	}
	return true;
}
bool ModuleText::load(std::string name, int size) {
	std::string ex = "Fonts/" + name + ".ttf";
	fonts[name][size] = TTF_OpenFont(ex.c_str(), size);
	if (fonts[name][size] == NULL) {
		LOG("Font has not been created.\n");
		LOG(TTF_GetError());
		LOG("\n");
		return false;
	}
	return true;
}
update_status ModuleText::Update() {
	return update_status::UPDATE_CONTINUE;
}
update_status ModuleText::PostUpdate() {
	return update_status::UPDATE_CONTINUE;
}
bool ModuleText::CleanUp() {
	
	for (int i = 12; i <= 240; i += 12) {
		TTF_CloseFont(fonts["name"][i]);
	}
	TTF_Quit();
	return true;
}