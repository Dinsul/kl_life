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
    bool _cycled;
    int **_map;
    uniqList<Position> _challengerForBorn;

public:
    SimpleUniverse(bool cycled = true, int width = 50, int height = 50);
    ~SimpleUniverse() override;

    // Universe interface
    void refresh() override;
    void clear() override;

    void nextGeneration() override;
    void addCell(const Position &pos) override;
    void killCell(const Position &pos) override;
};

} // CGL

#endif // SIMPLEUNIVERSE_H
