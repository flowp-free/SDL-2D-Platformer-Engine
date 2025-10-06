#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <string>

class Button{
    public:
        bool isHovered = false;
        bool loadTexture(SDL_Renderer* renderer, const std::string& path, int x, int y);
        void setPosition(int x, int y);
        void check();

        void cleanup();
    private:
        
        SDL_Texture* texture;
        SDL_Rect rect;
        SDL_Event me;
};

class Menu{
    public: 
        Button play;
        Button exit;
        void loadMenu(SDL_Renderer* renderer, const std::string& path, const std::string& button1, const std::string& button2);
        void cleanupMenu();
    private:
        SDL_Texture* background = nullptr;
};