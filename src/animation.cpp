#include "animation.hpp"
#include <SDL2/SDL_render.h>

Animation::Animation(const int frames, SDL_Texture* text) : NUM_FRAMES(frames), texture(text) {}

void Animation::updateAnimation(float &deltaTime, bool loop = true) {
    animationTimer += deltaTime;
    while (animationTimer >= animationSpeed) {
        animationTimer -= animationSpeed;
        if (loop) {
            currentFrame = (currentFrame + 1) % NUM_FRAMES;
        } else {
            if (currentFrame < NUM_FRAMES - 1) {
                currentFrame++;
            }
            else{
                return;
            }     
        }
    }
}

void Animation::loadTexture(SDL_Renderer*& renderer, SDL_RendererFlip &flip, float &x, float &y, float &cx, float &cy){
    SDL_Rect srcRect = { currentFrame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT };
    SDL_Rect destRect = { static_cast<int>(x - cx), static_cast<int>(y - cy), 82, 82 };
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, flip);
}