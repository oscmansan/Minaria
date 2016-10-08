#include "Rect.h"


Rect::Rect()
{
}

Rect::Rect(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Rect::~Rect()
{
}

bool Rect::intersects(const Rect &r) const
{
	return 
		r.contains(glm::ivec2(x, y)) ||
		r.contains(glm::ivec2(x, y + height)) ||
		r.contains(glm::ivec2(x + width, y)) ||
		r.contains(glm::ivec2(x + width, y + height));
}

bool Rect::contains(const glm::ivec2 &point) const
{
	return (point.x >= x && point.x <= x + width &&
		point.y >= y && point.y <= y + height);
}

std::string Rect::toString() const
{
	std::ostringstream oss;
	oss << "(" << x << ", " << y << ", " << width << ", " << height << ")";
	return oss.str();
}
