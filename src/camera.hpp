#pragma once

#include <SDL2/SDL.h>

class Player;

class Camera {
public:
    float x;
    float y;
    int w;
    int h;
    SDL_Rect cameraRect() const { return { static_cast<int>(x), static_cast<int>(y), w, h }; }
    void followPlayer(const Player& player);

};