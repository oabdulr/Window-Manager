#pragma once

class rect
{
public:
	float x, y, width, height;

	rect( ) : x( 0 ), y( 0 ), width( 0 ), height( 0 ) { }
	rect( float x, float y, float width, float height ) : x( x ), y( y ), width( width ), height( height ) { }

	rect operator-( rect const& r )
	{
		return rect( this->x - r.x, this->y - r.y, this->width - width, this->height - r.height );
	}

	vec2 operator-( vec2 const& r )
	{
		return vec2( this->x - r.x, this->y - r.y );
	}

	bool is_inside( vec2 position )
	{
		if ( this->x > position.x || this->y > position.y )
			return false;
		if ( this->x + width < position.x || this->y + height < position.y )
			return false;

		return true;
	}

	void apply_scale(float scale, bool only_h = false, bool only_w = false)
	{
		this->height *= scale;
		this->width *= scale;
	}

	void apply_scale_h(float scale)
	{
		this->height *= scale;
	}

	void apply_scale_w(float scale)
	{
		this->width *= scale;
	}
};