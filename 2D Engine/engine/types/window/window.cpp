#include "window.h"

void window::handle_title_input( )
{
	if ( mouse_cursor::m1 )
	{
		this->kill = this->close_box.is_inside( mouse_cursor::mouse_positon );
		if ( !holding )
		{
			holding++;
			return;
		}

		if ( holding_position.is_zero( ) )
			holding_position = vec2( -this->title.width / 2, -this->title.height / 2 );

		this->update_size( rect( mouse_cursor::mouse_positon.x + holding_position.x, mouse_cursor::mouse_positon.y - holding_position.y, size.width, size.height ) );
	}
	else if ( !mouse_cursor::m1 && holding )
	{
		holding = 0;
		holding_position.set( 0, 0 );
	}
}

void window::handle_resize_input( )
{
	if ( mouse_cursor::m1 )
	{
		if ( !holding )
		{
			holding++;
			return;
		}

		if ( holding_position.is_zero( ) )
			holding_position = vec2( -this->resize_box.width / 2, -this->resize_box.height / 2 );

		float new_x = ( mouse_cursor::mouse_positon.x - this->size.x ) - holding_position.x;
		float new_y = ( mouse_cursor::mouse_positon.y - this->size.y ) - holding_position.y;

		if ( new_x > this->resize_box.width + 2 && new_y > this->resize_box.height + 2 )
			this->update_size( rect( this->size.x, this->size.y, new_x, new_y ) );
	}
	else if ( !mouse_cursor::m1 && holding )
	{
		holding = 0;
		holding_position.set( 0, 0 );
	}
}

void window::handle_input( )
{
	if ( mouse_cursor::m1 )
	{

		float lines = floor( this->size.height / font_size ) - 1;
		int y_offset = 10;
		for ( int line = 0; line < lines; line++ )
		{
			rect line_rect = rect( this->size.x + 5, this->size.y + y_offset + ( font_size * line ), this->size.width - 5, this->height + 20 );
			if ( line_rect.is_inside( mouse_cursor::mouse_positon ) )
			{
				engine->text_cursor->should_draw = true;
				engine->text_cursor->pos = std::get<1>( this->line_data[ line ] );

				key_manager::current_line = line;
				key_manager::current_window = this;
			}
		}

		if ( !holding )
		{
			holding++;
			return;
		}
	}
	else if ( !mouse_cursor::m1 && holding )
	{
		holding = 0;
		holding_position.set( 0, 0 );
	}
}

void window::update( )
{
	this->render_menu( );
}

void window::update_size( rect size )
{
	this->size = size;
	this->title = rect( this->size.x, this->size.y - 16, this->size.width, 16 );
	this->close_box = rect( this->title.x + this->title.width - 14, this->title.y + 3, 10, 10 );
	this->resize_box = rect( this->size.x + this->size.width - 11, this->size.y + this->size.height - 11, 10, 10 );


	this->height = engine->current_font->get_fixed_height( ) * ( font_size / engine->current_font->get_max_size( ) ) / 2.f;

	engine->text_cursor->should_draw = false;
}

void window::render_menu( )
{
	// draw main body
	engine->drawing->set_color( vec3( 180, 180, 180 ) );
	engine->drawing->draw_filled_rect( this->size );
	engine->drawing->set_color( vec3( 255, 255, 255 ) );
	engine->drawing->draw_rect( this->size );

	// draw title bar
	engine->drawing->set_color( vec3( 140, 140, 170 ) );
	engine->drawing->draw_filled_rect( this->title );
	engine->drawing->set_color( vec3( 255, 255, 255 ) );
	engine->drawing->draw_rect( this->title );

	// draw close box
	engine->drawing->set_color( vec3( 150, 100, 100 ) );
	engine->drawing->draw_filled_rect( this->close_box );
	engine->drawing->set_color( vec3( 130, 130, 170 ) );
	engine->drawing->draw_rect( this->close_box );

	// draw number lines

	float lines = floor( this->size.height / font_size ) - 1;
	int y_offset = 10;
	for ( int line = 0; line < lines; line++ )
	{
		engine->drawing->render_string( vec2( this->size.x + 10, this->size.y + y_offset + ( font_size * line ) ), std::format( "{}", line ), font_size, -1 );
		engine->drawing->draw_line( vec2( this->size.x + 5, this->size.y + y_offset + ( font_size * line ) + height + 20 ), vec2( this->size.x + this->size.width - 5, this->size.y + y_offset + ( font_size * line ) + height + 20 ) );

		if ( this->line_data.find( line ) == this->line_data.end( ) )
			this->line_data[ line ] = std::tuple<std::string, vec2>( "", { this->size.x + 10, this->size.y + y_offset + ( font_size * line ) } );
		else
		{
			vec2 pos = vec2( this->size.x + 15 + engine->current_font->get_max_size( ) * ( engine->text_cursor->raw_scale ), this->size.y + y_offset + ( font_size * line ) );
			vec2 offset_data = engine->drawing->render_string( pos, std::get<0>(this->line_data[ line ]), font_size - 3, -1, this->size.width - 55 );
			this->line_data[ line ] = std::tuple<std::string, vec2>( std::get<0>( this->line_data[ line ] ), pos + offset_data );
		}
	}

// draw reize box
	engine->drawing->set_color( vec3( 150, 150, 150 ) );
	engine->drawing->draw_filled_rect( this->resize_box );
	engine->drawing->set_color( vec3( 120, 120, 120 ) );
	engine->drawing->draw_rect( this->resize_box );
}
