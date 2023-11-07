#ifndef _GAME_LINE_H
#define _GAME_LINE_H

#include "ploink/renderable.h"
#include "ploink/vec.h"
#include "ploink/circle.h"

#include <optional>

struct Line : public Platform {
	Line(Vec s, Vec e) : start{ s }, end{ e } { }
	Line(float x0, float y0, float x1, float y1) : 
		Line({ x0, y0 }, { x1, y1 }) { }

	inline Vec get_start() const {
		return start;
	}
	inline Vec get_end() const {
		return end;
	}

	void render(SDL_Renderer* render) const;

	float intersect(const Line& line) const;
	float length() const;

	Vec project(Vec p) const;
	Vec point(float t) const;
private:
	Vec start, end;
};

#endif
