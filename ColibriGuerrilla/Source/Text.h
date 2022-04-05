#pragma once
#include "Globals.h"
#include "Application.h"
#include <string>
class Text {
	public:
		SDL_Surface* surface;
		bool isAnimating = false;
		SDL_Texture* texture;
		std::string font;
		std::string text;
		std::string partial = "";
		int size;
		int red;
		int green;
		int blue;
		int alpha;
		int rotation;
		/*void update() {
			partial = text.substr(0, partial.length() + 1);
			if (isAnimating) {
				if ((SDL_GetTicks() / 16) % 10 == 0) {
					if (partial.length() < text.length()) {
						alpha = min(255, alpha + 10);
					}
					else isAnimating = false;
				}
				rotation += 3;
			}
		}
		void draw() {
			surface = TTF_RenderText_Blended_Wrapped(App->text->get("font", 72), partial.c_str(), SDL_Color(red, green, blue, alpha), 0);
			SDL_DestroyTexture(texture);
			texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);
			App->render->Blit(texture, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
			SDL_FreeSurface(surface);
		}*/
};

