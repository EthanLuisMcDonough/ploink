#include "ploink/bezier.h"
#include "ploink/line.h"
#include <cmath>
#include <limits>
#include <iostream>

Bezier::Bezier(Vec s, Vec c, Vec e, size_t splines) 
        : start{ s }, control{ c }, end{ e } {
    float step = 1.0f / (splines + 2), t = step;
    for (int i = 0; i < splines; i++, t += step) {
        table.push_back(point(t));
    }
}

Bezier::Bezier(float x0, float y0, float xc, float yc, float x1, float y1, size_t s)
    : Bezier({ x0, y0 }, { xc, yc }, { x1, y1 }, s) { }

Vec Bezier::point(float t) const {
    float x = bezier_point(start.x, control.x, end.x, t),
        y = bezier_point(start.y, control.y, end.y, t);
    return Vec(x, y);
}

void Bezier::render(SDL_Renderer* renderer) const {
    Vec prev = start;
    for (int i = 0; i <= table.size(); i++) {
        Vec point = i == table.size() ? end : table[i];
        SDL_RenderDrawLineF(renderer, prev.x, prev.y, point.x, point.y);
        prev = point;
    }
}

Vec Bezier::project(Vec target) const {
    Vec prev = start, closest = {0,0};
    float dist_sq = std::numeric_limits<float>::infinity();
    for (int i = 0; i <= table.size(); i++) {
        Vec point = i == table.size() ? end : table[i];

        Line line(prev, point);
        Vec p = line.project(target);
        float d = p.dist_sq(target);
        if (d < dist_sq) {
            dist_sq = d;
            closest = p;
        }

        prev = point;
    }
    return closest;
}
