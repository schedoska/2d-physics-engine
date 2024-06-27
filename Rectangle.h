#pragma once

namespace dm2 
{
	struct Rectangle
	{
		Rectangle(float _x = 0, float _y = 0, float _width = 0, float _height = 0);
		float x, y, width, height;
		float left() const;
		float top() const;
		float right() const;
		float bottom() const;
	};
}

