
#include "../window.h"
#include "../../simulator/simulator.h"

void resolve_collision(game_object* a, game_object* b) {
	// Calculate normal
	vec2 normal = b->position.center() - a->position.center();
	normal.normalize();

	// Calculate relative velocity
	vec2 relative_velocity = b->velocity - a->velocity;
	float velocity_along_normal = relative_velocity.dot(normal);

	// Do not resolve if velocities are separating
	if (velocity_along_normal > 0) return;

	// Calculate restitution
	float restitution = std::min(a->elasticity, b->elasticity);

	// Calculate impulse scalar
	float impulse_scalar = -(1 + restitution) * velocity_along_normal;
	impulse_scalar /= 1 / a->mass + 1 / b->mass;

	// Apply impulse
	vec2 impulse = normal * impulse_scalar;
	a->velocity -= impulse / a->mass;
	b->velocity += impulse / b->mass;

	// Correct positions to prevent sinking
	const float percent = 0.2f; // Penetration percentage to correct
	const float slop = 0.01f; // Penetration allowance
	vec2 correction = normal * std::max(relative_velocity.length() - slop, 0.0f) / (1 / a->mass + 1 / b->mass) * percent;
	a->position -= correction / a->mass;
	b->position += correction / b->mass;
}

void sim_window::implode() {
	delete this->sim;
}

void sim_window::start() {
	if (!this->engine->simulator->try_add_update("sim_window", this->sim))
		this->engine->simulator->try_add_update("sim_window" + this->engine->simulator->get_list_size(), this->sim);
	this->ran_start = true;
}

void sim_window::content() {
	this->sim->update_window(this->size);

	this->engine->drawing->set_color(vec3(0, 0, 0));
	this->engine->drawing->set_thickness(2);

	for (int i = 0; i < this->sim->objects.size(); i++) {
		game_object* obj = this->sim->objects[i];

		this->engine->drawing->draw_circle(vec2(this->sim->window_size.x + obj->position.center().x, this->sim->window_size.y + obj->position.center().y), obj->radius, 20);
	}
}

void simulator::fixed_update() {
	// First, detect collisions
	std::vector<std::pair<game_object*, game_object*>> collisions;
	for (int i = 0; i < this->objects.size(); i++) {
		game_object* obj = this->objects[i];

		// Check for object collisions
		for (int j = i + 1; j < this->objects.size(); j++) {
			game_object* other = this->objects[j];
			if (obj->is_colliding(other)) {
				collisions.emplace_back(obj, other);
			}
		}
	

		// Boundary collision detection
		rect real_pos = obj->position + this->window_size;
		// Bottom boundary
		if (real_pos.bc().y > this->window_size.bc().y) {
			obj->velocity.y = -obj->velocity.y * obj->elasticity;
		}
		// Top boundary
		if (real_pos.tc().y < this->window_size.tc().y) {
			obj->velocity.y = std::abs(obj->velocity.y) * obj->elasticity;
		}
		// Right boundary
		if (real_pos.rc().x > this->window_size.rc().x) {
			obj->velocity.x = -std::abs(obj->velocity.x) * obj->elasticity;
		}
		// Left boundary
		if (real_pos.lc().x < this->window_size.lc().x) {
			obj->velocity.x = std::abs(obj->velocity.x) * obj->elasticity;
		}
	}

	// Resolve collisions
	for (auto& collision : collisions) {
		resolve_collision(collision.first, collision.second);
	}

	// Apply gravity and update positions
	for (auto& obj : this->objects) {
		obj->velocity.y += this->gravity;
		obj->position += obj->velocity;
	}
}

void sim_window::handle_input() {
	if (mouse_cursor::m2) {
		sim->objects.push_back(new game_object("ball" + (sim->objects.size() / sizeof(game_object)), vec2(100, 100), 15 * this->engine->desktop_scale, 55));
	}
}