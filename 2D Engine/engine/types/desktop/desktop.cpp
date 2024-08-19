#include "desktop.h"

void icon::handle_mouse( )
{
	this->is_hovered = true;
	if ( mouse_cursor::m1 )
	{
		mouse_cursor::m1 = false;
		new window( engine , rect( 100, 100, 100, 100 ) );
	}
}

void desktop::draw_icons( )
{
	for ( int idx = 0; idx < this->icons.size( ); idx++ )
	{
		icon* ic = this->icons[ idx ];

		if ( ic->is_hovered )
		{
			engine->drawing->set_color( vec3( 150, 150, 200 ) );
			engine->drawing->draw_filled_rect( rect( ic->position.x - 7, ic->position.y - 7, ic->position.width + 15, ic->position.height + 15 ) );
		}

		engine->drawing->set_color( vec3( 255, 255, 255 ) );
		engine->drawing->draw_texture( ic->tex_name.c_str( ), vec2( ic->position.x, ic->position.y ),
									   vec2( ic->position.x, ic->position.y + ic->position.height ),
									   vec2( ic->position.x + ic->position.width, ic->position.y ),
									   vec2( ic->position.x + ic->position.width, ic->position.y + ic->position.height ) );
		engine->drawing->set_color( vec3( 255, 255, 255 ) );
		engine->drawing->draw_rect( rect( ic->position.x, ic->position.y, ic->position.width, ic->position.height ), 2 );

		engine->drawing->render_string( vec2( ic->position.x - 4, ic->position.y + ic->position.height + 10 ), ic->name, 16, -1 );
	}
}

void desktop::create_icon( std::string name, std::string tex_name, rect position )
{
	this->icons.push_back( new icon( this->engine, name, tex_name, position ) );
}