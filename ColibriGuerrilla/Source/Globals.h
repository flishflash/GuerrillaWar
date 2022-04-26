#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <windows.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);


typedef unsigned int uint;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define RES_WIDTH 227
#define RES_HEIGHT 366 

#define SDL_FLIP_BOTH (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL)

enum class update_status {
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

constexpr auto NUM_MODULES = 12;

#endif // _GLOBALS_H_