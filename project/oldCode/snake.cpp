/****************************************************************************
* Title:          SDL2main.cpp
* Author:         Dawson Whipple
* Date:           3/8/24
* Description:    game of snake made using SDL2
* Checklist:      each of the following states can be found in the associated .cpp files as backups
*   - Draw a Pixel to screen (drawpixel.cpp)
*   - Able to accept user input, also draw rectangle (event.cpp)
*   - Render a texture (texture.cpp)
*   - Render an Image (image.cpp)
*	- Rotate a 3d cube (cubeRotate.cpp) (RotatingCube.exe)
*	- Snake Game (snake.cpp) (snake.exe)
****************************************************************************/
//for snake game screen.h is not required
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <algorithm>
//snake body will be a doubly ended queue
#include <deque>
#include <ctime>
#include <string>

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;
int SPEED = 10;

//main function arguments are required for SDL2
int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;

	// Seed the random number generator with the current time
    std::srand(std::time(nullptr));
	//possible directions the snake can go
	enum Direction{
		DOWN, LEFT, RIGHT, UP
	};

	//game rule
	bool running = true;
	//direction the snake is going
	int dir = UP;
	//create the head of the snake at the center of the screen
	SDL_Rect head {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 10, 10};

	//snake body container
	std::deque<SDL_Rect> rq;
	//size of snake
	int size = 1;
	int highScore = size;
	//create apple
	SDL_Rect apple {rand()%90 *10, rand()%90 * 10, 10, 10};

	// Initialize SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return -1;
	}

	// Load font
	TTF_Font* font = TTF_OpenFont("fonts/Peepo.ttf", 24);
	if (font == nullptr) {
		std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
		// Clean up and exit
		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

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
		//collision detection with apple
		if(head.x == apple.x && head.y == apple.y){
			//increase size of snake
			size += 10;
			//randomly select a new location for the apple
			apple = {rand()%90 *10, rand()%90 * 10, 10, 10};
			std::for_each(rq.begin(), rq.end(), [&](auto& snake_segment){
				if(apple.x = snake_segment.x && apple.y == snake_segment.y){
					//if the apple spawned on the snake then re randomize its location
					apple = {rand()%90 *10, rand()%90 * 10, 10, 10};
				}
			});
		}

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

		// Display score
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, ("Score: " + std::to_string(size - 1)).c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        SDL_Rect renderQuad = {(WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) - 10, textWidth, textHeight};
        SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(texture);

		if(size > highScore){
			highScore = size;
		}

		// Display High score
        SDL_Color high_textColor = {255, 255, 255, 255};
        SDL_Surface* high_textSurface = TTF_RenderText_Solid(font, ("High Score: " + std::to_string(highScore - 1)).c_str(), high_textColor);
        SDL_Texture* high_texture = SDL_CreateTextureFromSurface(renderer, high_textSurface);
        int high_textWidth = high_textSurface->w;
        int high_textHeight = high_textSurface->h;
        SDL_Rect high_renderQuad = {(WINDOW_WIDTH - high_textWidth) / 2, 0, high_textWidth, high_textHeight};
        SDL_RenderCopy(renderer, high_texture, nullptr, &high_renderQuad);
        SDL_FreeSurface(high_textSurface);
        SDL_DestroyTexture(high_texture);
		//display
		SDL_RenderPresent(renderer);
		int delay = 75;
		if(size == 1){
			delay = 75;
		}
		//increases the speed of the game on every other apple collection
		else if(size % 20 && delay > 15){
			delay -= 10;
		}
		SDL_Delay(delay);
	}
    return 0;
}
// //all:
// //	g++ -I src/include -L src/lib -o Main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
