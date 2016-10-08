#pragma once

#include <glm/glm.hpp>
#include <sstream>
#include <string>

class Rect
{
public:
	Rect();
	Rect(int x, int y, int width, int height);
	~Rect();

	int x = 0, y = 0, width = 0, height = 0;
	
	bool intersects(const Rect &r) const;
	bool contains(const glm::ivec2 &point) const;

	std::string toString() const;
};

