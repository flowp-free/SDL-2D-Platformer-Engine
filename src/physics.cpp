#include "physics.hpp"

PhysicsComponent::PhysicsComponent(float sforce) : force(sforce) {};

void PhysicsComponent::applyGravity(float deltaTime) {
    if (!onGround) {
        velocity.y += gravity * deltaTime;
        if (velocity.y > maxFallSpeed) {
            velocity.y = maxFallSpeed;
        }
    }
}

void PhysicsComponent::jump(bool &isJumping) {
    if (onGround || onAnyPlatform) {
        velocity.y = -force;
        onGround = false;
        isJumping = true;

    }
}