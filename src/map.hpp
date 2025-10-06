#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Platform;
class Camera;

class Platform {
public:
    int x;
    int y;
    int w;
    int h;
    Platform(int sx, int sy, int sw, int sh) : x(sx), y(sy), w(sw), h(sh) {}
    SDL_Rect getBoundingBox() const { return { x, y, w, h }; };
};

class Map {
public:
    int groundLevel = 568;
    void loadMap(std::vector<Platform>& platforms);
    void renderMap(SDL_Renderer* renderer, SDL_Texture* platformTexture, const Camera& camera, const std::vector<Platform>& platforms);
};