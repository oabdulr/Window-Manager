#pragma once
#include "game_objects.h"


class simulator {
public:
	std::vector<game_object*> objects{};

	bool is_gravity = true;
	float gravity = 1.f; //100% real earth graity 11!!!
};