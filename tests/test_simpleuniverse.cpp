#define BOOST_TEST_MODULE test_life

#include "info.h"
#include "life_types.hpp"
#include "simpleuniverse.h"

#include <iostream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_universe)

// Тесты основного функционала
BOOST_AUTO_TEST_CASE(test_main)
{
    // Создание вселенной
    cgl::SimpleUniverse un{false, 10, 10};

    BOOST_CHECK(un.inhabitants().size() == 0);
    BOOST_CHECK(un.width() == 10);
    BOOST_CHECK(un.height() == 10);

    // Добавление первого обитателя
    cgl::Position inhabitant_1{1, 2};
    un.addCell(inhabitant_1);

    BOOST_CHECK(un.inhabitants().size() == 1);
    BOOST_CHECK(un.inhabitants().countOf({1,2}) == 1);

    // Проверка на уникальность обитателей
    un.addCell(inhabitant_1);

    BOOST_CHECK(un.inhabitants().size() == 1);
    BOOST_CHECK(un.inhabitants().countOf(inhabitant_1) == 2);

    // Добавление второго обитателя
    cgl::Position inhabitant_2{2, 2};
    un.addCell(inhabitant_2);

    BOOST_CHECK(un.inhabitants().size() == 2);
    BOOST_CHECK(un.inhabitants().countOf(inhabitant_1) == 2);
    BOOST_CHECK(un.inhabitants().countOf(inhabitant_2) == 1);

    // Удаление обитателя
    un.killCell(inhabitant_1);

    BOOST_CHECK(un.inhabitants().size() == 1);
    BOOST_CHECK(un.inhabitants().countOf(inhabitant_1) == 0);
    BOOST_CHECK(un.inhabitants().countOf(inhabitant_2) == 1);


}

// Сравнение вселенных
BOOST_AUTO_TEST_CASE(test_equal)
{
    cgl::SimpleUniverse u1{false, 10, 10};
    cgl::SimpleUniverse u2{false, 10, 10};

    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());

    u1.addCell({1,1});
    u1.addCell({1,2});
    u1.addCell({1,3});

    BOOST_CHECK(u1.inhabitants() != u2.inhabitants());

    u2.addCell({1,1});
    u2.addCell({1,2});
    u2.addCell({1,3});

    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());

    u1.nextGeneration();

    BOOST_CHECK(u1.inhabitants() != u2.inhabitants());

    u2.nextGeneration();

    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());

}

// Логика
BOOST_AUTO_TEST_CASE(test_logic)
{
    cgl::SimpleUniverse u1{false, 10, 10};
    cgl::SimpleUniverse u2{false, 10, 10};

    // Один единственный обитатель умрёт
    u1.clear();
    u1.addCell({1,1});
    u1.nextGeneration();
    u1.refresh();

    BOOST_CHECK(u1.inhabitants().size() == 0);
    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());

    // Два любых обитателя умрут
    u1.clear();
    u1.addCell({1,1});
    u1.addCell({5,5});
    u1.nextGeneration();
    u1.refresh();

    BOOST_CHECK(u1.inhabitants().size() == 0);
    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());

    // Даже если они соседи, два обитателя умрут
    u1.clear();
    u1.addCell({1,1});
    u1.addCell({1,2});

    // Сначала проверим соседство
    u1.refresh(); // подсчёт соседей
    BOOST_CHECK(u1.inhabitants().size() == 2);
    BOOST_CHECK(u1.inhabitants().countOf({1,1}) == 2);
    BOOST_CHECK(u1.inhabitants().countOf({1,2}) == 2);

    u1.nextGeneration();
    u1.refresh();

    BOOST_CHECK(u1.inhabitants().size() == 0);
    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());

    // Вертикальная тройная палка должна стать горизонтальной
    u1.clear();
    u1.addCell({1,1});
    u1.addCell({1,2});
    u1.addCell({1,3});

    u2.clear();
    u2.addCell({0,2});
    u2.addCell({1,2});
    u2.addCell({2,2});

    u2.refresh(); // подсчёт соседей

    u1.nextGeneration();
    u1.refresh();

    BOOST_CHECK(u1.inhabitants().size() == 3);
    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());

    // Квадрат останется квадратом
    u1.clear();
    u1.addCell({1,1});
    u1.addCell({1,2});
    u1.addCell({2,1});
    u1.addCell({2,2});

    u2.clear();
    u2.addCell({1,1});
    u2.addCell({1,2});
    u2.addCell({2,1});
    u2.addCell({2,2});

    u2.refresh(); // подсчёт соседей

    u1.nextGeneration();
    u1.refresh();

    BOOST_CHECK(u1.inhabitants().size() == 4);
    BOOST_CHECK(u1.inhabitants() == u2.inhabitants());
}

BOOST_AUTO_TEST_SUITE_END()
