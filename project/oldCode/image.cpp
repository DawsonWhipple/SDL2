/****************************************************************************
* Title:          SDL2main.cpp
* Author:         Dawson Whipple
* Date:           3/8/24
* Description:    Learning SDL2 library in c++, this file continually updates as I learn new things
* Checklist:      each of the following states can be found in the associated .cpp files as backups
*   - Draw a Pixel to screen (drawpixel.cpp)
*   - Able to accept user input, also draw rectangle (event.cpp)
*   - Render a texture (texture.cpp)
*   - Render an Image (image.cpp)
****************************************************************************/
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>

//main function arguments are required for SDL2
int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
		return 1;
	}
		
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "Error SDL2_image Initialization";
		return 2;
	}

	SDL_Window* window = SDL_CreateWindow("Rilakkuma", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 546, 420, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		std::cout << "Error window creation";
		return 3;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Error renderer creation";
		return 4;
	}

	SDL_Surface* rilakkuma_sur = IMG_Load("res/rilakkuma2.png");
	if (rilakkuma_sur == NULL) {
		std::cout << "Error loading image: " << IMG_GetError();
		return 5;
	}

	SDL_Texture* rilakkuma_tex = SDL_CreateTextureFromSurface(renderer, rilakkuma_sur);
	if (rilakkuma_tex == NULL) {
		std::cout << "Error creating texture";
		return 6;
	}

	SDL_FreeSurface(rilakkuma_sur);

	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, rilakkuma_tex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(rilakkuma_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

    return 0;
}