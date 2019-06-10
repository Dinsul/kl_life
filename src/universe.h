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
    //!
    //! \brief _inhabitants
    //! Содержит пары значений координата обитателя и количество соседей
    //!
    uniqList<Position> _inhabitants;

public:
    virtual ~Universe();
    virtual int  height()  = 0;
    virtual int  width()   = 0;
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
