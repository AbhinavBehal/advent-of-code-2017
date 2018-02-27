#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <cstddef>
#include <utility>

struct Point
{
	int x;
	int y;
	
	void rotL()
	{
		x = -std::exchange(y, x);
	}

	void rotR()
	{
		y = -std::exchange(x, y);
	}

	void reverse()
	{
		x = -x;
		y = -y;
	}
	
	int dist(const Point &p) const
	{
		return std::abs(x - p.x) + std::abs(y - p.y);
	}

	Point &operator+=(const Point &p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}

	Point operator+(const Point &p) const
	{
		return Point(*this) += p;
	}

	bool operator==(const Point &p) const 
	{
		return x == p.x && y == p.y;
	}

	bool operator!=(const Point &p) const 
	{
		return !(*this == p);
	}

	struct Hash
	{
		std::size_t operator()(const Point &p) const 
		{
			return (p.y << 16) ^ p.x;
		}
	};
};

#endif