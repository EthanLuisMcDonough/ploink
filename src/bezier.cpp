#include "ploink/bezier.h"
#include "ploink/line.h"

#include <cmath>
#include <limits>
#include <iostream>

Bezier::Bezier(Vec s, Vec c, Vec e, bool h, size_t splines)
    : start{ s }, control{ c }, end{ e }, is_hazard{ h } {
    float step = 1.0f / (splines + 2), t = step;
    for (int i = 0; i < splines; i++, t += step) {
        table.push_back(point(t));
    }
}

Bezier::Bezier(float x0, float y0, float xc, float yc, 
    float x1, float y1, bool h, size_t s) : Bezier({ x0, y0 },
        { xc, yc }, { x1, y1 }, h, s) { }

Vec Bezier::point(float t) const {
    float x = bezier_point(start.x, control.x, end.x, t),
        y = bezier_point(start.y, control.y, end.y, t);
    return Vec(x, y);
}

void Bezier::render(SDL_Renderer* renderer, Vec center) const {
    Vec prev = start;

    if (is_hazard) {
        SDL_SetRenderDrawColor(renderer, 255, 29, 6, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    for (int i = 0; i <= table.size(); i++) {
        Vec point = i == table.size() ? end : table[i];
        SDL_RenderDrawLineF(renderer,
            prev.x - center.x, prev.y - center.y,
            point.x - center.x, point.y - center.y);
        prev = point;
    }
}

float Bezier::intersect(const Line& l) const {
    Vec prev = start;
    float t = 1.0;
    for (int i = 0; i <= table.size(); i++) {
        Vec point = i == table.size() ? end : table[i];
        Line line(point, prev);
        float tn = l.intersect(line);
        if (tn >= 0) {
            t = std::min(t, tn);
        }
        prev = point;
    }
    return t;
}

ProjectionData Bezier::project(Vec target) const {
    Vec prev = start;
    ProjectionData closest;
    float dist_sq = std::numeric_limits<float>::infinity();
    for (int i = 0; i <= table.size(); i++) {
        Vec point = i == table.size() ? end : table[i];

        Line line(prev, point, is_hazard);
        ProjectionData p = line.project(target);
        float d = p.pos.dist_sq(target);
        if (d < dist_sq) {
            dist_sq = d;
            closest = p;
        }

        prev = point;
    }
    return closest;
}
