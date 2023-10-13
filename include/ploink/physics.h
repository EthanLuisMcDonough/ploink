#include <SDL2/SDL.h>

#ifndef _GAME_PHYSICS_H
#define _GAME_PHYSICS_H

struct Force {
    float x, y;

    void apply_to(Force& f) const {
        f.x += x;
        f.y += y;
    }

    void apply_to(SDL_FPoint& p) const {
        p.x += x;
        p.y += y;
    }
};

#endif
