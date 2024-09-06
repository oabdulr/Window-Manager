#pragma once
#include "../vectors/vec.h"

class game_object {
public:
	game_object(std::string name, vec2 pos, int radius, int elasticity) : name(name), radius(radius) 
	{
		this->position = rect(pos.x + radius, pos.y + radius, radius * 2, radius * 2);
		this->elasticity = elasticity / 100.f;
	}

	rect position;
	vec2 velocity = vec2(0, 0);
	vec2 terminal_v = vec2(100, 100);
	std::string name;
	int radius;
	float elasticity; // < 1
};