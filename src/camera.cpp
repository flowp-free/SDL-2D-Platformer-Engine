#include "camera.hpp"
#include "player.hpp"


void Camera::followPlayer(const Player& player) {
    
	x = player.characterX + static_cast<float>(player.getPlayerWidth()) / 2 - static_cast<float>(w) / 2;
	y = player.characterY + static_cast<float>(player.getPlayerHeight()) / 2 - static_cast<float>(h) / 2;

}