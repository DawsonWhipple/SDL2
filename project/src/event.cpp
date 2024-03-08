/****************************************************************************
* Title:          SDL2main.cpp
* Author:         Dawson Whipple
* Date:           3/8/24
* Description:    Learning SDL2 library in c++, this file adds user input, event handling, game loop
* Checklist:      each of the following states can be found in the associated .cpp files as backups
*   - Draw a Pixel to screen (drawpixel.cpp)
*   - Able to accept user input, also draw rectangle (event.cpp)
****************************************************************************/
#include <SDL.h>
#include <iostream>

//main function arguments are required for SDL2
int main(int argc, char* argv[]){
    //need window and renderer as part of init
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Event e;
    //initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //var that determines whether the game is running
    bool running = true;
    //defines the size of the rectangle to be drawn later
    SDL_Rect r{10, 10, 250, 250};

    //initialize window and renderer
    //*4 for a high dpi screen, sets scale to be larger so pixel is visible
    SDL_CreateWindowAndRenderer(1280,720, 0, &window, &renderer);
    //main game loop
    while(running){
        //checks for events while the game is running
        while(SDL_PollEvent(&e)){
            //if the user clicks the 'x' on the window
            if(e.type == SDL_QUIT){
                running = false;
            }
            //if the user presses a key
            else if(e.type == SDL_KEYDOWN){
                //figures out which specific key was pressed
                switch(e.key.keysym.sym){
                    case SDLK_RIGHT:
                        std::cout << "Right Key was pressed" << '\n';
                        r.x += 50;
                        break;
                }
                //std::cout << "Key was pressed" << '\n';
            }
            //when the key is released
            else if(e.type == SDL_KEYUP){
                //figures out which specific key was pressed
                switch(e.key.keysym.sym){
                    case SDLK_RIGHT:
                        std::cout << "Right Key was released" << '\n';
                        break;
                }
            }
            //checks if the mouse has moved
            else if(e.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&r.x, &r.y);
            }
        }
        //tells SDL what color we want to use to draw the renderer
        //in RGBA
        //resets screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        //sets draw color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //draws a rectangle to the screen
        SDL_RenderFillRect(renderer, &r);

        //present the renderer (showing it to the window so the user can see it)
        SDL_RenderPresent(renderer);

    }

    return 0;
}