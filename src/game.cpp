#include <limits>
#include <cmath>
#include <iostream>
#include "ploink/game.h"
#include "ploink/window.h"
#include "ploink/constants.h"
#include "ploink/drawing.h"

const int PULSE_PERIOD = 1000;
const float PULSE_PERIOD_ANGLE = ((2 * M_PI) / (float)PULSE_PERIOD);

void Level::render_end(SDL_Renderer* renderer, Vec center) const {
    SDL_SetRenderDrawColor(renderer, 3, 148, 51, 255);
    draw_circle(renderer, goal - center, GOAL_SIZE);

    size_t ticks = get_frame_count() % PULSE_PERIOD;
    float angle = PULSE_PERIOD_ANGLE * ticks;

    float pulse_s = sinf(angle) * GOAL_SIZE;
    draw_circle(renderer, goal - center, pulse_s);

    float pulse_c = cosf(angle) * GOAL_SIZE;
    draw_circle(renderer, goal - center, pulse_c);
}

void Level::render(SDL_Renderer* renderer, Vec c) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const auto& bezier : platforms) {
        bezier.render(renderer, c);
    }
    for (const auto& ball : balls) {
        ball.render(renderer, c);
    }
    for (auto& emitter : emitters) {
        emitter.render(renderer, c);
    }
    render_end(renderer, c);
}

void Level::update() {
    for (int i = balls.size() - 1; i >= 0; i--) {
        auto& ball = balls[i];
        ball.apply_forces();
        ball.collide_with(*this);
        if (!ball.is_alive()) {
            balls.erase(balls.begin() + i);
        }
    }
}

void Level::handle_player(Player& p) {
    for (auto& ball : balls) {
        p.collide_with(ball);
    }
    for (auto& emitter : emitters) {
        if (auto c = emitter.aim(p, balls.size() < MAX_HAZARDS)) {
            balls.push_back(*c);
        }
    }
    p.collide_with(*this);
}

void Level::reset() {
    balls.clear();
    for (auto& emitter : emitters) {
        emitter.reset();
    }
}

void Level::prevent_clipping(DynamicCircle& c) const {
    Line trajectory(c.get_past_center(), c.get_center());
    float t = 1.0;
    for (const auto& bezier : platforms) {
        t = std::min(t, bezier.intersect(trajectory));
    }
    if (t < 1.0) {
        Vec inv_dir = (c.get_center() - c.get_past_center()).with_len(c.get_radius());
        c.set_center(inv_dir + c.get_center());
    }
}

ProjectionData Level::project(Vec point) const {
    ProjectionData closest;
    float dist_sq = std::numeric_limits<float>::infinity();
    for (const auto& bezier : platforms) {
        ProjectionData p = bezier.project(point);
        float d = p.pos.dist_sq(point);
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
        get_level().render(renderer, get_camera());
        player.render(renderer, get_camera());
        player.render_healthbar(renderer);
    }

    SDL_RenderPresent(renderer);
}

bool Game::has_won() const {
    return has_level() && player.get_center()
        .dist_sq(get_level().get_goal()) < 4 * GOAL_SIZE * GOAL_SIZE;
}

bool Game::has_lost() const {
    return !player.is_alive();
}

void Game::update() {
    if (!has_level()) {
        return;
    }

    get_level().update();

    player.apply_forces();
    player.reset_normal();
    get_level().handle_player(player);

    if (has_won()) {
        current_level = (current_level + 1) % levels.size();
        init_level();
        return;
    }

    if (has_lost()) {
        init_level();
        return;
    }

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
    if (has_level()) {
        player.reset(get_level().get_start());
        get_level().reset();
    }
}
