#ifndef _GAME_BEZIER_H
#define _GAME_BEZIER_H

#include "ploink/renderable.h"
#include "ploink/line.h"

#include <vector>

const size_t DEFAULT_SPLINES = 10;

struct Bezier : public Platform {
    Bezier(float x0, float y0, float xc, float yc, 
        float x1, float y1, bool hazard = false,
        size_t splines = DEFAULT_SPLINES);
    Bezier(Vec s, Vec c, Vec e, bool hazard = false,
        size_t splines = DEFAULT_SPLINES);

    Vec point(float t) const;
    ProjectionData project(Vec p) const;

    void render(SDL_Renderer* renderer, Vec center) const;
    float intersect(const Line& l) const;
private:
    Vec start, control, end;
    std::vector<Vec> table;
    bool is_hazard;
};

inline float bezier_point(float p0, float p1, float p2, float t) {
    return p1 + (1 - t)*(1 - t)*(p0 - p1) + t*t*(p2 - p1);
};

#endif
