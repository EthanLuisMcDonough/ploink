#ifndef _GAME_CIRCLE_H
#define _GAME_CIRCLE_H

#include "ploink/vec.h"
#include "ploink/renderable.h"
#include "ploink/line.h"
#include "ploink/constants.h"

#include <memory>
#include <vector>
#include <optional>

/// <summary>
/// Base circle class that other round game objects extend
/// </summary>
struct Circle : public Renderable {
    Circle(Vec p, float r) : center{ p }, radius{ r } {}

    virtual void render(SDL_Renderer* renderer, Vec center) const;
    inline Vec get_center() const {
        return center;
    }
    inline float get_radius() const {
        return radius;
    }
protected:
    float radius;
    Vec center;
};

/// <summary>
/// Balls that are capable of bouncing off walls and against each other
/// This class is used to represent enemy projectiles.Objects of this type
/// have N lives and are marked as dead after experiencing N collisions
/// with harmful surfaces.If an instance of this class is marked as fragile,
/// every collision will be marked as harmful collision
/// </summary>
struct DynamicCircle : public Circle {
    DynamicCircle(Vec p, float r, int life = BALL_LIFE_COUNT, bool f = true) : 
        Circle(p, r), velocity{ Vec{0, 0} }, acceleration{ Vec{0, 0} },
        starting_life{ life }, active_life{ life }, is_fragile{ f },
        p_center{ p }  {}

    void collide_with(const Platform& l);
    void collide_with(DynamicCircle& c);

    inline void reset_normal() {
        normal = std::nullopt;
    }
    bool has_landed();

    inline bool is_alive() const {
        return active_life > 0;
    }
    virtual void apply_forces();
    void apply_velocity(Vec v);

    inline void set_center(Vec v) {
        center = v;
    }
    inline Vec get_past_center() const {
        return p_center;
    }
protected:
    void take_hit() {
        active_life--;
        hit_visual = 255.0f;
    }
    
    Vec velocity, acceleration, p_center;
    std::optional<Vec> normal;
    int starting_life, active_life;
    float hit_visual = 0.0f;
    bool is_fragile;
};

/// <summary>
/// The player object
/// The player is represented as a non-fragile subclass of the projectile
/// The player can be controlled via the move and jump methods
/// These methods are called by the game
/// </summary>
class Player : public DynamicCircle {
public:
    Player(Vec p, float r = PLAYER_DEFAULT_SIZE, int life = PLAYER_LIFE_COUNT)
        : DynamicCircle(p, r, life, false), torque{ 0 }, angular_velocity{0} { }
    Player(float x, float y, float r = PLAYER_DEFAULT_SIZE)
        : Player({ x, y }, r) { }
    Player() : Player({ 0, 0 }, PLAYER_DEFAULT_SIZE, PLAYER_LIFE_COUNT) { }

    void move(float d);
    void jump();

    void render(SDL_Renderer* renderer, Vec center) const;
    void render_healthbar(SDL_Renderer* renderer) const;
    void apply_forces();

    void reset(Vec p);
private:
    float torque, angular_velocity;
};

/// <summary>
/// Hazard emitters inherit from circle because they have the properties
/// of a circle but aren't physical objects. These objects emit projectiles
/// that are then used by the game logic. Hazard emitters run on a frame-based
/// timer so that they aren't constantly spamming projectiles
/// </summary>
struct HazardEmitter : public Circle {
    HazardEmitter(Vec c, int rate = HAZARD_EMITTER_RATE, 
        float speed = HAZARD_EMITTER_SPEED) : Circle(c, HAZARD_EMITTER_SIZE),
        shot_rate{ rate }, shot_timer{ rate }, launch_speed{ speed } {}

    /// <summary>
    /// Generates a projectile in the direction of the player if it can
    /// </summary>
    /// <param name="p">The player to shoot at</param>
    /// <param name="can_shoot">Whether the player can shoot (used to limit number of active projectiles)</param>
    /// <returns>An optional monad projectile. Returns None when the emitter didn't shoot</returns>
    std::optional<DynamicCircle> aim(const Player& p, bool can_shoot = true);

    void render(SDL_Renderer* renderer, Vec center) const;
    void reset();
private:
    int shot_timer, shot_rate;
    float launch_speed;
};

#endif
