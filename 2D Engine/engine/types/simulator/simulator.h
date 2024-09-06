#pragma once
#include "game_objects.h"
#include <unordered_map>

class simulator {
public:
	std::vector<game_object*> objects{};

	bool is_gravity = true;
	float gravity = 9.81f;

	static void run_on_launch();
	static void fixed_update();

	// String names to locate and remove certain calls if needed.
	static std::unordered_map<std::string, void(*)()> physics_update;
};

/*

	static void run_on_launch() {
		simulator::frame_time = std::chrono::milliseconds(1000 / 60);
		simulator::last_time = std::chrono::steady_clock::now();
	}

	static void fixed_update() {

		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = current_time - last_time;

		if (elapsed_time < frame_time) return;
		last_time = current_time;


		// maybe a try catch?
		for ( auto& function : physics_update) {
			function.second();
		}
	}
*/