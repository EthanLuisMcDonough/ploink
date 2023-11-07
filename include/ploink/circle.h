#ifndef _GAME_CIRCLE_H
#define _GAME_CIRCLE_H

#include "ploink/vec.h"
#include "ploink/renderable.h"
#include "ploink/line.h"
#include "ploink/constants.h"

#include <memory>
#include <vector>
#include <optional>

struct Circle : public Renderable {
    Circle(Vec p, float r) : center{ p }, radius{ r } {}

    virtual void render(SDL_Renderer* renderer) const;
protected:
    float radius;
    Vec center;
};

struct DynamicCircle : public Circle {
    DynamicCircle(Vec p, float r) : Circle(p, r),
        velocity{ Vec{0, 0} }, acceleration{ Vec{0, 0} } {}

    void collide_with(const Platform& l);
    void collide_with(DynamicCircle& c);

    inline void reset_normal() {
        normal = std::nullopt;
    }
    bool has_landed();

    virtual void apply_forces();
    void apply_velocity(Vec v);
protected:
    Vec velocity, acceleration;
    std::optional<Vec> normal;
};

class Player : public DynamicCircle {
public:
    Player(Vec p, float r = PLAYER_DEFAULT_SIZE)
        : DynamicCircle(p, r), torque{ 0 }, angular_velocity{0} {}
    Player(float x, float y, float r = PLAYER_DEFAULT_SIZE)
        : Player({ x, y }, r) {}

    void move(float d);

    void render(SDL_Renderer* renderer) const;
    void apply_forces();
private:
    float torque, angular_velocity;
};

#endif