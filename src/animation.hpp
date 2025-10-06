#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

class Animation{
    
    public:
        Animation(const int frames, SDL_Texture * text);
        void updateAnimation(float &deltaTime, bool loop);
        void loadTexture(SDL_Renderer*& renderer, SDL_RendererFlip &flip, float &x, float &y, float &cx, float &cy);
        const int FRAME_WIDTH = 52;
        const int FRAME_HEIGHT = 52;
    private:
        const int NUM_FRAMES = 0;
        SDL_Texture * texture;
        int currentFrame = 0; 
        float animationTimer = 0.0f;        // Accumulated time since last frame switch
        float animationSpeed = 0.1;        // Time between frames in seconds (e.g., 0.1 = 10 fps)
        


    };  