#include "universe.h"
#include "life_types.hpp"

CGL::Universe::~Universe(){}

void CGL::Universe::addCell(size_t x, size_t y)
{
    addCell(Position{x, y});
}

void CGL::Universe::killCell(size_t x, size_t y)
{
    killCell(Position{x, y});
}
