#include "universe.h"

const cgl::uniqList<cgl::Position> &cgl::Universe::inhabitants() const
{
    return _inhabitants;
}

cgl::Universe::~Universe(){}

void cgl::Universe::addCell(int x, int y)
{
    addCell(Position{x, y});
}

void cgl::Universe::killCell(int x, int y)
{
    killCell(Position{x, y});
}
