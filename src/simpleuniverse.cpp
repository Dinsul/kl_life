#include "simpleuniverse.h"
#include "logger.h"

#include <SFML/Graphics.hpp>

void CGL::SimpleUniverse::checkCells()
{
    quick_trace();

    for (int x = 0; x < 100; ++x)
    {
        for (int y = 0; y < 100; ++y)
        {
            if (_inhabitants[x][y])
            {
                _challengerForDie.add({x, y});

                for (int nx = x - 1; nx <= x + 1; ++nx)
                {

                    for (int ny = y - 1; ny <= y + 1; ++ny)
                    {
                        if (ny == y && nx == x)
                        {
                            continue;
                        }

                        if (_inhabitants[nx][ny])
                        {

                            _challengerForDie.add({x, y});
                        }
                        else
                        {
                            _challengerForBorn.add({nx, ny});
                        }
                    }
                }
            }
        }
    }
}


CGL::SimpleUniverse::SimpleUniverse()
{
    quick_trace();

    for (int x = 0; x < 100; ++x)
    {
        for (int y = 0; y < 100; ++y)
        {
            _inhabitants[x][y] = 0;
        }
    }
}

CGL::SimpleUniverse::~SimpleUniverse()
{}

void CGL::SimpleUniverse::nextGeneration()
{
    quick_trace();

    checkCells();

    for (auto & cell : _challengerForDie)
    {
        if (cell.second > 4 || cell.second < 3)
        {
            _inhabitants[cell.first.x][cell.first.y] = 0;
        }
    }

    for (auto & cell : _challengerForBorn)
    {
        if (cell.second == 3)
        {
            _inhabitants[cell.first.x][cell.first.y] = 1;
        }
    }

    _challengerForDie.clear();
    _challengerForBorn.clear();
}

void CGL::SimpleUniverse::addCell(const CGL::Position &pos)
{
    quick_trace();

    _inhabitants[pos.x][pos.y] = 1;
}

void CGL::SimpleUniverse::draw(sf::RenderWindow &window)
{
    quick_trace();

    sf::RectangleShape rect;

    rect.setFillColor(sf::Color{200, 100, 0});
    rect.setSize(sf::Vector2f{10,10});

    for (int x = 0; x < 100; ++x)
    {
        for (int y = 0; y < 100; ++y)
        {
            if (_inhabitants[x][y])
            {
                rect.setPosition(x * 10, y * 10);

                window.draw(rect);
            }
        }
    }
}
