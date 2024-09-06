#include "../window.h"
#include "../../simulator/simulator.h"

void sim_window::content() {
	engine->drawing->set_color(vec3(0, 0, 0));
	engine->drawing->set_thickness(2);

	for (int i = 0; i < sim->objects.size(); i++) {
		game_object* obj = sim->objects[i];
		
		vec2 bc = this->size + obj->position.bc();
		if (this->size.bc().y <= bc.y) {
			obj->velocity.y = -obj->velocity.y * obj->elasticity;
		}
		else
			obj->velocity.y = this->sim->gravity + obj->velocity.y;

		obj->position.append(obj->velocity * engine->deltaTime);

		engine->drawing->draw_circle(vec2(this->size.x + obj->position.center().x, this->size.y + obj->position.center().y), obj->radius, 20);
	}
}

void sim_window::handle_input() {
	if (mouse_cursor::m2)
		sim->objects.push_back(new game_object("test" + (sim->objects.size() / sizeof(game_object)), vec2(100, 100), 15 * this->engine->desktop_scale, 55));

}