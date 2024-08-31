#pragma once

// currently useless
class bounds : public rect
{
public:
	vec2 tl, tr, br, bl;

	bounds() : rect(0, 0, 0, 0) { }
	bounds(float x, float y, float width, float height) : rect(x, y, width, height)
	{
		this->tl = vec2(x, y);
		this->tr = vec2(x + width, y);
		this->br = vec2(x + width, y + height);
		this->bl = vec2(x, y + height);
	}

	bounds operator-(bounds const& r)
	{
		return bounds(this->x - r.x, this->y - r.y, this->width - width, this->height - r.height);
	}

	bool is_inside(bounds position)
	{
		return true;
	}
};