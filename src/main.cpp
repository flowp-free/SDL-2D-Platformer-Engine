#include "animation.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
//#include <memory>
//#include <SDL.h>
//include <iostream>


InputState processInput(InputState &input) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            input.quit = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            input.isleftClicked = true; break;
        }
        else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
            input.isleftClicked = false; break;
        }
        else if (e.type == SDL_KEYDOWN && !e.key.repeat) {
            switch (e.key.keysym.sym) {
                case SDLK_a: input.moveLeft = true; break;
                case SDLK_d: input.moveRight = true; break;
                case SDLK_w: input.jump = true; break;
                case SDLK_s: input.down = true; break;
            }
        }
        else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_a: input.moveLeft = false; break;
                case SDLK_d: input.moveRight = false; break;
                case SDLK_w: input.jump = false; break;
                case SDLK_s: input.down = false; break;
            }
        }
    }

    return input;
}




// Frame rate settings
const int TARGET_FPS = 60;
const float TARGET_FRAME_TIME = 1.0f / TARGET_FPS; // Target time per frame in milliseconds
float deltaTime = 0.0f;
Uint32 lastFrameTime = SDL_GetTicks();

int main() {
    
    Game* game = new Game();
    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;


    if (!game->initSDL(&window, &renderer)) {
        return -1;
    }

    //Uncomment for linux 
    SDL_Texture* standingTexture = game->loadTexture("../Assets/MainChar.png", renderer);
    SDL_Texture* walkingTexture = game->loadTexture("../Assets/Walking.png", renderer);
    SDL_Texture* platformTexture = game->loadTexture("../Assets/platform.png", renderer);
    SDL_Texture* jumpingTexture = game->loadTexture("../Assets/jumping102.png", renderer);
    
    //Uncomment for Windows
    /*w*//*SDL_Texture* standingTexture = game->loadTexture("C:\\Users\\VM\\Documents\\Projects\\Platformer\\Assets\\MainChar.png", renderer);
    SDL_Texture* walkingTexture = game->loadTexture("C:\\Users\\VM\\Documents\\Projects\\Platformer\\Assets\\Walking.png", renderer);
    SDL_Texture* platformTexture = game->loadTexture("C:\\Users\\VM\\Documents\\Projects\\Platformer\\Assets\\platform.png", renderer);*//*w1*/
    
    Camera camera;
    Map gameMap;
    Menu menu;
    Animation walkingAnim(11, walkingTexture);
    Animation jumpingAnim(4, jumpingTexture);
    Player player(walkingAnim, jumpingAnim, gameMap);
 

    std::vector<Platform> platforms;

    gameMap.loadMap(platforms);


    player.characterSpeed = 300.0f; // Speed of movement
    player.characterX = 368; // X position of the character
    player.characterY = 368; // Y position of the character
    player.isWalking = false;

    camera.x = 0;
    camera.y = 0;
    camera.w = 800;
    camera.h = 600;

   
   

    if (!standingTexture || !walkingTexture || !platformTexture) {
        game->closeSDL(window, renderer, standingTexture, walkingTexture,jumpingTexture, platformTexture);
        return -1;
    }
    
    InputState input;
	bool wasLeft = false;
    bool inMenu = true;
    bool needRedraw = true;
    bool prevPlayHover = false;
    bool prevExitHover = false;

    //Loading menu and manu loop
    while (inMenu) {
        processInput(input);
        menu.play.check();
        menu.exit.check();
        if (input.quit) {
            break;
            menu.cleanupMenu();
            }
        if (input.isleftClicked && menu.play.isHovered) {
            inMenu = false;
            menu.cleanupMenu();

        }
        if (input.isleftClicked && menu.exit.isHovered) {
            input.quit = true;
            menu.cleanupMenu();

        }
        if(menu.play.isHovered != prevPlayHover|| menu.exit.isHovered != prevExitHover){  
            needRedraw = true;
            prevPlayHover = menu.play.isHovered;
            prevExitHover = menu.exit.isHovered;
        }
        
        if(needRedraw){  
            menu.loadMenu(renderer, "../Assets/menu.png", "../Assets/play.png", "../Assets/exit.png");
            needRedraw = false;
        }

        SDL_Delay(16);
    }
    //Main game loop
    while (!input.quit) {
        Uint32 currentFrameTime = SDL_GetTicks();
        deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // Convert ms to seconds
        lastFrameTime = currentFrameTime;

        processInput(input);
        player.handleInput(input);
        
       
        // Update player logic
        int iter = 5;
        float physdt = deltaTime / iter;
        for(int i = 0; i < iter; i++)
            player.update(physdt, wasLeft, platforms);
        
        //Update camera position
		camera.followPlayer(player);
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the map
        gameMap.renderMap(renderer, platformTexture, camera, platforms);
        player.runAnimation(wasLeft,standingTexture, camera, player, renderer, deltaTime);
        

        // Update the screen
        SDL_RenderPresent(renderer);

        Uint32 frameDuration = SDL_GetTicks() - currentFrameTime;
        if (frameDuration < TARGET_FRAME_TIME * 1000) {
            SDL_Delay(static_cast<Uint32>((TARGET_FRAME_TIME * 1000) - frameDuration));
        }
    }
    
    delete game;
    game->closeSDL(window, renderer, standingTexture, walkingTexture, jumpingTexture, platformTexture);
    return 0;
}

