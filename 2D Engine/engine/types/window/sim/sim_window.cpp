#include "../window.h"
#include "simulator.h"

bool mouse_down = false;
vec2 m1_down_loca = vec2();

void sim_window::content() {
	if (sim->objects.empty())
		sim->objects.push_back(new game_object("test", vec2(100, 100), 15, 55));

	float dT = engine->get_dT();

	if (!m1_down_loca.is_zero()) {
		engine->drawing->draw_line(m1_down_loca, mouse_cursor::mouse_positon);
	}

	engine->drawing->set_color(vec3(0, 0, 0));
	engine->drawing->set_thickness(2);

	for (int i = 0; i < sim->objects.size(); i++) {
		game_object* obj = sim->objects[i];


		if (this->size.height <= (obj->position.y + obj->radius) ||
			(0 >= (obj->position.y - obj->radius)))
			obj->velocity.y = -obj->velocity.y * obj->elasticity;
		else if (obj->terminal_v.y > abs(obj->velocity.y + (sim->gravity * dT)))
			obj->velocity.y += sim->gravity * dT;

		if (this->size.width < (obj->position.x + obj->radius))
			obj->velocity.x = -obj->velocity.x * obj->elasticity;

		obj->position = obj->position + obj->velocity;

		engine->drawing->draw_circle(vec2(this->size.x + obj->position.x, this->size.y + obj->position.y), obj->radius, 20);
	}
}

void sim_window::handle_input() {
	if (mouse_cursor::m1) {
		if (!mouse_down) {
			m1_down_loca = mouse_cursor::mouse_positon;
			mouse_down = true;
		}
	}
	else {
		mouse_down = false;
		m1_down_loca.set(0, 0);
	}
	
}