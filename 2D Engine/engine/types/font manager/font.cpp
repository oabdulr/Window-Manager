#include "font.h"

std::string font_manager::parse_line( std::string line, std::string search, std::string end_delim, bool end_ln )
{
	int search_idx = line.find( search );
	int search_size = search.length( );
	if ( search_idx != std::string::npos )
	{
		if ( !end_ln )
		{
			int end = line.find( end_delim, search_idx + search_size );
			if ( end != std::string::npos )
				return line.substr( search_idx + search_size, end - ( search_idx + search_size ) );
		}
		else
		{
			return line.substr( search_idx + search_size );
		}
	}

	return "";
}

int font_manager::load_texture( const char* file )
{
	int width, height, channels;
	stbi_uc* image = stbi_load( file, &width, &height, &channels, STBI_rgb_alpha );
	if ( !image )
	{
		printf( "Failed to load image\n" );
		return 0;
	}

	GLuint textureID;
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	stbi_image_free( image );

	return textureID;
}

font font_manager::load_font( const char* file, std::unordered_map<std::string, unsigned int>& engine_list_textures )
{
	std::ifstream infile( file );
	std::string line;

	font generated_font( this->engine );

	bool get_font_name = false;
	bool get_fixed_height = false;
	bool get_file_name = false;
	bool get_count = false;

	std::unordered_map<int, glyph> temp_map { };
	while ( std::getline( infile, line ) )
	{
		if ( !get_font_name )
		{
			auto parsed_data = this->parse_line( line, "face=\"", "\"" );
			if ( !parsed_data.empty( ) )
				generated_font.set_font_name( parsed_data );

			parsed_data = this->parse_line( line, "size=-", "\"" );
			if ( !parsed_data.empty( ) )
			{
				generated_font.set_font_max_size( std::stoi( parsed_data ) );
				get_font_name = true;
				continue;
			}
		}


		if ( !get_fixed_height )
		{
			auto parsed_data = this->parse_line( line, "lineHeight=", " " );
			if ( !parsed_data.empty( ) )
			{
				generated_font.set_fixed_height( std::stoi( parsed_data ) );
				get_fixed_height = true;
				continue;
			}
		}

		if ( !get_file_name )
		{
			auto parsed_data = this->parse_line( line, "file=\"", "\"" );
			if ( !parsed_data.empty( ) )
			{
				generated_font.set_file_name( parsed_data );
				get_file_name = true;
				continue;
			}
		}

		if ( !get_count )
		{
			auto parsed_data = this->parse_line( line, "count=", "", true );
			if ( !parsed_data.empty( ) )
			{
				generated_font.set_count( std::stoi( parsed_data ) );
				get_count = true;
				continue;
			}
		}

		if ( get_font_name && get_fixed_height && get_file_name && get_count )
		{
			if ( line.substr( 0, 4 ) != "char" )
				continue;

			glyph g;

			auto id_parse = this->parse_line( line, "id=", " " );
			if ( id_parse.empty( ) )
				continue;

			auto x_parse = this->parse_line( line, "x=", " " );
			if ( x_parse.empty( ) )
				continue;

			auto y_parse = this->parse_line( line, "y=", " " );
			if ( y_parse.empty( ) )
				continue;

			auto width_parse = this->parse_line( line, "width=", " " );
			if ( width_parse.empty( ) )
				continue;

			auto height_parse = this->parse_line( line, "height=", " " );
			if ( height_parse.empty( ) )
				continue;

			auto xadvance_parse = this->parse_line( line, "xadvance=", " " );
			if ( xadvance_parse.empty( ) )
				continue;

			g.id = std::stoi( id_parse );
			g.x = std::stoi( x_parse );
			g.y = std::stoi( y_parse );
			g.width = std::stoi( width_parse );
			g.height = std::stoi( height_parse );
			g.xadvance = std::stoi( xadvance_parse );

			temp_map[ g.id ] = g;
		}
	}

	if ( generated_font.get_count( ) != temp_map.size( ) )
	{
		printf( "Failed to load %s, Invalid font hash size ... %d %d\n", generated_font.get_font_name( ).c_str( ), generated_font.get_count( ), temp_map.size( ) );
		return generated_font;
	}
	else
		printf( "Parsed %s\n", generated_font.get_font_name( ).c_str( ) );


	int width, height, channels;
	stbi_uc* image = stbi_load( generated_font.get_file_name( ).c_str( ), &width, &height, &channels, STBI_rgb_alpha );
	if ( !image )
	{
		printf( "%s Failed to load image\n", generated_font.get_file_name( ).c_str( ) );
		stbi_image_free( image );
		return generated_font;
	}

	for ( auto& map_pair : temp_map )
	{

		int x_offset = map_pair.second.x;
		int y_offset = map_pair.second.y;
		int portion_width = map_pair.second.width;
		int portion_height = map_pair.second.height;

		if ( x_offset + portion_width > width || y_offset + portion_height > height )
		{
			printf( "Portion dimensions exceed image bounds\n" );
			stbi_image_free( image );
			return generated_font;
		}


		stbi_uc* portion_data = new stbi_uc[ portion_width * portion_height * 4 ];
		for ( int y = 0; y < portion_height; ++y )
		{
			memcpy( &portion_data[ y * portion_width * 4 ],
					&image[ ( ( y + y_offset ) * width + x_offset ) * 4 ],
					portion_width * 4 );
		}


		GLuint textureID;
		glGenTextures( 1, &textureID );
		glBindTexture( GL_TEXTURE_2D, textureID );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, portion_width, portion_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, portion_data );

		delete[ ] portion_data;

		GLenum error = glGetError( );
		if ( error != GL_NO_ERROR )
		{
			printf( "OpenGL error %d at %d\n", error, map_pair.second.id );
			continue;
		}

		temp_map[ map_pair.first ].texture_id = textureID;
		engine_list_textures.emplace( std::string( 1, char( map_pair.second.id ) ), textureID );
	}

	generated_font.set_map( temp_map );

	printf( "Generated %s\n", generated_font.get_font_name( ).c_str( ) );

	stbi_image_free( image );

	return generated_font;
}