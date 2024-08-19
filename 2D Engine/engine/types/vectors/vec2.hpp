#pragma once

class vec2
{
public:
	float x, y;

	vec2( ) : x(0), y(0) { }
	vec2( float x, float y ) : x( x ), y( y ) { }

	bool is_zero() { return this->x == 0 && this->y == 0; }

	void resolve_engine_pixel( vec2 screen )
	{
		this->y = screen.y - this->y;
		this->x = ( this->x / screen.x * 2.f ) - 1.f;
		this->y = ( this->y / screen.y * 2.f ) - 1.f;
	}

	void set( float x, float y )
	{
		this->x = x;
		this->y = y;
	}

	vec2 resolve_engine_pixel_v( vec2 screen )
	{
		this->y = screen.y - this->y;
		this->x = ( this->x / screen.x * 2.f ) - 1.f;
		this->y = ( this->y / screen.y * 2.f ) - 1.f;

		return *this;
	}

	vec2 operator+ ( const vec2& r )
	{
		return vec2( this->x + r.x, this->y + r.y );
	}
};