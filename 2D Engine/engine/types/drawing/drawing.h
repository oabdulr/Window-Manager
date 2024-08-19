#pragma once
#include "../../dependences/stb_image.h"
#include "../../types/vectors/vec.h"
#include "../../game_engine.h"

class drawing
{
public:
	drawing( engine_2d* engine ) : engine( engine ) { }

	void set_color( vec3 color, bool is32 = true );
	void draw_line( vec2 start, vec2 end, int thickness = 1 );
	void draw_rect( rect data, int thickness = 1 );
	void draw_filled_rect( rect data, int thickness = 1 );

	void cleanup_textures( );

	void draw_texture( const char* name, vec2 top_left );
	void draw_texture( const char* name, vec2 tl, vec2 bl, vec2 tr, vec2 br, bool resolve = true );

	int load_texture( const char* path, const char* name );
	int get_texture( const char* name );

	void render_char( vec2 pos, char c, vec2 offsets, float raw_scale, vec4 color = { 1.f, 1.f, 1.f, 1.f } );
	void render_char( glyph* glyph, vec2 pos, char c, vec2 offsets, float raw_scale, int outline = 2, vec4 color = { 1.f, 1.f, 1.f, 1.f } );
	vec2 render_string( vec2 pos, std::string string, int pt_scale = 12, int outline = 2, float cutoff = 0.f, vec4 color = { 1.f, 1.f, 1.f, 1.f } );

	engine_2d* engine;
};