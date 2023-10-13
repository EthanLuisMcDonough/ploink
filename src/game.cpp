#include "ploink/game.h"
#include <cmath>

const double TAU = 6.283185307179586;

template<int N>
struct CircleLUT : public Renderable {
    constexpr CircleLUT() : vertices() {
        for (auto i = 0; i < N + 1; i++) {
            double angle = (TAU / N) * i;
            vertices[i] = { (float)cos(angle), (float)sin(angle) };
        }
        vertices[N] = {1, 0};
    }
    void scale_move(SDL_FPoint center, float radius) {
        for (int i = 0; i < N + 1; i++) {
            vertices[i].x *= radius;
            vertices[i].x += center.x;
            vertices[i].y *= radius;
            vertices[i].y += center.y;
        }
    }
    void render(SDL_Renderer* renderer) const {
        SDL_RenderDrawLinesF(renderer, vertices, N + 1);
    }
private:
    SDL_FPoint vertices[N + 1];
};
constexpr auto circle_lut = CircleLUT<100>();

void Circle::render(SDL_Renderer* renderer) const {
    auto circ = circle_lut;
    circ.scale_move(center, radius);
    circ.render(renderer);
}

void Player::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    Circle::render(renderer);
}

void Level::render(SDL_Renderer* renderer) const {
    for (const auto& bezier : platforms) {
        bezier.render(renderer);
    }
}

void Level::update() {
    // TODO
}

void Game::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if (levels.size() < current_level) {
        levels[current_level].render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::update() {
    if (levels.size() < current_level) {
        levels[current_level].update();
    }
}
