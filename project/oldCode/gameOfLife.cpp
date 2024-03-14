/****************************************************************************
* Title:          SDL2main.cpp
* Author:         Dawson Whipple
* Date:           3/8/24
* Description:    conways game of life made using sdl2
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

// Function to determine if a cell at position (x, y) will be alive in the next generation
bool isAlive(const std::vector<std::vector<int>>& game, int x, int y) {
    // Store the coordinates of neighboring cells
    static const std::vector<std::pair<int, int>> neighbors = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    // Calculate the number of alive neighbors
    int alive = 0;
    for (const auto& [dx, dy] : neighbors) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < WINDOW_WIDTH && ny >= 0 && ny < WINDOW_HEIGHT && game[ny][nx] == 1) {
            ++alive;
        }
    }

    // Apply the rules of the game
    if (game[y][x] == 1) {
        return alive == 2 || alive == 3;
    } else {
        return alive == 3;
    }
}

// Function to update the game state for the next generation
void updateGame(std::vector<std::vector<int>>& display, std::vector<std::vector<int>>& swap) {
    // Compute the next generation
    for (int i = 0; i < WINDOW_WIDTH; ++i) {
        for (int j = 0; j < WINDOW_HEIGHT; ++j) {
            swap[j][i] = isAlive(display, i, j) ? 1 : 0;
        }
    }

    // Copy the new state back to the display
    std::swap(display, swap);
}

int main(int argc, char* argv[]) {
    // Initialize SDL and create a Screen object
    Screen screen;

    // Create vectors to hold the current and next game states
    std::vector<std::vector<int>> display(WINDOW_HEIGHT, std::vector<int>(WINDOW_WIDTH));
    std::vector<std::vector<int>> swap(WINDOW_HEIGHT, std::vector<int>(WINDOW_WIDTH));

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Populate the initial game state with random values
    for (auto& row : display) {
        std::generate(row.begin(), row.end(), []() { return std::rand() % 2; });
    }

    // Main loop
    while (true) {
        // Process input events
        screen.input(display);

        // Update the game state for the next generation
        updateGame(display, swap);

        // Clear the screen
        screen.clear();

        // Draw the game state to the screen
        for (int i = 0; i < WINDOW_WIDTH; ++i) {
            for (int j = 0; j < WINDOW_HEIGHT; ++j) {
                if (display[j][i] == 1) {
                    screen.pixel(i, j);
                }
            }
        }

        // Display the updated screen
        screen.show();

        // Delay for a short interval
        SDL_Delay(50);
    }

    return 0;
}