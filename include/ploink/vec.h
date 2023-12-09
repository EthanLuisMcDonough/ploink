#ifndef _GAME_VEC_H
#define _GAME_VEC_H

#include "SDL.h"

/// <summary>
/// Math class for 2D vectors
/// </summary>
struct Vec {
    float x, y;

    Vec(float _x, float _y) : x{ _x }, y{ _y } {}
    Vec(SDL_FPoint p) : x{ p.x }, y{ p.y } {}
    Vec() : Vec(0, 0) {}

    // Addition
    inline Vec operator+(const Vec& f) const {
        return Vec(x + f.x, y + f.y);
    }
    inline Vec operator+=(const Vec& f) {
        x += f.x;
        y += f.y;
        return *this;
    }

    // Subtraction
    inline Vec operator-(const Vec& f) const {
        return Vec(x - f.x, y - f.y);
    }
    inline Vec operator-=(const Vec& f) {
        x -= f.x;
        y -= f.y;
        return *this;
    }

    // Multiplication
    inline Vec operator*(float f) const {
        return Vec(x * f, y * f);
    }
    inline Vec operator*=(float f) {
        x *= f;
        y *= f;
        return *this;
    }

    // Division
    inline Vec operator/(float f) const {
        return Vec(x / f, y / f);
    }
    inline Vec operator/=(float f) {
        x /= f;
        y /= f;
        return *this;
    }

    inline Vec operator-() const {
        return *this * -1;
    }

    // Euclidian distance
    inline float magnitude_sq() const {
        return x * x + y * y;
    }
    float magnitude() const;
    inline float dist_sq(const Vec& p) const {
        return (*this - p).magnitude_sq();
    }
    float dist(const Vec& p) const;

    inline float dot(const Vec& p) const {
        return x * p.x + y * p.y;
    }

    inline Vec rot90() const {
        return Vec(y, -x);
    }

    Vec capped(float max_size) const;
    Vec with_len(float scalar) const;
    Vec unit() const;
};

#endif
