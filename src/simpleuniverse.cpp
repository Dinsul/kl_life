#include "simpleuniverse.h"
#include "logger.h"
#include "settings.h"

#include "chrono"

#include <SFML/Graphics.hpp>

void cgl::SimpleUniverse::checkCells()
{
    quick_trace();

    _inhabitants.clear();
    _challengerForBorn.clear();

    auto &settings = Settings::get();

    for (int x = 0; x < settings.universeWidth; ++x)
    {
        for (int y = 0; y < settings.universeHeight; ++y)
        {
            if (_map[x][y])
            {
                _inhabitants.add({x, y});

                for (int nx = x - 1; nx <= x + 1; ++nx)
                {

                    for (int ny = y - 1; ny <= y + 1; ++ny)
                    {
                        if (ny == y && nx == x)
                        {
                            continue;
                        }

                        if (_map[nx][ny])
                        {

                            _inhabitants.add({x, y});
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


cgl::SimpleUniverse::SimpleUniverse()
    : _width(Settings::get().universeWidth),
      _height(Settings::get().universeHeight)
{
    quick_trace();

    _map = new int*[static_cast<size_t>(_width)];

    for (int x = 0; x < _width; ++x)
    {
        _map[x] = new int[static_cast<size_t>(_height)];
    }

    clear();
}

cgl::SimpleUniverse::~SimpleUniverse()
{
    for (int x = 0; x < _width; ++x)
    {
        delete [] _map[x];
    }

    delete []  _map;
}

int cgl::SimpleUniverse::width()    { return _width;  }
int cgl::SimpleUniverse::height()   { return _height; }

void cgl::SimpleUniverse::refresh()
{
    checkCells();
}

void cgl::SimpleUniverse::clear()
{
    for (int x = 0; x < _width; ++x)
    {
        for (int y = 0; y < _height; ++y)
        {
            _map[x][y] = 0;
        }
    }
}

void cgl::SimpleUniverse::nextGeneration()
{
    quick_trace();

    checkCells();

    for (auto & cell : _inhabitants)
    {
        if (cell.second > 4 || cell.second < 3)
        {
            _map[cell.first.x][cell.first.y] = 0;
        }
    }

    for (auto & cell : _challengerForBorn)
    {
        if (cell.second == 3)
        {
            _map[cell.first.x][cell.first.y] = 1;
        }
    }

}

void cgl::SimpleUniverse::addCell(const cgl::Position &pos)
{
    quick_trace();

    _map[pos.x][pos.y] = 1;

    checkCells();
}

void cgl::SimpleUniverse::killCell(const cgl::Position &pos)
{
    quick_trace();

    _map[pos.x][pos.y] = 0;

    checkCells();
}
