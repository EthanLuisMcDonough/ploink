#include "ploink/vec.h"
#include <cmath>

float Vec::magnitude() const {
	return sqrt(magnitude_sq());
}

float Vec::dist(const Vec& v) const {
	return sqrt(dist_sq(v));
}

Vec Vec::with_len(float scalar) const {
	return unit() * scalar;
}

Vec Vec::unit() const {
	return *this / magnitude();
}

Vec Vec::capped(float max_mag) const {
	if (magnitude_sq() > max_mag * max_mag) {
		return with_len(max_mag);
	}
	return *this;
}
