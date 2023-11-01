#ifndef _GAME_GAME_H
#define _GAME_GAME_H

#include <vector>
#include "ploink/bezier.h"

struct Circle : public Renderable {
    SDL_FPoint center;
    double radius;

    virtual void render(SDL_Renderer* renderer) const;
};

class Player : private Circle {
public:
    void render(SDL_Renderer* renderer) const;
private:
    float torque;
};

class Level : public Renderable {
public:
    void update();
    void render(SDL_Renderer* renderer) const;
private:
    std::vector<Bezier> platforms;
    Player player;
};

class Game : public Renderable {
public:
    void update();
    void render(SDL_Renderer* renderer) const;
private:
    std::vector<Level> levels;
    size_t current_level = 0;
};

#endif
