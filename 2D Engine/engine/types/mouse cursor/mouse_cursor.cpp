#include "mouse_cursor.h"

void mouse_cursor::mouse_down_callback( GLFWwindow* window, int button, int action, int mods )
{
	if ( button == 0 )
		mouse_cursor::m1_raw = action;
	else if ( button == 1 )
		mouse_cursor::m2_raw = action;
}

void mouse_cursor::mouse_position_callback( GLFWwindow* window, double xpos, double ypos )
{
	mouse_cursor::mouse_positon = vec2( xpos, ypos );
}

void mouse_cursor::draw_mouse_cursor( )
{
	rect pos = rect( mouse_cursor::mouse_positon.x, mouse_cursor::mouse_positon.y, mouse_cursor::mouse_size.x, mouse_cursor::mouse_size.y );
	pos.apply_scale( mouse_cursor::engine->desktop_scale );

	// holy bad code
	if (m1_raw && !m1 && !m1_h) {
	    m1 = true;
		m1_h = true;
	}
	else if (m1_raw && m1 && m1_h) {
		m1 = false;
	}
	else if (!m1_raw) {
		m1 = false;
		m1_h = false;
	}

	if (m2_raw && !m2 && !m2_h) {
		m2 = true;
		m2_h = true;
	}
	else if (m2_raw && m2 && m2_h) {
		m2 = false;
	}
	else if (!m2_raw) {
		m2 = false;
		m2_h = false;
	}


	// mouse filled
	if ( m1 || m2 )
		mouse_cursor::engine->drawing->set_color( vec3( 200, 200, 200 ) );
	else
		mouse_cursor::engine->drawing->set_color( vec3( 255, 255, 255 ) );

	mouse_cursor::engine->drawing->draw_filled_rect( pos );

	// outline
	mouse_cursor::engine->drawing->set_color( vec3( 10, 10, 10 ) );
	mouse_cursor::engine->drawing->draw_rect( pos );
}

void mouse_cursor::handle_mouse_input( )
{
	for ( int idx = 0; idx < engine->engine_windows.size( ); idx++ )
	{
		window* window = engine->engine_windows[ idx ].object;
		if ( window->size.is_inside( mouse_cursor::mouse_positon ) )
			window->handle_input( );

		if ( window->title.is_inside( mouse_cursor::mouse_positon ) )
			window->handle_title_input( );

		if ( window->resize_box.is_inside( mouse_cursor::mouse_positon ) )
			window->handle_resize_input( );

		if ( window->kill )
		{
			engine->kill_id = idx;
			break;
		}

		if ( window->holding )
		{
			engine->focused_id = idx;
			break;
		}
	}


	for ( int idx = 0; idx < engine->desktop->icons.size( ); idx++ )
	{
		icon* ic = engine->desktop->icons[ idx ];

		if ( ic->position.is_inside( mouse_cursor::mouse_positon ) )
			ic->handle_mouse( ic );
		else
			ic->is_hovered = false;

	}

	if ( engine->focused_id != -1 )
	{
		utils::move( engine->engine_windows, engine->focused_id, 0 );
		engine->focused_id = -1;
	}

	if ( engine->kill_id != -1 )
	{
		//delete engine->engine_windows[ engine->kill_id ].object;
		engine->engine_windows.erase( engine->engine_windows.begin( ) + engine->kill_id );
		engine->kill_id = -1;
	}
}