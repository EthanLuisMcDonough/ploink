#include "ploink/circle.h"
#include "ploink/drawing.h"

void Circle::render(SDL_Renderer* renderer) const {
    draw_circle(renderer, center, radius);
}

void DynamicCircle::apply_velocity(Vec v) {
    velocity += v;
}

void DynamicCircle::apply_forces() {
    acceleration = Vec{ 0, GRAVITY };
    velocity += acceleration;
    velocity *= DAMPENING;
    velocity = velocity.capped(TERMINAL_VELOCITY);
    center += velocity;
}

void DynamicCircle::collide_with(const Platform& l) {
    Vec closest = l.project(center);
    if (closest.dist_sq(center) < radius * radius) {
        auto n = (center - closest).unit();
        center = n * radius + closest;
        velocity -= n * 2 * velocity.dot(n);
        normal = { n };
    }
}

void DynamicCircle::collide_with(DynamicCircle& l) {
    
}

void Player::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    Circle::render(renderer);
}
