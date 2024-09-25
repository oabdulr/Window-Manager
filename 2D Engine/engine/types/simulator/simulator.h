#pragma once
#include "game_objects.h"
#include "functional"
#include <unordered_map>

class simulator {
public:
	void update_window(rect new_size) { this->window_size = new_size; }
	void fixed_update();

	rect window_size;
	std::vector<game_object*> objects{};

	bool is_gravity = true;
	float gravity = 1.81f;
};

class static_simulator { // static (via engine)
public:
	void fixed_update();
	int get_list_size();
	bool try_add_update(std::string name, simulator* sim);

private:
	const int fixed_time = 60; //fps
	std::unordered_map<std::string, simulator*> physics_update;

	std::chrono::milliseconds frame_time = std::chrono::milliseconds(1000 / fixed_time);
	std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
};