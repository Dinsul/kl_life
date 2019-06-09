#ifndef SIMPLEUNIVERSE_H
#define SIMPLEUNIVERSE_H

#include "universe.h"
#include "life_types.hpp"

#include <vector>

namespace sf {
class RenderWindow;
}

namespace CGL {

class SimpleUniverse : public Universe
{
    size_t _width;
    size_t _height;

    int **_inhabitants;
    uniqList<Position> _challengerForBorn;
    uniqList<Position> _challengerForDie;

    void checkCells();

public:
    SimpleUniverse();
    ~SimpleUniverse() override;

    // Universe interface
    size_t width()  override;
    size_t height() override;
    void nextGeneration() override;
    void addCell(const Position &pos) override;
    void killCell(const Position &pos) override;


    void draw(sf::RenderWindow &window) override;

};

} // CGL

#endif // SIMPLEUNIVERSE_H
