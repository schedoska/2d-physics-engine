#include "Rectangle.h"

dm2::Rectangle::Rectangle(float _x, float _y, float _width, float _height)
    :x(_x), y(_y), width(_width), height(_height) {}

float dm2::Rectangle::left() const
{
    return x;
}

float dm2::Rectangle::top() const
{
    return y;
}

float dm2::Rectangle::right() const
{
    return x + width;
}

float dm2::Rectangle::bottom() const
{
    return y + height;
}
