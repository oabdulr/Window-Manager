#pragma once
#include <functional>

#include "../../types/vectors/vec.h"
#include "../../game_engine.h"

class window
{
public:
	window( engine_2d* engine, rect size ) : engine( engine )
	{
		this->update_size( size );
		engine->engine_windows.push_back( engine_window( this ) );
	}



	rect size;
	rect title;

	rect close_box;
	rect resize_box;

	int holding = 0;
	vec2 holding_position;

	void update( );
	void render_menu( );
	void handle_input( );
	void handle_title_input( );
	void handle_resize_input( );
	void update_size( rect size );

	engine_2d* engine;

	int font_size = 20;
	float height = -1;

	bool border = true;
	bool kill = false;

	std::unordered_map<int, std::tuple<std::string, vec2>> line_data { };
};