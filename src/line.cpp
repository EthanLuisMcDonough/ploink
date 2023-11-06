#include "ploink/line.h"
#include <cmath>

void Line::render(SDL_Renderer* renderer) const {
	SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
}

Vec Line::point(float t) const {
	return start + (end - start) * t;
}

Vec Line::project(Vec p) const {
	const Vec d = end - start;
	float t = ((p.x * dx() - start.x * dx() + p.y * dy() -
		start.y * dy()) / (dx() * dx() + dy() * dy()));
	t = fmaxf(fminf(t, 1.0f), 0.0f);
	return point(t);
	/*float t = ((p.x * d.x - start.x * d.x + p.y * d.y -
		start.y * d.y) / (d.x * d.x + d.y * d.y));
	return point(t);*/
	/*return ((p.x * dx() - start.x * dx() + p.y * dy() -
		start.y * dy()) / (dx() * dx() + dy() * dy()));*/
}

float Line::intersect(const Line& line) const {
	const Vec dt = end - start, dl = line.end - line.start,
		ds = start - line.start;
	return (dl.y * ds.x - dl.x * ds.y) / (dt.y * dl.x - dt.x * dl.y);
	/*float start_dx = start.x - line.start.x,
		start_dy = start.y - line.start.y;
	return (line.dy() * start_dx - line.dx() * start_dy) /
		(dy() * line.dx() - dx() * line.dy());*/
}

float Line::length() const {
	return start.dist(end);
}
