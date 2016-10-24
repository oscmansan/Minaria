#pragma once

#include <glm/glm.hpp>
#include <sstream>
#include <string>

class Rect
{
private:
    bool _intersects(const Rect &r) const;

public:
	Rect();
	Rect(int x, int y, int width, int height);
	~Rect();

	int x = 0, y = 0, width = 0, height = 0;
	
    glm::ivec2 getMin() const;
    glm::ivec2 getMax() const;
    glm::ivec2 getSize() const;

    bool intersects(const Rect &r) const;
	bool contains(const glm::ivec2 &point) const;

	std::string toString() const;
};

