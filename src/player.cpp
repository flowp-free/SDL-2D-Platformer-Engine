//#include <iostream>
#include "player.hpp"
#include "animation.hpp"
#include "map.hpp"
#include "physics.hpp"
//#include <iostream>

PhysicsComponent physics(18.0f);  
Player::Player(Animation& swalkingAnim, Animation& sjumpingAnim, Map& smap) : walkingAnim(swalkingAnim), jumpingAnim(sjumpingAnim), map(smap) {}

int Player::getPlayerWidth() const {
    return walkingAnim.FRAME_WIDTH;
};
int Player::getPlayerHeight() const {
    return walkingAnim.FRAME_HEIGHT;
};

bool checkCollision(SDL_Rect rect1, SDL_Rect rect2) {
    return   rect1.x + rect1.w > rect2.x &&
        rect1.x + rect1.w/2 < rect2.x + rect2.w &&
        rect1.y + rect1.h > rect2.y &&
        rect1.y < rect2.y + rect2.h;
};


void Player::update(float& deltaTime, bool& wasLeft, const std::vector<Platform>& platforms) {

    if (currentInput.moveLeft) {
        characterX -= characterSpeed * deltaTime;
        flip = SDL_FLIP_HORIZONTAL;
		wasLeft = true;
    } // LEFT
    if (currentInput.moveRight) {
        characterX += characterSpeed * deltaTime;
        flip = SDL_FLIP_NONE;
		wasLeft = false;
    } // RIGHT
    if (currentInput.jump) {
        physics.jump(isJumping);
		physics.onAnyPlatform = false;
    }// JUMP
    if (currentInput.down) {
        characterY += characterSpeed * deltaTime;
    } // DOWN



    physics.applyGravity(deltaTime);

    // Update character's Y position
    characterY += static_cast<int>(physics.velocity.y * deltaTime * 100);

	playerRect = getBoundingBox();
    
    for (auto platform : platforms) {
        //SDL_Rect platformRect = { platform.x - cameraRect.x, platform.y - cameraRect.y, platform.w, platform.h };
		SDL_Rect platformRect = platform.getBoundingBox();
        if (checkCollision(playerRect, platformRect)) {
            if (physics.velocity.y >= 0 && playerRect.y + playerRect.h/2  <= platformRect.y) {
                characterY = platformRect.y - playerRect.h;
                physics.velocity.y = 0;
                physics.onAnyPlatform = true;
            }
        }
        else if (characterY >= map.groundLevel) {
            characterY = map.groundLevel;
            physics.onGround = true;
            physics.velocity.y = 0;

        }
        else
        {
            if (!physics.onAnyPlatform) {
                physics.onGround = false;
            }
        }
    }
}

void Player::handleInput(const InputState& input) {
    currentInput = input;
    isWalking = input.moveLeft || input.moveRight;
    isJumping = input.jump;

}


void Player::runAnimation(bool &wasLeft, SDL_Texture*& standingTexture, Camera &camera, Player &player, SDL_Renderer*& renderer, float &deltaTime){
    
    if (player.isWalking) {
            // Render walking frame
            walkingAnim.updateAnimation(deltaTime, true);
            walkingAnim.loadTexture(renderer, flip, characterX, characterY, camera.x, camera.y);
            

    } else if (player.isJumping){    
            //Render jumping frame
            jumpingAnim.updateAnimation(deltaTime, false);
            jumpingAnim.loadTexture(renderer, flip, characterX, characterY, camera.x, camera.y);
            
        }

    else {
            
		    if (wasLeft) {
				player.flip = SDL_FLIP_HORIZONTAL;
			}
		    else {
				player.flip = SDL_FLIP_NONE;
			}
            
            // Render standing frame
            SDL_Rect destRect = { static_cast<int>(player.characterX - camera.x), static_cast<int>(player.characterY - camera.y), 82, 82 };
            SDL_RenderCopyEx(renderer, standingTexture, nullptr, &destRect, 0, nullptr, player.flip);
        }
}
