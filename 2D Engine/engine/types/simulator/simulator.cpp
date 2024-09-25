#include "chrono"
#include "simulator.h"

bool static_simulator::try_add_update(std::string name, simulator* sim) {
	return this->physics_update.try_emplace(name, sim).second;
}

int static_simulator::get_list_size() {
	return this->physics_update.size();
}

void static_simulator::fixed_update() {

	auto current_time = std::chrono::steady_clock::now();
	auto elapsed_time = current_time - last_time;

	if (elapsed_time < frame_time) return;
	last_time = current_time;


	// maybe a try catch?
	for (auto& function : this->physics_update) {
		function.second->fixed_update();
	}
}