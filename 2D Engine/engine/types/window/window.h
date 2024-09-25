#pragma once
#include <functional>
#include "../../types/vectors/vec.h"
#include "../../game_engine.h"

class window
{
public:
	window( engine_2d* engine, rect size ) : engine( engine )
	{
		size.apply_scale( engine->desktop_scale );
		this->update_size( size );
		engine->engine_windows.push_back( engine_window( this ) );
	}

	bool ran_start = false;
	virtual void implode() {};
	virtual void start() { this->ran_start = true; }
	virtual void content() {}
	virtual void handle_input() { }

	rect size;
	rect title;

	rect close_box;
	rect resize_box;

	int holding;
	vec2 holding_position;

	void update( );
	void render_menu( );
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

#pragma region text windows
class text_window : public window
{
public:

	text_window(engine_2d* engine, rect size) : window(engine, size) { this->font_size *= (this->engine->desktop_scale * 1.3f); }

	void content();
	void handle_input();

	std::unordered_map<int, std::tuple<std::string, vec2>> line_data{ };
};
#pragma endregion

#pragma region sim windows
#include "../drawing/drawing.h"
#include "../simulator/simulator.h"

class sim_window : public window
{
public:

	sim_window(engine_2d* engine, rect size) : window(engine, size) {}

	void implode();
	void start();
	void content();
	void handle_input();

	simulator* sim = new simulator(); 
};
#pragma endregion