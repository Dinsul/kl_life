#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "life_types.hpp"

namespace sf {
class RenderWindow;
}

namespace cgl {

//!
//! \brief The Universe class
//! Интерфес вселенной.
//!
class Universe
{
protected:
    int _width;
    int _height;
    //!
    //! \brief _inhabitants
    //! Содержит пары значений координата обитателя и количество соседей
    //!
    uniqList<Position> _inhabitants;

public:
    Universe(int width = 50, int height = 50);

    virtual ~Universe();
    virtual int  height();
    virtual int  width();
    virtual void refresh() = 0;
    virtual void clear()   = 0;

    virtual void nextGeneration() = 0;
    virtual void addCell(const Position &pos)   = 0;
    virtual void killCell(const Position &pos)  = 0;

    virtual void addCell(int x, int y);
    virtual void killCell(int x, int y);

    virtual const uniqList<Position> &inhabitants() const;
};


//Universe::~Universe(){}

} // CGL

#endif // UNIVERSE_H
