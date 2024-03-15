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
****************************************************************************/
#include "headers/screen.hpp" // Include the header file with the Screen class
#include <map>

// Function to update the game state for the next generation
void updateGame() {
    // Compute the next generation
    for (int i = 0; i < WINDOW_WIDTH; ++i) {
        for (int j = 0; j < WINDOW_HEIGHT; ++j) {
            //swap[j][i] = isAlive(display, i, j) ? 1 : 0;
        }
    }
}

float mapValue(float oldValue, float oldMin, float oldMax, float newMin, float newMax) {
    float oldRange = oldMax - oldMin;
    float newRange = newMax - newMin;
    return (((oldValue - oldMin) * newRange) / oldRange) + newMin;
}


int main(int argc, char* argv[]) {
    // Initialize SDL and create a Screen object
    Screen screen;  
    float newMax = 2;
    float newMin = -2; 
    float newRange = (newMax - newMin);
    int count = 0;
    int oldMax = WINDOW_HEIGHT;
    int oldMin = 0;
    int OldRange = (oldMax - oldMin);
    // Main loop
    while (true) {
        // Process input events
        screen.inputMandelbrot(&newMax, &newMin);
        // Update the game state for the next generation
        //updateGame();

        // Clear the screen
        screen.clear();
        // OldRange = (OldMax - OldMin)  
        // NewRange = (NewMax - NewMin)  
        // NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
        // Draw the game state to the screen
        int color = 50;
        int r = color;
        int g = color;
        int b = color;
        
        int maxIterations = 100;
        // float newMax = 2;
        // float newMin = -2;
        //std::cout << "New Max" << newMax << '\n';
        //std::cout << "New Min" << newMin << '\n';
        //newRange = (newMax - newMin);
        //std::cout << "New Range" << newRange << '\n';
        //count++;
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            for (int y = 0; y < WINDOW_HEIGHT; ++y) {
                //mapping size of screen onto the size of the mandelbrot set
                float real = mapValue(x, 0, WINDOW_WIDTH, newMin, newMax);
                float imaginary = mapValue(y, 0, WINDOW_HEIGHT, newMin, newMax);

                
                float a = real;
                float b = imaginary;
                float ca = real;
                float cb = imaginary;
                if((x+y)%20 == 0){
                    //std::cout << "Mapped values - a: " << a << ", b: " << b << std::endl; // Debug output
                }
                
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
                // float a = mapValue(x, 0, WINDOW_WIDTH, newMin, newMax);
                // float b = mapValue(y, 0, WINDOW_HEIGHT, newMin, newMax);
                // // float a = (static_cast<float>(x) * newRange / WINDOW_WIDTH) + newMin;
                // // float b = (static_cast<float>(y) * newRange / WINDOW_HEIGHT) + newMin;
                // // float a = (((x - 0) * newRange) / OldRange) + newMin;
                // // float b = (((y - 0) * newRange) / OldRange) + newMin;
                
                // //stores the original values of a and b
                // float ca = a;
                // float cb = b;
                // int n = 0;
                // //checks for if a given value will tend towards infinity
                // while(n < maxIterations){
                //     float aa = a*a - b*b;
                //     float bb = 2 * a * b;

                //     a = aa + ca;
                //     b = bb + cb;
                //     if(abs(a+b) > 16){
                //         break;
                //     }
                //     n++;
                // }
                // int bright = mapValue(n, 0, maxIterations, 0, 255);
                //std::cout << n << '\n';
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
        // oldMin = newMin;
        // oldMax = newMax;
        // OldRange = newRange;

        // Display the updated screen
        screen.show();
        // Delay for a short interval
        SDL_Delay(25);
    }

    return 0;
}