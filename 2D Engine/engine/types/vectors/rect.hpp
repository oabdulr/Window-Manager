#pragma once

class rect
{
public:
	float x, y, width, height;

	rect( ) : x( 0 ), y( 0 ), width( 0 ), height( 0 ) { }
	rect( float x, float y, float width, float height ) : x( x ), y( y ), width( width ), height( height ) { }

	rect operator-( rect const& r )
	{
		return rect( this->x - r.x, this->y - r.y, this->width, this->height);
	}

	rect operator+(rect const& r)
	{
		return rect(this->x + r.x, this->y + r.y, this->width, this->height);
	}

	// Overload += operator
	rect& operator+=(const vec2& r)
	{
		this->x += r.x;
		this->y += r.y;
		return *this;
	}

	// Overload -= operator
	rect& operator-=(const vec2& r)
	{
		this->x -= r.x;
		this->y -= r.y;
		return *this;
	}

	// Overload += operator
	rect& operator+=(const rect& r)
	{
		this->x += r.x;
		this->y += r.y;
		return *this;
	}

	// Overload -= operator
	rect& operator-=(const rect& r)
	{
		this->x -= r.x;
		this->y -= r.y;
		return *this;
	}

	vec2 operator+(vec2 const& r)
	{
		return vec2(this->x + r.x, this->y + r.y);
	}

	vec2 operator-( vec2 const& r )
	{
		return vec2( this->x - r.x, this->y - r.y );
	}

	vec2 center() 
	{
		return vec2(this->x + (this->width / 2), this->y + (this->height / 2));
	}

	vec2 tl() 
	{
		return vec2(this->x, this->y);
	}

	vec2 tr()
	{
		return vec2(this->x + this->width, this->y);
	}

	vec2 br()
	{
		return vec2(this->x + this->width, this->y + this->height);
	}

	vec2 bl()
	{
		return vec2(this->x + this->width, this->y + this->height);
	}

	vec2 tc()
	{
		return vec2(this->x + (this->width/2), this->y);
	}

	vec2 rc()
	{
		return vec2(this->x + this->width, this->y + (this->height/2));
	}

	vec2 bc()
	{
		return vec2(this->x + (this->width / 2), this->y + this->height);
	}

	vec2 lc()
	{
		return vec2(this->x, this->y + (this->height/2));
	}

	float distance(rect const& v) {
		return utils::distance(this->x, this->y, v.x, v.y);
	}

	float distance(vec2 const& v) {
		return utils::distance(this->x, this->y, v.x, v.y);
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

	void set(vec2 data) {
		this->x = data.x;
		this->y = data.y;
	}

	void append(vec2 data) {
		this->x += data.x;
		this->y += data.y;
	}

	void entropy_append(vec2 data) {
		this->x += data.x + utils::random() * 10;
		this->y += data.y + utils::random() * 10;
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