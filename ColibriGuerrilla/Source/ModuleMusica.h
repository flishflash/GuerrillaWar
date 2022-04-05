#pragma once
#include "Module.h"
#include <filesystem>
#include <string>
#include <map>
#include "SDL_mixer/include/SDL_mixer.h"
#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200
class ModuleMusica : public Module {
	public:
		std::map<std::string, Mix_Music*> mapaMusic;
		std::map<std::string, Mix_Chunk*> mapaSFX;
		bool CleanUp() override;
		bool loadMusic(std::filesystem::directory_entry);
		bool loadSFX(std::filesystem::directory_entry);
		bool playMusic(std::string name, float fade_time = DEFAULT_MUSIC_FADE_TIME);
		bool playSFX(std::string name, int repeat = 0);
		bool Init() override;
};