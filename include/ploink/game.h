#ifndef _GAME_GAME_H
#define _GAME_GAME_H

#include "ploink/vec.h"
#include "ploink/bezier.h"
#include "ploink/circle.h"

#include <vector>

/// <summary>
/// The object responsible for storing and managing non-player game objects.
/// The level is in charge of managing the emitters, platforms, and projectiles
/// in a particilar level. A level is a platform to encapsulate projection logic
/// </summary>
class Level : public Platform {
public:
    void update();
    void render(SDL_Renderer* renderer, Vec c) const;

    Level(std::vector<Bezier> b, std::vector<HazardEmitter> e, Vec start, 
        Vec end) : platforms{ std::move(b) }, emitters{ std::move(e)},
        player_start{ start }, goal{ end } { }

    /// <summary>
    /// Allows a game-scope player to interact with level objects
    /// </summary>
    /// <param name="p">The player meant to interface with the game</param>
    void handle_player(Player& p);

    /// <summary>
    /// Resets a level to its initial state
    /// </summary>
    void reset();

    inline Vec get_start() const {
        return player_start;
    }
    inline Vec get_goal() const {
        return goal;
    }

    ProjectionData project(Vec p) const;
private:
    /// <summary>
    /// Renders the level end/goal
    /// </summary>
    /// <param name="renderer">SDL renderer</param>
    /// <param name="center">Where to render the end</param>
    void render_end(SDL_Renderer* renderer, Vec center) const;

    std::vector<Bezier> platforms;
    std::vector<HazardEmitter> emitters;
    std::vector<DynamicCircle> balls;
    Vec player_start, goal;
    std::optional<Bezier> cached_closest = std::nullopt;
};

/// <summary>
/// The object responsible for managing levels and 
/// </summary>
class Game {
public:
    void init_level();
    void update();
    void render(SDL_Renderer* renderer) const;

    inline Level& get_level() {
        return levels[current_level];
    }
    inline const Level& get_level() const {
        return levels[current_level];
    }
    inline bool has_level() const {
        return current_level < levels.size();
    }
    Vec get_camera() const;

    Game(std::vector<Level> l) : levels{ std::move(l) } {}
private:
    bool has_won() const;
    bool has_lost() const;

    std::vector<Level> levels;
    Player player;
    size_t current_level = 0;
};

#endif
