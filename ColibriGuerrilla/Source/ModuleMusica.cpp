#include "ModuleMusica.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
bool ModuleMusica::CleanUp() {
	for (std::map<std::string, Mix_Music*>::iterator iterador = mapaMusic.begin(); iterador != mapaMusic.end(); iterador++) {
		Mix_FreeMusic(iterador->second);
	}
	for (std::map<std::string, Mix_Chunk*>::iterator iterador = mapaSFX.begin(); iterador != mapaSFX.end(); iterador++) {
		Mix_FreeChunk(iterador->second);
	}
	Mix_CloseAudio();
	return true;
}
bool ModuleMusica::Init() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		LOG("Audio library has not been initialized.\n");
		LOG(SDL_GetError());
		return false;
	}
	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) {
		LOG("Audio library has not been initialized.\n");
		LOG(SDL_GetError());
		LOG("\n");
		return false;
	}
	for (const auto& entry : std::filesystem::directory_iterator("./Assets")) {
		if (entry.is_regular_file() && !entry.path().extension().compare(".ogg")) {
			if (!loadMusic(entry)) return false;
		}
	}
	for (const auto& entry : std::filesystem::directory_iterator("./Assets")) {
		if (entry.is_regular_file() && !entry.path().extension().compare(".wav")) {
			if (!loadMusic(entry)) return false;
		}
	}
	return true;
}
bool ModuleMusica::loadMusic(std::filesystem::directory_entry file) {
	mapaMusic[file.path().stem().string()] = Mix_LoadMUS(file.path().string().c_str());
	LOG(file.path().string().c_str());
	if (mapaMusic[file.path().stem().string()] == NULL) {
		LOG(" has not been loaded.\n");
		LOG(SDL_GetError());
		LOG("\n");
		return false;
	}
	LOG(" has been loaded.\n");
	return true;
}

bool ModuleMusica::loadSFX(std::filesystem::directory_entry file) {
	mapaSFX[file.path().stem().string()] = Mix_LoadWAV(file.path().string().c_str());
	LOG(file.path().string().c_str());
	if (mapaSFX[file.path().stem().string()] == NULL) {
		LOG(" has not been loaded.\n");
		LOG(SDL_GetError());
		LOG("\n");
		return false;
	}
	LOG(" has been loaded.\n");
	return true;
}
bool ModuleMusica::playMusic(std::string name, float fade_time)
{
	bool ret = true;
	if (mapaMusic[name] != nullptr) {
		if (fade_time > 0.0f) {
			// Warning: This call blocks the execution until fade out is done
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		} else {
			Mix_HaltMusic();
		}
	}
	if (mapaMusic[name] == nullptr) {
		LOG("Cannot play music %s. Mix_GetError(): %s\n", name.c_str(), Mix_GetError());
		ret = false;
	}
	else {
		if (fade_time > 0.0f) {
			if (Mix_FadeInMusic(mapaMusic[name], -1, (int)(fade_time * 1000.0f)) < 0) {
				LOG("Cannot fade in music %s. Mix_GetError(): %s", name, Mix_GetError());
				ret = false;
			}
		}
		else {
			if (Mix_PlayMusic(mapaMusic[name], -1) < 0) {
				LOG("Cannot play in music %s. Mix_GetError(): %s", name, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", name);
	return ret;
}

bool ModuleMusica::playSFX(std::string name, int repeat) {
	if (mapaSFX[name] != nullptr) {
		Mix_PlayChannel(-1, mapaSFX[name], repeat);
		return true;
	}
	return false;
}