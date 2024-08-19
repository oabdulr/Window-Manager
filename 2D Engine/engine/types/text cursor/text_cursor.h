#pragma once
#include <time.h>
#include <chrono>

#include "../../dependences/stb_image.h"
#include "../../types/vectors/vec.h"
#include "../../game_engine.h"

class text_cursor
{
public:
	text_cursor( engine_2d* engine ) : engine( engine ) { }

	void draw_cursor( vec2 relative_location );

	vec2 pos;
	float raw_scale;

	std::chrono::high_resolution_clock::time_point blink_time;
	std::chrono::high_resolution_clock::time_point off_time;

	float blink_dur = 500.f; // mili
	bool should_draw = false;
	engine_2d* engine;
};