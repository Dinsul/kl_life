#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <stddef.h>

namespace sf {
class RenderWindow;
}

namespace CGL {

class Position;

//!
//! \brief The Universe class
//! Интерфес вселенной.
//!
class Universe
{
public:
    virtual ~Universe();
    virtual size_t height() = 0;
    virtual size_t width()  = 0;
    virtual void nextGeneration() = 0;
    virtual void addCell(const Position &pos)   = 0;
    virtual void killCell(const Position &pos)  = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    virtual void addCell(size_t x, size_t y);
    virtual void killCell(size_t x, size_t y);

};


//Universe::~Universe(){}

} // CGL

#endif // UNIVERSE_H
