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
    int _inhabitants[100][100];
    uniqList<Position> _challengerForBorn;
    uniqList<Position> _challengerForDie;

    void checkCells();

public:
    SimpleUniverse();
    ~SimpleUniverse() override;

    // Universe interface
    unsigned int height() override {return 100;}
    unsigned int width()  override {return 100;}
    void nextGeneration() override;
    void addCell(const Position &pos) override;


    void draw(sf::RenderWindow &window) override;
};

} // CGL

#endif // SIMPLEUNIVERSE_H
