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

//main function arguments are required for SDL2
int main(int argc, char* argv[]){
    Screen screen;
	for (int i = 0; i < 100; i++){
		screen.pixel(rand()%640, rand()%480);
	}

	while(true){
		screen.show();
		screen.input();
	}

    return 0;
}
//all:
//	g++ -I src/include -L src/lib -o Main main.cpp -lmingw32 -lSDL2main -lSDL2