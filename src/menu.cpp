#include "menu.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <iostream>


void Button::check(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point mousePoint = { mouseX, mouseY };
    isHovered = SDL_PointInRect(&mousePoint, &rect);
}

void Button::cleanup(){
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void Button::setPosition(int x, int y){
    rect.x = x;
    rect.y = y;
};


bool Button::loadTexture(SDL_Renderer* renderer, const std::string& path, int x, int y){
    setPosition(x, y);
    texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << path << " IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }else{
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        if (isHovered){
            rect.w = w * 1.1;
            rect.h = h * 1.1;
            rect.x = rect.x - (rect.w - w) / 2;
            rect.y = rect.y - (rect.h - h) /2;
        }else{ 
            rect.w = w;
            rect.h = h;
        } 
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        
        
    }
    return true;
};


void Menu::loadMenu(SDL_Renderer* renderer, const std::string& path, const std::string& button1, const std::string& button2){
    background = IMG_LoadTexture(renderer, path.c_str());
    
    if (!background) {
        std::cerr << "Failed to load texture: " << path << " IMG_Error: " << IMG_GetError() << std::endl;
    
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    play.loadTexture(renderer, button1, 100, 360);
    exit.loadTexture(renderer, button2, 100, 460);
    SDL_RenderPresent(renderer);

};

void Menu::cleanupMenu(){
    SDL_DestroyTexture(background);
    background = nullptr;
    play.cleanup();
    exit.cleanup();
};






