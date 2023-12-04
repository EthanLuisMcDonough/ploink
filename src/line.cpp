#include "ploink/line.h"
#include <cmath>

void Line::render(SDL_Renderer* renderer, Vec c) const {
	SDL_RenderDrawLineF(renderer,
		start.x - c.x, start.y - c.y,
		end.x - c.x, end.y - c.y);
}

Vec Line::point(float t) const {
	return start + (end - start) * t;
}

ProjectionData Line::project(Vec p) const {
	const Vec d = end - start;
	float t = ((p.x * d.x - start.x * d.x + p.y * d.y -
		start.y * d.y) / (d.x * d.x + d.y * d.y));
	t = fmaxf(fminf(t, 1.0f), 0.0f);
	return { point(t), is_hazard };
}

float Line::intersect(const Line& line) const {
	const Vec dt = end - start,
		dl = line.end - line.start,
		ds = start - line.start;
	return (dl.y * ds.x - dl.x * ds.y) /
		(dt.y * dl.x - dt.x * dl.y);
}

float Line::length() const {
	return start.dist(end);
}
