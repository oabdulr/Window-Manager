#pragma once

class vec3
{
public:
	float x, y, z;

	vec3() : x(0), y(0), z(0) { }
	vec3(float x, float y, float z): x(x), y(y), z(z) { }

	bool is_zero() { return this->x == 0 && this->y == 0 && this->z == 0; }
};