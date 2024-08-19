#pragma once
#include <unordered_map>
#include <fstream>
#include <GLFW/glfw3.h>

#include "string"
#include "vector"
#include "../../dependences/stb_image.h"
#include "../../types/vectors/vec.h"
#include "../../game_engine.h"

struct glyph
{
	int id;
	int x, y;
	int width, height;
	int xadvance;

	int texture_id;
};

class font
{
public:
	std::string font_name = "default";

	font( engine_2d* engine ) : engine( engine ) { }
	font( engine_2d* engine, const char* font_name, const char* file_name, int fixed_height, int count ) : engine(engine), font_name( font_name ), file_name( file_name ), fixed_height( fixed_height ), count( count ) { }

	void set_font_name( std::string font_name )
	{
		this->font_name = font_name;
	}

	void set_font_max_size( int max_size)
	{
		this->max_size = max_size;
	}

	void set_file_name( std::string file_name )
	{
		this->file_name = file_name;
	}

	void set_fixed_height( int fixed_height )
	{
		this->fixed_height = fixed_height;
	}

	void set_count( int count )
	{
		this->count = count;
	}

	void set_map( std::unordered_map<int, glyph> id_texture_map )
	{
		this->id_texture_map = id_texture_map;
	}
	
	int get_fixed_height( ) { return this->fixed_height; }
	int get_max_size		( ) { return this->max_size; }
	glyph* get_glyph( int id ) { return this->id_texture_map.find( id ) == this->id_texture_map.end( ) ? 0 : &this->id_texture_map [ id ]; }
	int get_count( ) { return this->count; }
	std::string get_file_name( ) { return this->file_name; }
	std::string get_font_name( ) { return this->font_name; }

private:
	// idk lol im cooked
	engine_2d* engine;
	std::string file_name;
	int max_size = 25;
	int fixed_height = 33;
	int count = -1;

	std::unordered_map<int, glyph> id_texture_map {};
};

class font_manager
{
public:
	font_manager( engine_2d* engine ) : engine( engine ) { }

	engine_2d* engine;
	std::string parse_line( std::string line, std::string search, std::string end_delim, bool end_ln = false );

	font load_font( const char* file, std::unordered_map < std::string, unsigned int >& engine_list_textures );
	int load_texture( const char* file );
	std::vector<char*> all_fonts( const char* path = "fonts\\" );
};