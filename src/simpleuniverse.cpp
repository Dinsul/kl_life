#include "simpleuniverse.h"
#include "logger.h"

#include "chrono"

#include <SFML/Graphics.hpp>

void cgl::SimpleUniverse::refresh()
{
    quick_trace();

    _inhabitants.clear();
    _challengerForBorn.clear();

    for (int x = 0; x < _width; ++x)
    {
        for (int y = 0; y < _height; ++y)
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

                        int loopX = nx;
                        int loopY = ny;

                        if (ny >= _height || nx >= _width || ny < 0 || nx < 0)
                        {
                            if (!_cycled)
                            {
                                continue;
                            }
                            else
                            {
                                if (nx < 0)
                                    loopX = _width - 1;
                                if (ny < 0)
                                    loopY = _height - 1;
                                if (nx >= _width)
                                    loopX = 0;
                                if (ny >= _height)
                                    loopY = 0;

                            }
                        }

                        if (_map[loopX][loopY])
                        {
                            _inhabitants.add({x, y});
                        }
                        else
                        {
                            _challengerForBorn.add({loopX, loopY});
                        }
                    }
                }
            }
        }
    }
}

cgl::SimpleUniverse::SimpleUniverse(bool cycled, int width, int height)
    : Universe(width, height), _cycled(cycled)
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

    refresh();

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

    _inhabitants.add(pos);
}

void cgl::SimpleUniverse::killCell(const cgl::Position &pos)
{
    quick_trace();

    _map[pos.x][pos.y] = 0;

    _inhabitants.erase(pos);
}
