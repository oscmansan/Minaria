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

Rect::Rect(glm::ivec2 pos, glm::ivec2 size) {
    x = pos.x;
    y = pos.y;
    width = size.x;
    height = size.y;
}

Rect::~Rect()
{
}

glm::ivec2 Rect::getMin() const
{
    return glm::ivec2(x, y);
}

glm::ivec2 Rect::getMax() const
{
    return getMin() + glm::ivec2(width, height);
}

glm::ivec2 Rect::getSize() const
{
    return glm::ivec2(width, height);
}

bool Rect::_intersects(const Rect &r) const
{
    return
        r.contains(glm::ivec2(x, y)) ||
        r.contains(glm::ivec2(x, y + height)) ||
        r.contains(glm::ivec2(x + width, y)) ||
        r.contains(glm::ivec2(x + width, y + height));
}

bool Rect::intersects(const Rect &r) const
{
    return _intersects(r) || r._intersects(*this);
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
