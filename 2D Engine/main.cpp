#include <iostream>
#include <format>
#include <thread>
#include "windows.h"
#include "engine/game_engine.h"
#include "engine/types/window/window.h"

engine_2d engine( { 1600.f, 900.f }, "Engine 2D" );

class FrameTimer {
private:
	std::chrono::steady_clock::time_point current_time;
	std::chrono::steady_clock::time_point previous_time;

public:
	void update() {
		previous_time = current_time;
		current_time = std::chrono::high_resolution_clock::now();
	}

	float delta() const {
		return std::chrono::duration<float>(current_time - previous_time).count();
	}
};

FrameTimer blah = FrameTimer();

void main( )
{
	printf( "Loading ...\n" );

	engine.font_manager = new font_manager( &engine );
	engine.drawing = new drawing( &engine );
	engine.text_cursor =  new text_cursor( &engine );
	engine.desktop = new desktop( &engine );
	mouse_cursor::engine = &engine;
	key_manager::engine = &engine;

	auto pixel = engine.font_manager->load_font( "times.fnt", engine.loaded_textures );
	engine.drawing->load_texture( "window_icon.png", "window_icon" );

	engine.current_font = &pixel;

	if ( !engine.get_window( ) )
	{
		printf( "An error occured loading GLFW." );
		return;
	}

	glfwSetKeyCallback( engine.get_window( ), key_manager::key_callback );
	glfwSetInputMode( engine.get_window( ), GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
	glfwSetCursorPosCallback( engine.get_window( ), mouse_cursor::mouse_position_callback );
	glfwSetMouseButtonCallback( engine.get_window( ), mouse_cursor::mouse_down_callback );

	engine.desktop->create_icon("Create\nWindow", "create_window", "window_icon", rect( 30, 30, 50, 50 ) );
	engine.desktop->create_icon("Simulator", "sim_game", "window_icon", rect( 30, 220, 50, 50) );

	while ( !glfwWindowShouldClose( engine.get_window( ) ) )
	{
		
		blah.update();
		engine.deltaTime = blah.delta();


		const vec4 background_color { 0.1f, 0.1f, 0.1f, 1.f };
		engine.glfw_clear_color( background_color );

		engine.desktop->draw_icons( );

		for ( int idx = engine.engine_windows.size( ) - 1; idx >= 0; idx-- )
		{
			window* window = engine.engine_windows[ idx ].object;
			window->update( );
		}

		if ( engine.text_cursor->should_draw )
			engine.text_cursor->draw_cursor( { 0, 0 } );
		mouse_cursor::handle_mouse_input( );
		mouse_cursor::draw_mouse_cursor( );
		engine.glfw_endframe( );

		printf("FPS %d DT: %.6f\r", engine.fps, engine.deltaTime);

	}



	engine.drawing->cleanup_textures( );
	engine.glfw_terminate( );
}