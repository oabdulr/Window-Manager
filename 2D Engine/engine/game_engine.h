#pragma once
#include <GLFW/glfw3.h>
#include "string"
#include "vector"
#include <chrono>

#include "unordered_map"

#include "utils/utils.hpp"

#include "types/vectors/vec.h"
#include "dependences/stb_image.h"

class font_manager;
class drawing;
class text_cursor;
class mouse_cursor;
class key_manager;
class engine_window;
class desktop;
class icon;
class font;

struct glyph;

class engine_2d
{
public:
	engine_2d( vec2 size, const char* name );
	bool should_exit( );
	GLFWwindow* get_window( );

	void glfw_endframe( );
	void glfw_terminate( );
	void glfw_clear_color( vec4 color );
	float get_dT();

	vec2 screen_size;

	font_manager* font_manager;
	font* current_font;
	drawing* drawing;
	text_cursor* text_cursor;
	mouse_cursor* mouse_cursor;
	desktop* desktop;
	float deltaTime;

	std::unordered_map<std::string, unsigned int> loaded_textures;
	std::vector< engine_window > engine_windows { };

	int focused_id = -1;
	int kill_id = -1;

private:
	GLFWwindow* window;
};

#include "types/queue/engine_window.hpp"
#include "types/desktop/desktop.h"
#include "types/text cursor/text_cursor.h"
#include "types/mouse cursor/mouse_cursor.h"
#include "types/key manager/key_manager.h"
#include "types/font manager/font.h"
#include "types/drawing/drawing.h"

