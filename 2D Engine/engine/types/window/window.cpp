#include "window.h"

void window::handle_title_input( )
{
	if ( mouse_cursor::m1 || mouse_cursor::m1_h )
	{
		this->kill = this->close_box.is_inside( mouse_cursor::mouse_positon );
		if (!mouse_cursor::m1_h)
			return;

		if ( holding_position.is_zero( ) )
			holding_position = vec2( -this->title.width / 2, -this->title.height / 2 );

		this->update_size( rect( mouse_cursor::mouse_positon.x + holding_position.x, mouse_cursor::mouse_positon.y - holding_position.y, size.width, size.height ) );
	}
	else if (!mouse_cursor::m1_h && !holding_position.is_zero())
		holding_position.set(0, 0);
}

void window::handle_resize_input( )
{
	if (mouse_cursor::m1 || mouse_cursor::m1_h)
	{
		if ( !mouse_cursor::m1_h)
			return;
		

		if ( holding_position.is_zero( ) )
			holding_position = vec2( -this->resize_box.width / 2, -this->resize_box.height / 2 );

		float new_x = ( mouse_cursor::mouse_positon.x - this->size.x ) - holding_position.x;
		float new_y = ( mouse_cursor::mouse_positon.y - this->size.y ) - holding_position.y;

		if ( new_x > this->resize_box.width + 2 && new_y > this->resize_box.height + 2 )
			this->update_size( rect( this->size.x, this->size.y, new_x, new_y ) );
	}
	else if ( !mouse_cursor::m1_h && !holding_position.is_zero() )
		holding_position.set( 0, 0 );
}

void window::update( )
{
	this->render_menu( );
}

void window::update_size( rect size )
{
	this->size = size;
	this->title = rect( this->size.x, this->size.y - 16, this->size.width, 16 );
	this->title.apply_scale_h(this->engine->desktop_scale);

	this->close_box = rect( this->title.x + this->title.width, this->title.y, 10, 10 );
	this->close_box.apply_scale(this->engine->desktop_scale);
	this->close_box.x -= this->title.height - (2 * this->engine->desktop_scale);
	this->close_box.y += 3 * this->engine->desktop_scale;

	this->resize_box = rect( this->size.x + this->size.width, this->size.y + this->size.height, 10, 10);
	this->resize_box.apply_scale(this->engine->desktop_scale);
	this->resize_box.x -= this->resize_box.width + 1;
	this->resize_box.y -= this->resize_box.height + 1;

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

	this->content();

	// draw reize box
	engine->drawing->set_color( vec3( 150, 150, 150 ) );
	engine->drawing->draw_filled_rect( this->resize_box );
	engine->drawing->set_color( vec3( 120, 120, 120 ) );
	engine->drawing->draw_rect( this->resize_box );
}
