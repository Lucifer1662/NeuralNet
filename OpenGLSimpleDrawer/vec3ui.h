#pragma once

struct vec3ui {
	size_t x;
	size_t y;
	size_t z;
	inline vec3ui(size_t x, size_t y, size_t z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	inline vec3ui() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
};