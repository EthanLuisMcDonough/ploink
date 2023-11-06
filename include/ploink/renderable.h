#ifndef _GAME_RENDERABLE_H
#define _GAME_RENDERABLE_H

#include "ploink/vec.h"
#include "SDL.h"

struct Renderable {
    virtual void render(SDL_Renderer* renderer) const = 0;
};

struct Platform : public Renderable {
    virtual Vec point(float t) const = 0;
    virtual Vec project(Vec p) const = 0;
};

#endif
