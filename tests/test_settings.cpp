#define BOOST_TEST_MODULE test_life

#include "settings.h"
#include "info.h"

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_settings)

BOOST_AUTO_TEST_CASE(test_save_load)
{
    std::string defaultFilename(PRJ_NAME".ini");

    boost::filesystem::path iniPath{defaultFilename};

    if (boost::filesystem::exists(iniPath))
    {
        boost::filesystem::remove(iniPath);
    }

    BOOST_CHECK(!boost::filesystem::exists(iniPath));

    // Здесь файл поумолчанью существовать не должен
    // Будет соответствующее сообщение
    auto &ls = cgl::Settings::get();

    std::cout << ls.logPath << std::endl;
    // Проверяем значение поумолчанию
    BOOST_CHECK(ls.logPath == "log");

    // Меняем значение
    ls.logPath = "MyLog";

    BOOST_CHECK(ls.logPath == "MyLog");

    // Возвращаем значение поумолчанию
    // Здесь файл поумолчанью всё ещё отсутствует
    // Будет соответствующее сообщение
    ls.load();

    BOOST_CHECK(ls.logPath == "log");

    // Сохраняем изменённое значение
    ls.logPath = "MyLog";
    ls.save();
    ls.load();

    BOOST_CHECK(ls.logPath == "MyLog");

    // Файл поумолцанию должен был создасться после сохранения
    BOOST_CHECK(boost::filesystem::exists(iniPath));
}


BOOST_AUTO_TEST_SUITE_END()
