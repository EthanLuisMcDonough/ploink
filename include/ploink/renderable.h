#ifndef _GAME_RENDERABLE_H
#define _GAME_RENDERABLE_H

#include "ploink/vec.h"
#include "SDL.h"

struct Renderable {
    virtual void render(SDL_Renderer* renderer,
        Vec camera = { 0, 0 }) const = 0;
};

struct ProjectionData {
    Vec pos;
    bool is_hazard;
};

struct Platform : public Renderable {
    virtual ProjectionData project(Vec p) const = 0;
};

#endif
