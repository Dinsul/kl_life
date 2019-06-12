#ifndef LIFE_TYPES_H
#define LIFE_TYPES_H

//! \file
//! Здесь содержатся объявления
//! необходимых классов, типов и структур, которые
//! используются в программе
//!

#include <map>
#include <algorithm>

namespace cgl {

struct Position
{
    int x;
    int y;

    bool operator <(const Position &other) const
    {
        if (this->y < other.y)
            return true;

        if (this->y == other.y)
            return this->x < other.x;

        return false;
    }

    Position(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    bool operator == (const Position &other) const
    {
        return this->x == other.x && this->y == other.y;
    }
};

template <class T>
class uniqList : public std::map<T, size_t>
{
public:
    size_t add(const T& value)
    {
        return  ++(*this)[value];
    }

    size_t countOf(const T& value) const
    {
        try {
            return this->at(value);
        } catch (...) {
            return 0;
        }
    }

    bool operator == (const uniqList<T> &other) const
    {
        if (this->size() != other.size())
        {
            return false;
        }

        return std::equal(this->begin(), this->end(), other.begin(), other.end());
    }
};

}

#endif // LIFE_TYPES_H
