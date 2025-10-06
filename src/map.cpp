#include "map.hpp"
#include "camera.hpp"

void Map::loadMap(std::vector<Platform>& platforms) {
    platforms.push_back({ 200, 300, 140, 20 });
    platforms.push_back({ 400, 200, 130, 20 });
    platforms.push_back({ 600, 100, 200, 20 });
    platforms.push_back({ 820, 100, 150, 20 });
    platforms.push_back({ 840, 300, 160, 20 });
    platforms.push_back({ 880, 400, 144, 20 });
}


void Map::renderMap(SDL_Renderer* renderer, SDL_Texture* platformTexture, const Camera& camera, const std::vector<Platform>& platforms) {
    for (const auto& platform : platforms) {
        if (platform.x + platform.w >= camera.x && platform.x <= camera.x + camera.w &&
            platform.y + platform.h >= camera.y && platform.y <= camera.y + camera.h) {
            SDL_Rect platformdestRect = { static_cast<int>(platform.x - camera.x), static_cast<int>(platform.y - camera.y), platform.w, platform.h };
            SDL_RenderCopy(renderer, platformTexture, nullptr, &platformdestRect);
        }
    }
}