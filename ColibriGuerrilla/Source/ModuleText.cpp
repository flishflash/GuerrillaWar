#include "ModuleText.h"
#include "Application.h"
bool ModuleText::Init() {
	if (TTF_Init() == -1) {
		LOG("TTF has not been initialized");
		LOG(TTF_GetError());
		return false;
	}
	for (int size = 12; size <= 120; size += 12) {
		for (const auto& entry : std::filesystem::directory_iterator("./Fonts")) {
			if (entry.is_regular_file() && !entry.path().extension().compare(".ttf")) {
				fonts[entry.path().stem().string()][size] = TTF_OpenFont(entry.path().string().c_str(), size);
				LOG(entry.path().string().c_str());
				if (fonts[entry.path().stem().string()][size] == NULL) {
					LOG(" Font has not been created.\n");
					LOG(TTF_GetError());
					LOG("\n");
					return false;
				}
				LOG(" Font has been created.\n");
			}
		}
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