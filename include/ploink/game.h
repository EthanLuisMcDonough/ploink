#ifndef _GAME_GAME_H
#define _GAME_GAME_H

#include "ploink/vec.h"
#include "ploink/bezier.h"
#include "ploink/circle.h"

#include <vector>

class Level : public Platform {
public:
    void update();
    void render(SDL_Renderer* renderer, Vec c) const;

    Level(std::vector<Bezier> b, std::vector<DynamicCircle> c,
        Vec start) : platforms{ std::move(b) }, balls{ std::move(c)}, 
        player_start{ start } { }

    void handle_player(Player& p);

    inline Vec get_start() {
        return player_start;
    }

    Vec project(Vec p) const;
private:
    std::vector<Bezier> platforms;
    std::vector<DynamicCircle> balls;
    Vec player_start;
};

class Game {
public:
    void init_level();
    void update();
    void render(SDL_Renderer* renderer) const;

    inline Level& get_level() {
        return levels[current_level];
    }
    inline bool has_level() {
        return current_level < levels.size();
    }
    Vec get_camera() const;

    Game(std::vector<Level> l) : levels{ std::move(l) } {}
private:
    std::vector<Level> levels;
    Player player;
    size_t current_level = 0;
};

#endif
