#include "game_engine.h"

GLFWwindow* engine_2d::get_window( )
{
	return this->window;
}

bool engine_2d::should_exit( )
{
	return glfwWindowShouldClose( this->window );
}

void engine_2d::glfw_endframe( )
{
	glfwSwapBuffers( this->window );
	glfwPollEvents( );
}

void engine_2d::glfw_terminate( )
{
	glfwTerminate( );
}/*

		// Draw textured quad
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);
		glEnd();*/

void engine_2d::glfw_clear_color( vec4 color )
{
	glClearColor( color.x, color.y, color.z, color.w );
	glClear( GL_COLOR_BUFFER_BIT );
}

float engine_2d::get_dT() 
{
	return -1.f; // todod
}

engine_2d::engine_2d( vec2 size, const char* name )
{
	this->window = NULL;

	if ( !glfwInit( ) )
		return;

	// should prolly flag
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	this->screen_size = size;
	this->window = glfwCreateWindow( this->screen_size.x, this->screen_size.y, name, NULL, NULL );
	this->desktop_scale = 2.f; // make customizable in future

	if ( !window )
	{
		this->glfw_terminate( );
		return;
	}

	glfwMakeContextCurrent( this->window );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}