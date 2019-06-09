#include "settings.h"
#include "logger.h"
#include "info.h"

#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

CGL::Settings::Settings()
{
    load();
}

void CGL::Settings::load(const std::string &filename)
{
    boost::property_tree::ptree settingsTree;

    try
    {
        boost::property_tree::ini_parser::read_ini(filename, settingsTree);
    }
    catch (...)
    {
         std::cerr << "Error: can not load log settings." << std::endl;
    }

    // Журналирование
//    logLevel    = settingsTree.get<LogLevel> ("LogSettings.logLevel",    LogLevel::info);
    logToFile   = settingsTree.get<bool>        ("LogSettings.logToFile",   true);
    logToStdout = settingsTree.get<bool>        ("LogSettings.logToStdout", false);
    logLast     = settingsTree.get<bool>        ("LogSettings.logLast",     false);
    logPath     = settingsTree.get<std::string> ("LogSettings.logPath",     "log");

    // Отображение
    mainFrameHeight = settingsTree.get<size_t>  ("Graphic.mainFrameHeight", 500);
    mainFrameWidth  = settingsTree.get<size_t>  ("Graphic.mainFrameWidth",  500);
    cellSize        = settingsTree.get<size_t>  ("Graphic.cellSize",        10);
    drawPeriod      = settingsTree.get<int>     ("Graphic.drawPeriod",      42);
    scale           = settingsTree.get<int>     ("Graphic.scale",           1);

    // Вселенная
    universeHeight   = settingsTree.get<size_t> ("Universe.height",           500);
    universeWidth    = settingsTree.get<size_t> ("Universe.width",            500);
    generationPeriod = settingsTree.get<int>    ("Universe.generationPeriod", 500);
    cycled           = settingsTree.get<bool>   ("Universe.cycled",           false);
}

void CGL::Settings::load()
{
    load(PRJ_NAME".ini");
}

void CGL::Settings::save(const std::string &filename)
{
    boost::property_tree::ptree settingsTree;

    // Журналирование
//    settingsTree.put("LogSettings.logLevel",    logLevel);
    settingsTree.put("LogSettings.logToFile",   logToFile);
    settingsTree.put("LogSettings.logToStdout", logToStdout);
    settingsTree.put("LogSettings.logLast",     logLast);
    settingsTree.put("LogSettings.logPath",     logPath);

    // Отображение
    settingsTree.put("Graphic.mainFrameHeight",   mainFrameHeight  );
    settingsTree.put("Graphic.mainFrameWidth",    mainFrameWidth   );
    settingsTree.put("Graphic.cellSize",          cellSize         );
    settingsTree.put("Graphic.drawPeriod",        drawPeriod       );
    settingsTree.put("Graphic.scale",             scale            );

    // Вселенная
    settingsTree.put("Universe.height",           universeHeight   );
    settingsTree.put("Universe.width",            universeWidth    );
    settingsTree.put("Universe.generationPeriod", generationPeriod );
    settingsTree.put("Universe.cycled",           cycled           );


    try {
        boost::property_tree::write_ini(filename, settingsTree);
    } catch (...) {

        std::cout << "Error: can not save log settings to file \""
                  << filename << "\"" << std::endl;
    }
}

void CGL::Settings::save()
{
    save(PRJ_NAME".ini");
}

CGL::Settings &CGL::Settings::get()
{
    static Settings settings;

    return settings;
}
