#ifndef _GAME_CIRCLE_H
#define _GAME_CIRCLE_H

#include "ploink/vec.h"
#include "ploink/renderable.h"
#include "ploink/line.h"

struct Circle : public Renderable {
    Circle(Vec p, float r) : center{ p }, radius{ r } {}

    virtual void render(SDL_Renderer* renderer) const;
protected:
    float radius;
    Vec center;
};

struct DynamicCircle : public Circle {
    DynamicCircle(SDL_FPoint p, float r) : Circle(p, r),
        velocity{ Vec{0, 0} }, acceleration{ Vec{0, 0} } {}

    void collide_with(const Platform& l);
    void collide_with(DynamicCircle& c);
    virtual void apply_forces();
protected:
    Vec velocity, acceleration;
};

const float PLAYER_DEFAULT_SIZE = 20;
class Player : private DynamicCircle {
public:
    Player(SDL_FPoint p, float r = PLAYER_DEFAULT_SIZE)
        : DynamicCircle(p, r), torque{ 0 } {}
    Player(float x, float y, float r = PLAYER_DEFAULT_SIZE)
        : Player(SDL_FPoint{ x, y }, r) {}

    void render(SDL_Renderer* renderer) const;
private:
    float torque;
};

#endif