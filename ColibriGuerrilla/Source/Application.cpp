#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleImatges.h"
#include "ModuleMusica.h"
#include "ModuleScene.h"
#include "ModuleText.h"
#include "ModuleCollisions.h"

Application::Application() {
	modules[0] = window = new ModuleWindow();
	modules[1] = input = new ModuleInput();
	modules[2] = imatges = new ModuleImatges();
	modules[3] = audio = new ModuleMusica();

	modules[4] = scene = new ModuleScene();
	modules[5] = player = new ModulePlayer();

	modules[6] = particles = new ModuleParticles();
	modules[7] = collisions = new ModuleCollisions();

	modules[8] = render = new ModuleRender();
}

Application::~Application() {
	for (int i = 0; i < NUM_MODULES; ++i) {
		delete modules[i];
		modules[i] = nullptr;
	}
}
// INIT all modules
bool Application::Init() {
	bool ret = true;
	for (int i = 0; i < NUM_MODULES && ret; ++i) ret = modules[i]->Init();
	LOG("INITED CORRECTLY\n");
	for (int i = 0; i < NUM_MODULES&& ret; ++i) ret = modules[i]->Start();
	return ret;
}

update_status Application::Update() {
	update_status ret = update_status::UPDATE_CONTINUE;
	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i) ret = modules[i]->PreUpdate();
	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i) ret = modules[i]->Update();
	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i) ret = modules[i]->PostUpdate();
	return ret;
}
 
bool Application::CleanUp() {
	bool ret = true;
	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i) {
		ret = modules[i]->CleanUp();
	}
	return ret;
}