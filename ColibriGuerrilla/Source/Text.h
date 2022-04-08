#pragma once
#include "Globals.h"
#include "Application.h"
#include <string>
#include <cmath>
#include "SDL/include/SDL_pixels.h"
class Text {
	public:
		Text(std::string, std::string, int);
		SDL_Surface* surface;
		bool isAnimating = false;
		SDL_Texture* texture;
		std::string font;
		int size;
		std::string text;
		int fpc = 10;
		int cC = 10;
		std::string partial = "";
		SDL_Color color;
		int rotation;
		void update() {
			partial = text.substr(0, partial.length() + 1);
			if (isAnimating) {
				if (cC == 0) {
					if (partial.length() < text.length()) {
						color.a = min(255, color.a + 10);
						cC = fpc;
					}
					else {
						isAnimating = false;
						cC = -1;
					}
				}
				else {
					cC--;
				}
				rotation += 3;
			}
		}
		void draw() {
			surface = TTF_RenderText_Blended_Wrapped(App->text->get("font", 72), partial.c_str(), color, 0);
			SDL_DestroyTexture(texture);
			texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);
			App->render->Blit(texture, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
			SDL_FreeSurface(surface);
		}
};

