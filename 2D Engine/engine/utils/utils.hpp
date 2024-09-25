#pragma once

#include <chrono>
#include <cmath>
#include "string"
#include "vector"
#include "unordered_map"

namespace utils
{
	template <typename t> inline void move( std::vector<t>& v, size_t oldIndex, size_t newIndex )
	{
		if ( oldIndex > newIndex )
			std::rotate( v.rend( ) - oldIndex - 1, v.rend( ) - oldIndex, v.rend( ) - newIndex );
		else
			std::rotate( v.begin( ) + oldIndex, v.begin( ) + oldIndex + 1, v.begin( ) + newIndex + 1 );
	}
	inline double fastPow(double a, double b) {
		union {
			double d;
			int x[2];
		} u = { a };
		u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
		u.x[0] = 0;
		return u.d;
	}

	inline double distance(double x, double y, double x2, double y2) {
		return sqrt(std::pow((x2 - x), 2) + std::pow((y2 - y), 2));
	}

	inline double random() {
		return ((double)rand() / (RAND_MAX));
	}
}