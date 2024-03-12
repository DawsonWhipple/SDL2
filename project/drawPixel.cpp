/****************************************************************************
* Title:          drawPixel.cpp
* Author:         Dawson Whipple
* Date:           3/8/24
* Description:    Learning SDL2 library in c++, draws a single pixel to the screen
****************************************************************************/
#include <SDL.h>

//main function arguments are required for SDL2
int main(int argc, char* argv[]){
    //need window and renderer as part of init
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    //initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    //initialize window and renderer
    //*4 for a high dpi screen, sets scale to be larger so pixel is visible
    SDL_CreateWindowAndRenderer(640,480, 0, &window, &renderer);

    //tells SDL what color we want to use to draw the renderer
    //in RGBA
    //resets screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //sets draw color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //draws a single point to the center of the screen (due to the /2)
    SDL_RenderDrawPoint(renderer, 640/2, 480/2);

    //present the renderer (showing it to the window so the user can see it)
    SDL_RenderPresent(renderer);
    //holds the program open for 10000 milliseconds
    SDL_Delay(10000);

    return 0;
}