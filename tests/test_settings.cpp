#define BOOST_TEST_MODULE test_life

#include "settings.h"
#include "info.h"
#include "logger.h"

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_settings)

BOOST_AUTO_TEST_CASE(test_save_load)
{
    auto defaultFilename = cgl::cat(getenv("HOME"), "/.", PRJ_NAME, "/settings.ini");

    boost::filesystem::path iniPath{defaultFilename};

    if (boost::filesystem::exists(iniPath))
    {
        boost::filesystem::remove(iniPath);
    }

    BOOST_CHECK(!boost::filesystem::exists(iniPath));

    // Здесь файл поумолчанью существовать не должен
    // Будет соответствующее сообщение
    auto &ls = cgl::Settings::get();


    // Проверяем значения поумолчанию
    BOOST_CHECK(ls.universeHeight == 200);
    BOOST_CHECK(ls.universeWidth == 200);
    BOOST_CHECK(ls.generationPeriod == 100);

    // Меняем значеничения
    ls.universeHeight = 30;
    ls.universeWidth = 30;
    ls.generationPeriod = 200;

    BOOST_CHECK(ls.universeHeight == 30);
    BOOST_CHECK(ls.universeWidth == 30);
    BOOST_CHECK(ls.generationPeriod == 200);

    // Возвращаем значение поумолчанию
    // Здесь файл поумолчанью всё ещё отсутствует
    // Будет соответствующее сообщение
    ls.load();

    BOOST_CHECK(ls.universeHeight == 200);
    BOOST_CHECK(ls.universeWidth == 200);
    BOOST_CHECK(ls.generationPeriod == 100);

    // Сохраняем изменённое значение
    ls.universeHeight = 30;
    ls.universeWidth = 30;
    ls.generationPeriod = 200;
    ls.save();

    // Файл настроек должен был создасться после сохранения
    BOOST_CHECK(boost::filesystem::exists(iniPath));

    ls.load();

    BOOST_CHECK(ls.universeHeight == 30);
    BOOST_CHECK(ls.universeWidth == 30);
    BOOST_CHECK(ls.generationPeriod == 200);

}


BOOST_AUTO_TEST_SUITE_END()
