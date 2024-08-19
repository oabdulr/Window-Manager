#pragma once

class vec4
{
public:
	float x, y, z, w;

	vec4() : x(0), y(0), z(0), w(0) { }
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

	bool is_zero( ) { return this->x == 0 && this->y == 0 && this->z == 0 && this->w == 0; }
};