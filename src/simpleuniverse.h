#ifndef SIMPLEUNIVERSE_H
#define SIMPLEUNIVERSE_H

#include "universe.h"
#include "life_types.hpp"

#include <vector>

namespace sf {
class RenderWindow;
}

namespace cgl {

class SimpleUniverse : public Universe
{
    int _width;
    int _height;

    int **_map;
    uniqList<Position> _challengerForBorn;

    void checkCells();

public:
    SimpleUniverse();
    ~SimpleUniverse() override;

    // Universe interface
    int  width()  override;
    int  height() override;
    void refresh() override;
    void clear() override;

    void nextGeneration() override;
    void addCell(const Position &pos) override;
    void killCell(const Position &pos) override;
};

} // CGL

#endif // SIMPLEUNIVERSE_H
