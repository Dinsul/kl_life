#ifndef LIFE_TYPES_H
#define LIFE_TYPES_H

//! \file
//! Здесь содержатся объявления
//! необходимых классов, типов и структур, которые
//! используются в программе
//!

#include <map>

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

};

template <class T>
class uniqList : public std::map<T, size_t>
{
public:
    size_t add(const T& value)
    {
        return  ++(*this)[value];
    }

    size_t countOf(const T& value)
    {
        try {
            return this->at(value);
        } catch (...) {
            return 0;
        }
    }
};

}

#endif // LIFE_TYPES_H
