#include "ploink/game.h"
#include "ploink/window.h"
#include "ploink/constants.h"

#include <limits>
#include <cmath>
#include <iostream>

void Level::render(SDL_Renderer* renderer, Vec c) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const auto& bezier : platforms) {
        bezier.render(renderer, c);
    }
    for (const auto& ball : balls) {
        ball.render(renderer, c);
    }
}

void Level::update() {
    for (int i = 0; i < balls.size(); i++) {
        auto& ball = balls[i];
        for (int j = i + 1; j < balls.size(); j++) {
            ball.collide_with(balls[j]);
        }
        for (const auto& bezier : platforms) {
            ball.collide_with(bezier);
        }
        ball.apply_forces();
    }
}

void Level::handle_player(Player& p) {
    for (auto& ball : balls) {
        p.collide_with(ball);
    }
    p.collide_with(*this);
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
        levels[current_level].render(renderer, get_camera());
    }

    player.render(renderer, get_camera());
    SDL_RenderPresent(renderer);
}

void Game::update() {
    if (current_level >= levels.size()) {
        return;
    }

    get_level().update();

    player.apply_forces();
    player.reset_normal();
    get_level().handle_player(player);

    if (key_is_pressed(GameKeyInputs::GAME_KEY_UP)) {
        player.jump();
    }
    if (key_is_pressed(GameKeyInputs::GAME_KEY_RIGHT)) {
        player.move(PLAYER_MOVEMENT_SPEED);
    } else if (key_is_pressed(GameKeyInputs::GAME_KEY_LEFT)) {
        player.move(-PLAYER_MOVEMENT_SPEED);
    }
    if (key_is_pressed(GameKeyInputs::GAME_KEY_RESET)) {
        init_level();
    }
}

Vec Game::get_camera() const {
    return player.get_center() - Vec(get_win_center());
}

void Game::init_level() {
    if (current_level < levels.size()) {
        player.reset(get_level().get_start());
    }
}
