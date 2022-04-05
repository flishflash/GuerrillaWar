#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2main.lib")
#pragma comment( lib, "SDL/libx86/SDL2.lib")

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#include "SDL_ttf/include/SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )
enum class main_states {
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};
Application* App = nullptr;
int main(int argc, char* argv[]) {
	ReportMemoryLeaks();
	int main_return = EXIT_FAILURE;
	main_states state = main_states::MAIN_CREATION;
	update_status status;
	while (state != main_states::MAIN_EXIT) {
		switch (state) {
			case main_states::MAIN_CREATION:
				LOG("Application Creation --------------\n");
				App = new Application();
				state = main_states::MAIN_START;
				break;
			case main_states::MAIN_START:
				LOG("Application Start --------------\n");
				if(!App->Init()) {
					LOG("Application Init exits with error -----\n");
					state = main_states::MAIN_EXIT;
				} else state = main_states::MAIN_UPDATE;
				break;
			case main_states::MAIN_UPDATE:
				status = App->Update();
				if (status == update_status::UPDATE_ERROR) {
					LOG("Application Update exits with error -----\n");
					state = main_states::MAIN_EXIT;
				}
				else if (status == update_status::UPDATE_STOP) state = main_states::MAIN_FINISH;
				break;
			case main_states::MAIN_FINISH:
				LOG("Application Finish --------------\n");
				if (App->CleanUp()) main_return = EXIT_SUCCESS;
				else LOG("Application CleanUp exits with error -----\n");
				state = main_states::MAIN_EXIT;
		}
	}
	delete App;
	return main_return;
}