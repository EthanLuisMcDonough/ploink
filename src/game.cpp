#include "ploink/game.h"
#include "ploink/window.h"
#include "ploink/constants.h"

#include <limits>
#include <cmath>
#include <iostream>

void Level::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const auto& bezier : platforms) {
        bezier.render(renderer);
    }
    player.render(renderer);
}

void Level::update() {
    player.apply_forces();
    player.reset_normal();
    player.collide_with(*this);
    if (player.has_landed() && key_is_pressed(GameKeyInputs::GAME_KEY_UP)) {
        player.apply_velocity({ 0, -PLAYER_JUMP_HEIGHT });
    }
}

Vec Level::project(Vec point) const {
    Vec closest = { 0,0 };
    float dist_sq = std::numeric_limits<float>::infinity();
    for (const auto& bezier : platforms) {
        Vec p = bezier.project(point);
        float d = p.dist_sq(point);
        if (d < dist_sq) {
            dist_sq = d;
            closest = p;
        }
    }
    return closest;
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
