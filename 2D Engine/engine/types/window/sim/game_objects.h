#pragma once

class game_object {
public:
	game_object(std::string name, vec2 pos, int radius, int elasticity) : name(name), radius(radius) 
	{
		this->position = rect(pos.x - (radius / 2), pos.y - (radius / 2), radius, radius);
		this->elasticity = elasticity / 100.f;
	}

	rect position;
	vec2 velocity = vec2(0, 0);
	vec2 terminal_v = vec2(100, 100);
	std::string name;
	int radius;
	float elasticity; // < 1
};