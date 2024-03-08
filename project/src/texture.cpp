/****************************************************************************
* Title:          SDL2main.cpp
* Author:         Dawson Whipple
* Date:           3/8/24
* Description:    Learning SDL2 library in c++, aggresively flashes colors on the screen
*                 Color flashing is intential, I thought it'd be fun lol
* Checklist:      each of the following states can be found in the associated .cpp files as backups
*   - Draw a Pixel to screen (drawpixel.cpp)
*   - Able to accept user input, also draw rectangle (event.cpp)
*   - Render a texture (texture.cpp)
****************************************************************************/
#include <SDL.h>
#include <iostream>
int WAIT_TIME = 1000;
//main function arguments are required for SDL2
int main(int argc, char* argv[]){
    //var that determines whether the game is running
    bool running = true;
    //initializes SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    auto window = SDL_CreateWindow("Textures",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   1280, 720, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_Event e;

    //create textures
    //creates a texture struct
    auto red_texture = SDL_CreateTexture(renderer,
                                         SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET,
                                         1280, 720);
    auto green_texture = SDL_CreateTexture(renderer,
                                         SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET,
                                         1280, 720);
    auto blue_texture = SDL_CreateTexture(renderer,
                                         SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET,
                                         1280, 720);
    //draw textures
    //set the target to be the red texture
    SDL_SetRenderTarget(renderer, red_texture);
    //set the red texture to red, previously was nothing
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    //set the target to be the blue texture
    SDL_SetRenderTarget(renderer, blue_texture);
    //set the red texture to blue, previously was nothing
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    //set the target to be the red texture
    SDL_SetRenderTarget(renderer, green_texture);
    //set the red texture to red, previously was nothing
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    //sets render target back to the window
    SDL_SetRenderTarget(renderer, nullptr);
    //show textures
    while(running){
        //checks for events while the game is running
        while(SDL_PollEvent(&e)){
            //if the user clicks the 'x' on the window
            if(e.type == SDL_QUIT){
                running = false;
            }
            //if the user presses a key
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_RIGHT:
                        WAIT_TIME -= 100;
                        break;
                    case SDLK_LEFT:
                        WAIT_TIME += 100;
                        break;
                    case SDLK_SPACE:
                        running = false;
                        break;
                }
            }
        }
        SDL_RenderCopy(renderer, red_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_Delay(WAIT_TIME);
        SDL_RenderCopy(renderer, green_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_Delay(WAIT_TIME);
        SDL_RenderCopy(renderer, blue_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_Delay(WAIT_TIME);
    }
    //copy the texture to the window
    // SDL_RenderCopy(renderer, red_texture, nullptr, nullptr);
    // SDL_RenderPresent(renderer);
    // SDL_Delay(5000);

    // SDL_RenderCopy(renderer, blue_texture, nullptr, nullptr);
    // SDL_RenderPresent(renderer);
    // SDL_Delay(5000);

    return 0;
}