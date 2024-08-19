#pragma once
#pragma once
#include "../../types/vectors/vec.h"
#include "../../types/window/window.h"
#include "../../types/queue/engine_window.hpp"
#include "../../game_engine.h"

class key_manager
{
public:
	static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );


	inline static engine_2d* engine;
	inline static int current_line = -1;
	inline static window* current_window;
};