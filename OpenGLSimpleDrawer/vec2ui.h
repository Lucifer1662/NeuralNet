#pragma once



struct vec2ui {
	unsigned int x;
	unsigned int y;
	inline vec2ui(unsigned int x, unsigned int y) {
		this->x = x;
		this->y = y;
	}
	inline vec2ui() {
		this->x = 0;
		this->y = 0;
	}

};