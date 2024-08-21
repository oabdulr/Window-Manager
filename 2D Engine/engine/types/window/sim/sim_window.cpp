#include "../window.h"
#include "simulator.h"

void sim_window::content() {
	engine->drawing->set_color(vec3(0, 0, 0));
	engine->drawing->set_thickness(3);
	engine->drawing->draw_circle(vec2(this->size.x + 100, this->size.y + 100), 10, 100);

}

void sim_window::handle_input() {

}