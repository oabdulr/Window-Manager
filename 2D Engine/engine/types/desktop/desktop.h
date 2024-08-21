#pragma once

#include "../vectors/vec.h"
#include "../../game_engine.h"
#include "../../types/vectors/vec.h"

class desktop;
class icon
{
public:
	icon( engine_2d* engine, std::string display_name, std::string name, std::string tex_name, rect position ) : engine(engine), display_name(display_name), name( name ), tex_name (tex_name), position( position ) { }

	void handle_mouse( icon* pIcon );

	engine_2d* engine;
	std::string display_name;
	std::string name;
	std::string tex_name;
	rect position;

	bool is_hovered = false;
};

class desktop
{
public:

	desktop( engine_2d* engine ) : engine ( engine ) { }

	void draw_icons( );
	void create_icon( std::string display_name, std::string name, std::string tex_name, rect position );

	std::vector<icon*> icons {  };
	engine_2d* engine;
};