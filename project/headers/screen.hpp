#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <time.h>  
#include <vector>
#include <tuple>
#include <algorithm>
#include <ctime>

#pragma once

const int WINDOW_WIDTH = 200;
const int WINDOW_HEIGHT = 200;
const int CELL_SIZE = 10;
class Screen {

    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;
    public:
    //constructor
    Screen(){
        SDL_Init(SDL_INIT_VIDEO);
        //create window and renderer
        //*2 has to do with the scale and I believe resolution of monitor(?)
        //could need adjusting and not entirely sure what will be best for my monitor
        //SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
        SDL_CreateWindowAndRenderer(WINDOW_WIDTH*4, WINDOW_HEIGHT*4, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 4, 4);
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
        points.push_back(point);
    }
    //shows pixels to the screen
    //The most 'SDL' function in this .h file
    void show(){
        //set draw color to black, then clear whole screen
        //basically just set to black, resets the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //set draw color to white now so we can actually see the pixels
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //go through every pixel and draw it to the screen
        //does not display to screen yet
        for(auto& point : points){
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }
        //displays to screen
        SDL_RenderPresent(renderer);
    }
    //clears the screen of all points
    void clear(){
        points.clear();
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
                    int cellX = mouseX / 4;
                    int cellY = mouseY / 4;

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