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
*	- Rotate a 3d cube (cubeRotate.cpp) (RotatingCube.exe)
*	- Snake Game (snake.cpp) (snake.exe)
*   - Game of Life (gameOfLife.cpp) (gameOfLife.exe)
*   - MandelBrot Set render (mandelbrotSet.cpp) (mandelbrotSet.exe)
****************************************************************************/
#include "headers/screen.hpp" // Include the header file with the Screen class
#include <math.h>

#define START_POS -0.5
#define START_ZOOM (WINDOW_WIDTH * 0.25296875L) - 200

// Function to update the game state for the next generation
void updateGame() {
    // Compute the next generation
    for (int i = 0; i < WINDOW_WIDTH; ++i) {
        for (int j = 0; j < WINDOW_HEIGHT; ++j) {
            //swap[j][i] = isAlive(display, i, j) ? 1 : 0;
        }
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL and create a Screen object
    Screen screen;  

    SDL_FPoint center = {START_POS, START_POS};


    int oldMax = WINDOW_HEIGHT;
    int oldMin = 0;
    int OldRange = (oldMax - oldMin);
    bool autozoom = false;
    float increment = 0.01;
    //float incrementCount = 0.001;
    long int zoomCount = 0;
    //center = {-1.315180982097868, 0.073481649996795};

    float newMax = 1;
    float newMin = -1; 
    std::cout << newMin;
    // Main loop
    while (true) {
        // Process input events
        screen.inputMandelbrot(&newMax, &newMin, &autozoom);
        // Update the game state for the next generation
        //updateGame();

        // Clear the screen
        screen.clear();

        // Draw the game state to the screen
        int color = 50;
        int r = color;
        int g = color;
        int b = color;
        
        int maxIterations = 100;
        
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            for (int y = 0; y < WINDOW_HEIGHT; ++y) {
                //mapping size of screen onto the size of the mandelbrot set
                float real = mapValue(x, 0, WINDOW_WIDTH, newMin, newMax);
                float imaginary = mapValue(y, 0, WINDOW_HEIGHT, newMin, newMax);

                
                float a = real;
                float b = imaginary;
                float ca = real;
                float cb = imaginary;
                
                int n = 0;
                while(n < maxIterations){
                    float aa = a * a - b * b;
                    float bb = 2 * a * b;

                    a = aa + ca;
                    b = bb + cb;

                    if(abs(a+b) > 16){
                        break;
                    }
                    n++;
                }

                // Map the iteration count to a brightness value
                int bright = mapValue(n, 0, maxIterations, 0, 255);
                if (n == 100){
                    bright = 0;
                }
                
                screen.drawPixel(x, y, bright, bright, bright);
                
                //this block makes some cool patterns but not very useful
                // if (b >= 255){
                //     r = 0;
                //     g = 0;
                //     b = 0;
                // }
                // else if (g >= 255){
                //     b = (((i*j - 0) * NewRange)/OldRange) + 0;
                // }
                // else if(r >= 255){
                //     g = (((i*j - 0) * NewRange)/OldRange) + 0;
                // }
                // else{
                //     r = (((i*j - 0) * NewRange)/OldRange) + 0;
                // }
                // screen.drawPixel(j, i, r, g, b);
            }
        }
        //increment = 0.01;
        
        if(autozoom){
            if((newMin + (increment*2)) >= center.x){
                increment /= 10.0;
            }
            newMin += increment;
            newMax -= increment;
            zoomCount++;
            std::cout << increment << '\n';
        }        

        // Display the updated screen
        screen.show();
        
        //Delay for a short interval
        //SDL_Delay(10);
    }

    return 0;
}