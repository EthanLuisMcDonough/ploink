#include "ploink/circle.h"

const double TAU = 6.283185307179586;
template<int N>
struct CircleLUT : public Renderable {
    CircleLUT() : vertices() {
        for (auto i = 0; i < N + 1; i++) {
            double angle = (TAU / N) * i;
            vertices[i] = { (float)cos(angle), (float)sin(angle) };
        }
        vertices[N] = { 1, 0 };
    }
    template <typename T>
    void scale_move(T center, float radius) {
        for (int i = 0; i < N + 1; i++) {
            float x = vertices[i].x, y = vertices[i].y;
            vertices[i].x = fmaf(x, radius, center.x);
            vertices[i].y = fmaf(y, radius, center.y);
        }
    }
    void render(SDL_Renderer* renderer) const {
        SDL_RenderDrawLinesF(renderer, vertices, N + 1);
    }
private:
    SDL_FPoint vertices[N + 1];
};
const auto circle_lut = CircleLUT<100>();

void Circle::render(SDL_Renderer* renderer) const {
    auto circ = circle_lut;
    circ.scale_move(center, radius);
    circ.render(renderer);
}

void DynamicCircle::apply_forces() {
    acceleration += Vec{ 0, GRAVITY };
    velocity += acceleration;
    velocity = velocity.capped(TERMINAL_VELOCITY);
    center += velocity;
}

void DynamicCircle::collide_with(const Platform& l) {
    Vec closest = l.project(center);
    if (closest.dist_sq(center) < radius * radius) {
        center += (center - closest).with_len(radius);
    }
}

void DynamicCircle::collide_with(DynamicCircle& l) {
    
}

void Player::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    Circle::render(renderer);
}
