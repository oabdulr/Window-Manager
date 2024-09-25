#pragma once
#include "../../utils/utils.hpp"

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

	float distance(vec2 const& v) {
		return utils::distance(this->x, this->y, v.x, v.y);
	}

	vec2 resolve_engine_pixel_v( vec2 screen )
	{
		this->y = screen.y - this->y;
		this->x = ( this->x / screen.x * 2.f ) - 1.f;
		this->y = ( this->y / screen.y * 2.f ) - 1.f;

		return *this;
	}

	// Normalize the vector
	void normalize()
	{
		float length = sqrt(x * x + y * y);
		if (length != 0) {
			x /= length;
			y /= length;
		}
	}

	// Dot product of two vectors
	float dot(const vec2& other) const
	{
		return this->x * other.x + this->y * other.y;
	}

	float length() const
	{
		return sqrt(x * x + y * y);
	}

	// Overload += operator
	vec2& operator+=(const vec2& r)
	{
		this->x += r.x;
		this->y += r.y;
		return *this;
	}

	// Overload -= operator
	vec2& operator-=(const vec2& r)
	{
		this->x -= r.x;
		this->y -= r.y;
		return *this;
	}

	vec2 operator- (const vec2& r)
	{
		return vec2(this->x - r.x, this->y - r.y);
	}

	vec2 operator- (const float& r)
	{
		return vec2(this->x - r, this->y - r);
	}

	vec2 operator- ()
	{
		return vec2(-this->x, -this->y);
	}

	vec2 operator+ ( const vec2& r )
	{
		return vec2( this->x + r.x, this->y + r.y );
	}

	vec2 operator* (const vec2& r)
	{
		return vec2(this->x * r.x, this->y * r.y);
	}

	vec2 operator* (const float& r)
	{
		return vec2(this->x * r, this->y * r);
	}

	vec2 operator* (float r) const
	{
		return vec2(this->x * r, this->y * r);
	}

	vec2 operator/ (const float& r)
	{
		return vec2(this->x / r, this->y / r);
	}
};