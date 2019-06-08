#ifndef INFINITEUNIVERSE_H
#define INFINITEUNIVERSE_H

#include "universe.h"


namespace CGL {


class InfiniteUniverse : public Universe
{
public:
    InfiniteUniverse();

public:
    // Universe interface
    unsigned int height() override;
    unsigned int width() override;
    void nextGeneration() override;
    void addCell(const Position &pos) override;
    void draw(sf::RenderWindow &window) override;
};

}

#endif // INFINITEUNIVERSE_H
