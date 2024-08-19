#include "text_cursor.h"
static bool first = false;

void text_cursor::draw_cursor( vec2 relative_location )
{

	if ( std::chrono::duration<double, std::milli>( std::chrono::high_resolution_clock::now( ) - blink_time ).count( ) > blink_dur )
	{
		engine->drawing->draw_line( { relative_location.x + this->pos.x,relative_location.y + this->pos.y }, { relative_location.x + this->pos.x,relative_location.y + this->pos.y + engine->current_font->get_max_size( ) * ( this->raw_scale ) } );

		if ( !first )
		{
			first = true;
			off_time = std::chrono::high_resolution_clock::now( );
		}

		if ( std::chrono::duration<double, std::milli>( std::chrono::high_resolution_clock::now( ) - off_time ).count( ) > blink_dur )
		{
			blink_time = std::chrono::high_resolution_clock::now( );
			off_time = std::chrono::high_resolution_clock::now( );

			first = false;
		}
	}
}