#include "ploink/renderable.h"

#ifndef _GAME_BEZIER_H
#define _GAME_BEZIER_H

struct Bezier : public Renderable {
    SDL_FPoint start, control, end;

    Bezier(float x0, float y0, float xc, float yc, float x1, float y1) :
        start({ x0, y0 }), control({ xc, yc }), end({ x1, y1 }) {}
    Bezier(SDL_FPoint s, SDL_FPoint c, SDL_FPoint e) :
        start(s), control(c), end(e) {}

    SDL_FPoint point(float t) const;
    void render(SDL_Renderer* renderer) const;
};

inline float bezier_point(float p0, float p1, float p2, float t) {
    return p1 + (1 - t)*(1 - t)*(p0 - p1) + t*t*(p2 - p1);
};

#endif
