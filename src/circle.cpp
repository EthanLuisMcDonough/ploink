#include "ploink/circle.h"
#include "ploink/drawing.h"

#include <iostream>
#include <cmath>

void Circle::render(SDL_Renderer* renderer, Vec c) const {
    draw_circle(renderer, center - c, radius);
}

void DynamicCircle::apply_velocity(Vec v) {
    velocity += v;
}

void DynamicCircle::apply_forces() {
    Vec gravity = { 0, GRAVITY };
    if (has_landed()) {
        gravity -= (*normal * GRAVITY);
    }
    acceleration = gravity;
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
        velocity -= n * 2 * velocity.dot(n) * COLLISION_DAMPENING;
        normal = { n };
    }
}

void DynamicCircle::collide_with(DynamicCircle& l) {
    
}

bool DynamicCircle::has_landed() {
    return normal.has_value() && normal->y <= -PLAYER_JUMP_THRESHOLD;
}

void Player::apply_forces() {
    // ???
    if (normal.has_value()) {
        angular_velocity = velocity.magnitude() / (radius) * signbit(velocity.x);
    }
    DynamicCircle::apply_forces();
    torque += angular_velocity;
}

void Player::move(float d) {
    if (has_landed()) {
        velocity += normal->rot90() * -d;
    } else {
        velocity.x += d;
    }
}

void Player::jump() {
    if (has_landed()) {
        velocity.y -= PLAYER_JUMP_HEIGHT;
    }
}

void Player::reset(Vec p) {
    acceleration = { 0, 0 };
    velocity = { 0, 0 };
    center = p;
}

void Player::render(SDL_Renderer* renderer, Vec c) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    Circle::render(renderer, c);

    float r = radius * 0.75;
    Vec v0(cos(torque) * r, sin(torque) * r);
    Vec v1 = v0.rot90();
    Vec ce = center - c;

    SDL_RenderDrawLineF(renderer,
        ce.x + v0.x, ce.y + v0.y,
        ce.x - v0.x, ce.y - v0.y);
    SDL_RenderDrawLineF(renderer,
        ce.x + v1.x, ce.y + v1.y,
        ce.x - v1.x, ce.y - v1.y);
}
