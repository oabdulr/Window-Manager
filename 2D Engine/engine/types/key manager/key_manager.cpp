#include "key_manager.h"

void key_manager::key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	std::string txt = std::get<0>( current_window->line_data[ current_line ] );
	engine->text_cursor->pos = std::get<1>( current_window->line_data[ current_line ] );

	if ( action != GLFW_PRESS && action != GLFW_REPEAT )
		return;

	if ( key == GLFW_KEY_BACKSPACE && !txt.empty( ) )
		txt.pop_back( );
	else
	{
		if ( mods == GLFW_MOD_SHIFT )
			txt.push_back( toupper( ( char )key ) );
		else if ( mods == GLFW_MOD_CONTROL )
		{
			if ( key == GLFW_KEY_Q )
				exit( -1 );
		}
		else
			txt.push_back( key );

		if ( key == 257 )
		{
			engine->text_cursor->pos.x = 0;
			engine->text_cursor->pos.y += ( engine->current_font->get_fixed_height( ) * engine->text_cursor->raw_scale ) + 5;
			current_line++;
			return;
		}
		if ( key == 262 )
		{
			if ( engine->text_cursor->pos.x / static_cast< float >( engine->current_font->get_glyph( key )->width * engine->text_cursor->raw_scale ) + 5 < txt.length( ) )
				engine->text_cursor->pos.x += static_cast< float >( engine->current_font->get_glyph( key )->width * engine->text_cursor->raw_scale ) + 5;
		}
		else if ( key == 263 )
		{
			if ( engine->text_cursor->pos.x <= 0 )
				engine->text_cursor->pos.x = 0;
			else
				engine->text_cursor->pos.x -= static_cast< float >( engine->current_font->get_glyph( key )->width * engine->text_cursor->raw_scale ) + 5;
		}
		else if ( key == 264 )
		{
			if ( engine->text_cursor->pos.y <= 0 )
				engine->text_cursor->pos.y = 0;
			else
				engine->text_cursor->pos.y -= engine->current_font->get_fixed_height( ) * engine->text_cursor->raw_scale;
		}

		engine->text_cursor->pos.x += static_cast< float >( engine->current_font->get_glyph( key )->width * engine->text_cursor->raw_scale ) + 5;
	}

	current_window->line_data[ current_line ] = std::tuple<std::string, vec2>( txt, std::get<1>( current_window->line_data[ current_line ] ) );
}