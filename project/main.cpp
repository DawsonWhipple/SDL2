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
****************************************************************************/
//for snake game screen.h is not required
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
//snake body will be a doubly ended queue
#include <deque>
#include <ctime>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

const int SPEED = 10;

//main function arguments are required for SDL2
int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;

	// Seed the random number generator with the current time
    std::srand(std::time(nullptr));
	enum Direction{
		DOWN, LEFT, RIGHT, UP
	};

	bool running = true;
	//direction the snake is going
	int dir = 0;
	//create the head of the snake at the center of the screen
	SDL_Rect head {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 10, 10};

	//snake body container
	std::deque<SDL_Rect> rq;
	//size of snake
	int size = 1;
	//apple container
	//std::vector<SDL_Rect> apples;
	SDL_Rect apple {rand()%99 *10, rand()%99 * 10, 10, 10};

	//create apples on the map
	// for(int i = 0; i < 100; i++){
	// 	SDL_Rect rect = {rand()%100 *10, rand()%100 * 10, 10, 10};
    // 	apples.push_back(rect);
	// }
	// SDL_Rect rect = {rand()%100 *10, rand()%100 * 10, 10, 10};
    // apples.push_back(rect);

	//game loop
	while(running){
		//Check user input
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT){
				running = false;
			}
			//check for user input
			if(e.type == SDL_KEYDOWN){
				//check which specific key was pressed
				switch(e.key.keysym.sym){
					case SDLK_DOWN:
						if(dir != UP){dir = DOWN;}
						break;
					case SDLK_UP:
						if(dir != DOWN){dir = UP;}
						break;
					case SDLK_LEFT:
						if(dir != RIGHT){dir = LEFT;}
						break;
					case SDLK_RIGHT:
						if(dir != LEFT){dir = RIGHT;}
						break;
				}
			}
		}
		//move
		switch(dir){
			case DOWN:
				head.y += SPEED;
				break;
			case UP:
				head.y -= SPEED;
				break;
			case LEFT:
				head.x -= SPEED;
				break;
			case RIGHT:
				head.x += SPEED;
				break;
		}
		if(head.x == apple.x && head.y == apple.y){
			//increase size of snake
			size += 10;
			//randomly select a new location for the apple
			apple = {rand()%99 *10, rand()%99 * 10, 10, 10};
		}
		//collision detection with apple
		// std::for_each(apples.begin(), apples.end(), [&](auto& apple){
		// 	//check every single apple against the snake
		// 	if(head.x == apple.x && head.y == apple.y){
		// 		//increase size of snake
		// 		size += 10;
		// 		//move apple to off screen
		// 		apples.pop_back();
		// 		SDL_Rect rect = {rand()%100 *10, rand()%100 * 10, 10, 10};
    	// 		apples.push_back(rect);
		// 	}
		// });
		if(head.x > WINDOW_WIDTH){
			head.x = 0;
		}
		if(head.x < 0){
			head.x = WINDOW_WIDTH;
		}
		if(head.y > WINDOW_HEIGHT){
			head.y = 0;
		}
		if(head.y < 0){
			head.y = WINDOW_HEIGHT;
		}
		//collision detection with snake body
		std::for_each(rq.begin(), rq.end(), [&](auto& snake_segment){
			if(head.x == snake_segment.x && head.y == snake_segment.y){
				size = 1;
			}
			if(snake_segment.x > WINDOW_WIDTH){
				snake_segment.x = 0;
			}
			if(snake_segment.x < 0){
				snake_segment.x = WINDOW_WIDTH;
			}
			if(snake_segment.y > WINDOW_HEIGHT){
				snake_segment.y = 0;
			}
			if(snake_segment.y < 0){
				snake_segment.y = WINDOW_HEIGHT;
			}
		});
		//put head to the front of the queue
		rq.push_front(head);
		//pop tail from queue
		while(rq.size() > size){
			rq.pop_back();
		}

		//clear window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Draw Body
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &head);
		//render the whole snake including head
		std::for_each(rq.begin(), rq.end(), [&](auto& snake_segment){
			//draw rect to the screen
			SDL_RenderFillRect(renderer, &snake_segment);
		});
		//Draw apples
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &apple);
		// std::for_each(apples.begin(), apples.end(), [&](auto& apple){
		// 	SDL_RenderFillRect(renderer, &apple);
		// });

		//display
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}
    return 0;
}
//all:
//	g++ -I src/include -L src/lib -o Main main.cpp -lmingw32 -lSDL2main -lSDL2