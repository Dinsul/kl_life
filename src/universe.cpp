#include "universe.h"

const cgl::uniqList<cgl::Position> &cgl::Universe::inhabitants() const
{
    return _inhabitants;
}

cgl::Universe::Universe(int width, int height)
    : _width(width), _height(height)
{
}

cgl::Universe::~Universe(){}

int cgl::Universe::height()
{
    return _height;
}

int cgl::Universe::width()
{
    return _width;
}

void cgl::Universe::addCell(int x, int y)
{
    addCell(Position{x, y});
}

void cgl::Universe::killCell(int x, int y)
{
    killCell(Position{x, y});
}
