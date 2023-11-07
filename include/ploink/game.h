#ifndef _GAME_GAME_H
#define _GAME_GAME_H

#include "ploink/vec.h"
#include "ploink/bezier.h"
#include "ploink/circle.h"

#include <vector>

class Level : public Platform {
public:
    void update();
    void render(SDL_Renderer* renderer) const;

    Level(std::vector<Bezier> b, Player p) : platforms{ std::move(b) },
        player{ std::move(p) } { }

    Vec project(Vec p) const;
private:
    std::vector<Bezier> platforms;
    Player player;
};

class Game : public Renderable {
public:
    void update();
    void render(SDL_Renderer* renderer) const;

    Game(std::vector<Level> l) : levels{ std::move(l) } {}
private:
    std::vector<Level> levels;
    size_t current_level = 0;
};

#endif
