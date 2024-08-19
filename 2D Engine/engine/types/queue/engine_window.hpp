#pragma once

class window; // forward declaration
class engine_window
{
public:
	engine_window( window* object ) : object ( object ) {}

	window* object;
};