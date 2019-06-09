#include "simpleuniverse.h"
#include "logger.h"
#include "settings.h"

#include "chrono"

#include <SFML/Graphics.hpp>

void CGL::SimpleUniverse::checkCells()
{
    quick_trace();

    _challengerForDie.clear();
    _challengerForBorn.clear();

    auto &settings = Settings::get();

    for (size_t x = 0; x < settings.universeWidth; ++x)
    {
        for (size_t y = 0; y < settings.universeHeight; ++y)
        {
            if (_inhabitants[x][y])
            {
                _challengerForDie.add({x, y});

                for (size_t nx = x - 1; nx <= x + 1; ++nx)
                {

                    for (size_t ny = y - 1; ny <= y + 1; ++ny)
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
    : _width(Settings::get().universeWidth),
      _height(Settings::get().universeHeight)
{
    quick_trace();

    _inhabitants = new int*[_width];

    for (size_t x = 0; x < _width; ++x)
    {
        _inhabitants[x] = new int[_height];
    }


    for (size_t x = 0; x < _width; ++x)
    {
        for (size_t y = 0; y < _height; ++y)
        {
            _inhabitants[x][y] = 0;
        }
    }
}

CGL::SimpleUniverse::~SimpleUniverse()
{
    for (size_t x = 0; x < _width; ++x)
    {
        delete [] _inhabitants[x];
    }

    delete []  _inhabitants;
}

size_t CGL::SimpleUniverse::height()   { return _height; }
size_t CGL::SimpleUniverse::width()    { return _width;  }

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

}

void CGL::SimpleUniverse::addCell(const CGL::Position &pos)
{
    quick_trace();

    _inhabitants[pos.x][pos.y] = 1;
}

void CGL::SimpleUniverse::killCell(const CGL::Position &pos)
{
    quick_trace();

    _inhabitants[pos.x][pos.y] = 0;
}

void CGL::SimpleUniverse::draw(sf::RenderWindow &window)
{
    quick_trace();
    auto begin = std::chrono::steady_clock::now();

    sf::RectangleShape rect;
    auto cellSize = Settings::get().cellSize;

    rect.setFillColor(sf::Color{200, 100, 0});
    rect.setSize(sf::Vector2f{10,10});

    for (auto & cell : _challengerForDie)
    {
        rect.setPosition(cell.first.x * cellSize, cell.first.y * cellSize);

        window.draw(rect);
    }

    auto end = std::chrono::steady_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    Logger::debug(makeStr("Time of draw", elapsed_us.count(), "µs"));
}
