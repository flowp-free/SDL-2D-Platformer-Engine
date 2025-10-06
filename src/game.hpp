#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL.h>
#include <string>
//#include <vector>



class Game {
public:
    Game();
    ~Game();
    bool initSDL(SDL_Window** window, SDL_Renderer** renderer);
    void closeSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* standingTexture, SDL_Texture* walkingTexture, SDL_Texture* jumpingTexture, SDL_Texture* platformTexture);
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
};


