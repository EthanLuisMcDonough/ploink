#include "ploink/drawing.h"
#include "ploink/renderable.h"

#include <cmath>

template<int N>
struct CircleLUT {
    CircleLUT() : vertices() {
        for (auto i = 0; i < N + 1; i++) {
            double angle = ((2 * M_PI) / N) * i;
            vertices[i] = { (float)cos(angle), (float)sin(angle) };
        }
        vertices[N] = { 1, 0 };
    }
    template <typename T>
    void scale_move(T center, float radius) {
        for (int i = 0; i < N + 1; i++) {
            float x = vertices[i].x, y = vertices[i].y;
            vertices[i].x = fmaf(x, radius, center.x);
            vertices[i].y = fmaf(y, radius, center.y);
        }
    }
    void render(SDL_Renderer* renderer) const {
        SDL_RenderDrawLinesF(renderer, vertices, N + 1);
    }
private:
    SDL_FPoint vertices[N + 1];
};

const auto circle_lut = CircleLUT<100>();

void draw_circle(SDL_Renderer* renderer, Vec center, float radius) {
    auto circ = circle_lut;
    circ.scale_move(center, radius);
    circ.render(renderer);
}
