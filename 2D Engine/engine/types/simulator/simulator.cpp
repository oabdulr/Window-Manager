#include "chrono"
#include "simulator.h"


// Desired frame time for 60 FPS
std::chrono::milliseconds frame_time;
std::chrono::steady_clock::time_point last_time;

void simulator::run_on_launch() {
	frame_time = std::chrono::milliseconds(1000 / 60);
	last_time = std::chrono::steady_clock::now();
	simulator::physics_update = {};
}

void simulator::fixed_update() {

	auto current_time = std::chrono::steady_clock::now();
	auto elapsed_time = current_time - last_time;

	if (elapsed_time < frame_time) return;
	last_time = current_time;


	// maybe a try catch?
	//for (auto& function : simulator::physics_update) {
	//	function.second();
	//}
}