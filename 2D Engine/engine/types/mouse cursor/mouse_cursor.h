#pragma once
#include "../../types/vectors/vec.h"
#include "../../types/window/window.h"
#include "../../types/queue/engine_window.hpp"
#include "../../game_engine.h"

class mouse_cursor
{
public:
	static void handle_mouse_input( );
	static void draw_mouse_cursor( );
	static void mouse_down_callback( GLFWwindow* window, int button, int action, int mods );
	static void mouse_position_callback( GLFWwindow* window, double xpos, double ypos );

	inline static vec2 mouse_size = vec2(3, 3);
	inline static vec2 mouse_positon;
	inline static short m1, m2;

	inline static engine_2d* engine;
};