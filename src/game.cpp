#include "game.hpp"
//#include <SDL2/SDL_keycode.h>
//#include <SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
//#include <SDL_image.h>
//#include <vector>


Game::Game() {

}
Game::~Game() {

}


bool Game::initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Crate Window
    *window = SDL_CreateWindow("Platform game with no name, yet! <3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (!*window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

void Game::closeSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* standingTexture, SDL_Texture* walkingTexture, SDL_Texture* jumpingTexture, SDL_Texture* platformTexture) {
    SDL_DestroyTexture(standingTexture);
    SDL_DestroyTexture(walkingTexture);
    SDL_DestroyTexture(jumpingTexture);
    SDL_DestroyTexture(platformTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Game::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << path << " IMG_Error: " << IMG_GetError() << std::endl;
    }
    return texture;
}

