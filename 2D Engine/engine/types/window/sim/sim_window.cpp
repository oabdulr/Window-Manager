#include "../window.h"
#include "simulator.h"

bool mouse_down = false;
vec2 m1_down_loca = vec2();

void sim_window::content() {
	float dT = engine->get_dT();

	double forcex = 0;
	double forcey = 0;
	if (!m1_down_loca.is_zero() && mouse_cursor::m1) {
		engine->drawing->draw_line(m1_down_loca, mouse_cursor::mouse_positon);
	}
	else if (!mouse_cursor::m1 && !m1_down_loca.is_zero()) {
		double deltaX = mouse_cursor::mouse_positon.x - m1_down_loca.x;
		double deltaY = mouse_cursor::mouse_positon.y - m1_down_loca.y;
		double angle = atan2(deltaY, deltaX);
		double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
		double force = distance * 0.002f;

		forcex = force * cos(angle);
	    forcey = force * sin(angle);

		m1_down_loca.set(0, 0);
		mouse_down = false;
	}

	engine->drawing->set_color(vec3(0, 0, 0));
	engine->drawing->set_thickness(2);

	for (int i = 0; i < sim->objects.size(); i++) {
		game_object* obj = sim->objects[i];

		if (obj->position.x < 0 || obj->position.x > this->size.width ||
			obj->position.y < 0 || obj->position.y > this->size.height) {
			obj->position.set(100, 100);
			obj->velocity.set(0, 0);
		}

		if (obj->terminal_v.y > abs(obj->velocity.y + (sim->gravity * dT)))
			obj->velocity.y += sim->gravity * dT;

		if (this->size.height <= (obj->position.y + obj->radius) ||
			(0 >= (obj->position.y - obj->radius)))
			obj->velocity.y = -obj->velocity.y * obj->elasticity;

		

		if (this->size.width < (obj->position.x + obj->radius) || // Right wall
			(0 >= (obj->position.x - obj->radius))) // Left wall
			obj->velocity.x = -obj->velocity.x * obj->elasticity;

		obj->velocity = obj->velocity + vec2(forcex, forcey);
		obj->position = obj->position + obj->velocity;
		
		engine->drawing->draw_circle(vec2(this->size.x + obj->position.x, this->size.y + obj->position.y), obj->radius, 20);
	}
}

void sim_window::handle_input() {
	if (mouse_cursor::m2)
		sim->objects.push_back(new game_object("test" + (sim->objects.size() / sizeof(game_object)), vec2(100, 100), 15 * this->engine->desktop_scale, 55));

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