#include "ploink/game.h"
#include "ploink/window.h"
#include <cmath>
#include <iostream>


void Level::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const auto& bezier : platforms) {
        bezier.render(renderer);
    }
    auto m = get_mouse();
    auto p = platforms[0].project(m);
    SDL_RenderDrawLineF(renderer, m.x, m.y, p.x, p.y);
    player.render(renderer);
}

void Level::update() {
    // TODO
}

void Game::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if (current_level < levels.size()) {
        levels[current_level].render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::update() {
    if (current_level < levels.size()) {
        levels[current_level].update();
    }
}
