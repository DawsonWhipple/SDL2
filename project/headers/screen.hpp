#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <time.h>  
#include <vector>
#include <tuple>
#include <algorithm>
#include <ctime>
#include <cmath>

#pragma once

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int CELL_SIZE = 10;
const int SCALE = 2;
// OldRange = (OldMax - OldMin)  
// NewRange = (NewMax - NewMin)  
// NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
float mapValue(float oldValue, float oldMin, float oldMax, float newMin, float newMax) {
    float oldRange = oldMax - oldMin;
    float newRange = newMax - newMin;
    return (((oldValue - oldMin) * newRange) / oldRange) + newMin;
}
class Screen {

    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> pointLocations;
    std::vector<SDL_Color> pointColors; // Vector of SDL_Color for storing RGB colors

    public:
    //constructor
    Screen(){
        SDL_Init(SDL_INIT_VIDEO);
        //create window and renderer
        //*2 has to do with the scale and I believe resolution of monitor(?)
        //could need adjusting and not entirely sure what will be best for my monitor
        //SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
        SDL_CreateWindowAndRenderer(WINDOW_WIDTH*SCALE, WINDOW_HEIGHT*SCALE, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, SCALE, SCALE);
    }

    //Need to know how to tell the computer where the pixels are to draw the 
    //Add new points to the vector 'points' everytime we want to draw a point
    //specify where the point will be
    //this function draws the pixesl but does not display them to the screen
    void pixel(float x, float y){
        //creates a new point struct and adds it to the points vector
        //function push_back() apparently does the same thing
        // Create a new point with x and y coordinates
        SDL_FPoint point = {x, y};
        // Add the new point to the points vector
        pointLocations.push_back(point);
    }
    //this function draws the pixesl but does not display them to the screen
    void drawPixel(float x, float y, int r, int g, int b){
        //creates a new point struct and adds it to the points vector
        //function push_back() apparently does the same thing
        // Create a new point with x and y coordinates
        SDL_FPoint point = {x, y};
        // Create a new SDL_Color struct for the specified RGB values
        SDL_Color color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255};
        // Add the new point to the points vector
        pointLocations.push_back(point);
        // Add the corresponding color to the pointColors vector
        pointColors.push_back(color);
    }
    //shows pixels to the screen
    //The most 'SDL' function in this .h file
    void show(){
        //set draw color to black, then clear whole screen
        //basically just set to black, resets the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //go through every pixel and draw it to the screen
        //does not display to screen yet
        for(int i = 0; i < pointLocations.size(); i++){
            //set draw color of each pixel
            SDL_SetRenderDrawColor(renderer, pointColors[i].r, pointColors[i].g, pointColors[i].b, pointColors[i].a);
            SDL_RenderDrawPointF(renderer, pointLocations[i].x, pointLocations[i].y);
        }
        //displays to screen
        SDL_RenderPresent(renderer);
    }
    //clears the screen of all points
    void clear(){
        pointLocations.clear();
        pointColors.clear();
    }
    //go through inputs and see what they are
    //in this case only checks if user closes the window
    void input(){
        //check if the user clicked 'x' on the window, exits program
        // Check for input events
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                    break;
                default:
                    break;
            }
        }
    }
    //go through inputs and see what they are
    //in this case only checks if user closes the window
    void inputMandelbrot(float *newMin, float *newMax, bool *autozoom){
        //check if the user clicked 'x' on the window, exits program
        // Check for input events
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    //check which specific key was pressed
                    switch(e.key.keysym.sym){
                        case SDLK_DOWN:
                            *newMin += 0.01;
                            break;
                        case SDLK_UP:
                            *newMin -= 0.01;
                            break;
                        case SDLK_LEFT:
                            *newMax -= 0.01;
                            //*newMin -= 0.1;
                            break;
                        case SDLK_RIGHT:
                            *newMax += 0.01;
                            //*newMin += 0.01;
                            break;
                        case SDLK_a:
                            *autozoom = !*autozoom;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    x = mapValue(x, 0, WINDOW_WIDTH, *newMin, *newMax);
                    y = mapValue(y, 0, WINDOW_HEIGHT, *newMin, *newMax);
                    *newMin = (*newMin + x)/2;
                    *newMax = (*newMax + y)/2;
                    break;
                default:
                    break;
            }
        }
    }
    //overloaded function for gameOfLife.cpp
    //go through inputs and see what they are
    //in this case only checks if user closes the window
    void input(std::vector<std::vector<int>>& display){
        //check if the user clicked 'x' on the window, exits program
        // Check for input events
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);
                    break;
                //this case is specifically for gameOfLife
                case SDL_MOUSEBUTTONDOWN: {
                    
                    // Get the mouse position
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    // Convert mouse coordinates to cell coordinates
                    int cellX = mouseX / SCALE;
                    int cellY = mouseY / SCALE;

                    // Ensure the cell coordinates are within the bounds
                    if (cellX >= 0 && cellX < WINDOW_WIDTH && cellY >= 0 && cellY < WINDOW_HEIGHT) {
                        // Set the cell state to alive
                        display[cellY][cellX] = 1;
                        display[cellY+1][cellX] = 1;
                        display[cellY][cellX+1] = 1;
                        display[cellY-1][cellX] = 1;
                        display[cellY][cellX-1] = 1;
                        //std::cout << "MOUSE";
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

};