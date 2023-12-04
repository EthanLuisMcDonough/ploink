#include "ploink/circle.h"
#include "ploink/drawing.h"

#include <iostream>
#include <cmath>
#include <ploink/game.h>

void Circle::render(SDL_Renderer* renderer, Vec c) const {
    draw_circle(renderer, center - c, radius);
}

void DynamicCircle::apply_velocity(Vec v) {
    velocity += v;
}

void DynamicCircle::apply_forces() {
    p_center = center;
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
    ProjectionData pdata = l.project(center);
    Vec closest = pdata.pos;
    if (closest.dist_sq(center) < radius * radius) {
        auto n = (center - closest).unit();
        center = n * radius + closest;
        velocity -= n * 2 * velocity.dot(n) * COLLISION_DAMPENING;
        normal = { n };
        if (is_fragile || pdata.is_hazard) {
            take_hit();
        }
    }
    hit_visual *= 0.97;
}

void DynamicCircle::collide_with(DynamicCircle& l) {
    Vec dist = center - l.center;
    float r_sum = radius + l.radius;
    float mag = dist.magnitude();
    if (mag < r_sum) {
        Vec unit = dist.unit();
        float pd = (r_sum - mag) / 2.0f;
        center += unit * pd;
        l.center -= unit * pd;
        Vec dv = velocity - l.velocity;
        Vec norm = dist.unit();
        float new_vel_mag = dv.dot(norm);
        Vec new_vel = norm * new_vel_mag;
        l.velocity += new_vel;
        velocity -= new_vel;
        take_hit();
        l.take_hit();
    }
}

bool DynamicCircle::has_landed() {
    return normal.has_value() && normal->y <= -PLAYER_JUMP_THRESHOLD;
}

void Player::apply_forces() {
    float speed = normal.has_value() ? velocity.magnitude() : abs(velocity.x);
    angular_velocity = speed / radius * copysignf(PLAYER_ROTATION_SPEED, velocity.x);
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
    hit_visual = 0;
    active_life = starting_life;
}

void Player::render_healthbar(SDL_Renderer* renderer) const {
    float percent = ((float)active_life) / starting_life;
    float health_length = percent * 100;
    SDL_Rect heath_bar = { 5, 5, health_length, 30 };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &heath_bar);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &heath_bar);
}

void Player::render(SDL_Renderer* renderer, Vec c) const {
    SDL_SetRenderDrawColor(renderer, hit_visual, 0, 0, 255);
    Circle::render(renderer, c);

    float r = radius * 0.75;
    Vec v0(cosf(torque) * r, sinf(torque) * r);
    Vec v1 = v0.rot90();
    Vec ce = center - c;

    SDL_RenderDrawLineF(renderer,
        ce.x + v0.x, ce.y + v0.y,
        ce.x - v0.x, ce.y - v0.y);
    SDL_RenderDrawLineF(renderer,
        ce.x + v1.x, ce.y + v1.y,
        ce.x - v1.x, ce.y - v1.y);
}

std::optional<DynamicCircle> HazardEmitter::aim(const Player& p, bool can_shoot) {
    Vec d = p.get_center() - center;
    if (shot_timer > 0) {
        shot_timer--;
    }
    if (shot_timer <= 0 && can_shoot) {
        DynamicCircle c(center, HAZARD_SIZE);
        c.apply_velocity(d.with_len(launch_speed));
        shot_timer = shot_rate;
        return c;
    }
    return std::nullopt;
}

void HazardEmitter::render(SDL_Renderer* renderer, Vec c) const {
    SDL_SetRenderDrawColor(renderer, 89, 6, 125, 255);
    Circle::render(renderer, c);
    draw_circle(renderer, center - c, radius * 0.75);
    draw_circle(renderer, center - c, radius / 2);
    draw_circle(renderer, center - c, radius / 4);
}

void HazardEmitter::reset() {
    shot_timer = shot_rate;
}