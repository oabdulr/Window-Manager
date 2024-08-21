#include "../window.h"
#include "simulator.h"

void sim_window::content() {
	if (sim->objects.empty())
		sim->objects.push_back(new game_object("test", vec2(100, 100), 15, 55));

	float dT = engine->deltaTime.count();

	engine->drawing->set_color(vec3(0, 0, 0));
	engine->drawing->set_thickness(2);
	for (int i = 0; i < sim->objects.size(); i++) {
		game_object* obj = sim->objects[i];


		if (this->size.height <= (obj->position.y + obj->radius) ||
			(0 >= (obj->position.y - obj->radius)))
			obj->velocity.y = -obj->velocity.y * obj->elasticity;
		else//else if (obj->terminal_v.y > abs(obj->velocity.y + (sim->gravity * dT)))
		obj->velocity.y += sim->gravity * dT;

		//printf("%.2f\n", obj->velocity.y);
		//if (this->size.width < (obj->position.x + obj->radius))
		//	obj->velocity.x = -obj->velocity.x * obj->elasticity;

		obj->position = obj->position + obj->velocity;

		engine->drawing->draw_circle(vec2(this->size.x + obj->position.x, this->size.y + obj->position.y), obj->radius, 20);

	}
}

void sim_window::handle_input() {

}