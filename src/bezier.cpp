#include "ploink/bezier.h"

const int SPLINES = 10;

SDL_FPoint Bezier::point(float t) const {
    float x = bezier_point(start.x, control.x, end.x, t),
        y = bezier_point(start.y, control.y, end.y, t);
    return { x, y };
}

void Bezier::render(SDL_Renderer* renderer) const {
    float step = 1.0f/((float)SPLINES), t = step;
    SDL_FPoint prev = start;
    for (int i = 0; i < SPLINES; i++, t += step) {
        SDL_FPoint p = point(t);
        SDL_RenderDrawLineF(renderer, prev.x, prev.y, p.x, p.y);
        prev = p;
    }
}
