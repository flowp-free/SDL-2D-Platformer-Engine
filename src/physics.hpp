#pragma once

struct Vector2 {
    float x = 0;
    float y = 0;
};

class PhysicsComponent {
public:
    PhysicsComponent(float sforce);
    Vector2 velocity;
    bool onGround = true;
    bool onAnyPlatform = false;
  
    void applyGravity(float deltaTime);
    void jump(bool &isJumping);
    
private:
    float gravity = 40.8f;
    float maxFallSpeed = 20.0f;
    float force = 0.0f;
  

};