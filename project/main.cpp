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
#include "headers/screen.hpp"
#include <numeric>
#include <cmath>
#include <iostream>

//Function for drawing a line to the screen
//x1, y1 are start point coords
//x2, y2 are end point coords
void line(Screen& screen, float x1, float y1, float x2, float y2){
	//find difference between the two points
	float dx = x2 - x1;
	float dy = y2 - y1;

	//find the length of the line
	//pythagorean theorom
	float length = std::sqrt((dx*dx) + (dy*dy));

	//finds the angle of the line
	//atan2 is a special function that prevents division by 0
	float angle = std::atan2(dy, dx);

	//use pixel function to draw the line
	for(float i = 0; i < length; i++){
		//getting the forward vector
		//sin and cos are the vector math, * i scales up the pixels
		screen.pixel(x1 + std::cos(angle) * i, 
					 y1 + std::sin(angle) * i);
	}
}

//main function arguments are required for SDL2
int main(int argc, char* argv[]){
    Screen screen;
	for (int i = 0; i < 100; i++){
		screen.pixel(rand()%640, rand()%480);
	}

	line(screen, 0, 0, 400, 100);
	
	while(true){
		screen.show();
		screen.input();
	}

    return 0;
}
//all:
//	g++ -I src/include -L src/lib -o Main main.cpp -lmingw32 -lSDL2main -lSDL2