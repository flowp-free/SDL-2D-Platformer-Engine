#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "animation.hpp"
#include "camera.hpp"
#include "map.hpp"

class Platform;


struct InputState {
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool down = false;
    bool quit = false;
    bool isleftClicked = false;
};



class Player {
    
    public:
        Player (Animation &swalkingAnim, Animation& sjumpingAnim, Map& smap);
   
        float characterSpeed = 0.0f;
        float characterX = 0.0f; 
        float characterY = 0.0f;
        InputState currentInput;

        bool isWalking = false;
        bool isJumping = false;
        SDL_Rect getBoundingBox() const { return { static_cast<int>(characterX), static_cast<int>(characterY), walkingAnim.FRAME_HEIGHT, walkingAnim.FRAME_WIDTH }; }
        SDL_Rect  playerRect;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        
        void handleInput(const InputState& input);
        void update(float& deltaTime, bool& wasLeft, const std::vector<Platform>& platforms);
        void updateAnimation(float deltaTime);
        void runAnimation(bool &wasLeft, SDL_Texture*& standingTexture, Camera &camera, Player &player, SDL_Renderer*& renderer, float &deltaTime);
        int getPlayerWidth() const;
        int getPlayerHeight() const;
    private:
        Animation& walkingAnim;
        Animation& jumpingAnim;
        Map& map;
    };


