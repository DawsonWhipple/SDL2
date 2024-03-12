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

const float _x_ROTATE = 0.02;
const float _y_ROTATE = 0.01;
const float _z_ROTATE = 0.04;

const int X_WINDOW_CENTER = WINDOW_WIDTH/4;
const int Y_WINDOW_CENTER = WINDOW_HEIGHT/4;

struct vec3{
	float x, y, z;
};

struct connection{
	int a, b;
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1){
	//apply the rotation to the given point
	//radian
	float rad = 0;
	//following is the function for rotatin points i guess (?)
	//Don't quite remember geometry class
	rad = x;
	point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
	point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

	rad = y;
	point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
	point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

	rad = z;
	point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
	point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}

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
	//draws 100 random pixels to the screen
	// for (int i = 0; i < 100; i++){
	// 	screen.pixel(rand()%640, rand()%480);
	// }

	//draws a square on the screen
	// line(screen, 100, 100, 200, 100);
	// line(screen, 200, 100, 200, 200);
	// line(screen, 200, 200, 100, 200);
	// line(screen, 100, 200, 100, 100);

	//all points in the cube
	//the vertices
	std::vector<vec3> points{
		{X_WINDOW_CENTER + 100, Y_WINDOW_CENTER + 100, 100},
		{X_WINDOW_CENTER + 200, Y_WINDOW_CENTER + 100, 100},
		{X_WINDOW_CENTER + 200, Y_WINDOW_CENTER + 200, 100},
		{X_WINDOW_CENTER + 100, Y_WINDOW_CENTER + 200, 100},

		{X_WINDOW_CENTER + 100, Y_WINDOW_CENTER + 100, 200},
		{X_WINDOW_CENTER + 200, Y_WINDOW_CENTER + 100, 200},
		{X_WINDOW_CENTER + 200, Y_WINDOW_CENTER + 200, 200},
		{X_WINDOW_CENTER + 100, Y_WINDOW_CENTER + 200, 200},
	};
	
	//defines all connections for the vertices of the square
	//the edges
	std::vector<connection> connections{
		{0,4},
		{1,5},
		{2,6},
		{3,7},

		{0,1},
		{1,2},
		{2,3},
		{3,0},

		{4,5},
		{5,6},
		{6,7},
		{7,4}
	};

	//find the center point of the cube
	vec3 centeroid{0, 0, 0};
	for(auto& p : points){
		centeroid.x += p.x;
		centeroid.y += p.y;
		centeroid.z += p.z;
	}
	//divide the total of all points by the number of vertices in the shape
	//in this case there are 8 for a cube
	//can also think of it as dividing the centroid by the size of the vector of vertice points
	centeroid.x /= points.size();	
	centeroid.y /= points.size();
	centeroid.z /= points.size();

	//game loop
	while(true){
		//rotate all points
		//then draw pixels to the screen
		//standard method of rotating in computer graphics
		for(auto& p : points){
			p.x -= centeroid.x;
			p.y -= centeroid.y;
			p.z -= centeroid.z;
			rotate(p, 0.002, 0.001, 0.004);
			p.x += centeroid.x;
			p.y += centeroid.y;
			p.z += centeroid.z;
			screen.pixel(p.x, p.y);
		}
		for(auto& conn : connections){
			line(screen, points[conn.a].x, 
						 points[conn.a].y,
						 points[conn.b].x,
						 points[conn.b].y);
		}
		screen.show();
		screen.clear();

		screen.input();
		//delays for 30 milliseconds
		SDL_Delay(5);
	}

    return 0;
}
//all:
//	g++ -I src/include -L src/lib -o Main main.cpp -lmingw32 -lSDL2main -lSDL2