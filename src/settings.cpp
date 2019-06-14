#include "settings.h"
#include "logger.h"
#include "info.h"

#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>

#ifdef WIN32
    static std::string iniFileDefault = "settings.ini";
    static std::string logPathDefalt  = "log";
#else
    static auto iniFileDefault = cgl::cat(getenv("HOME"), "/.", PRJ_NAME, "/settings.ini");
    static auto logPathDefalt  = cgl::cat(getenv("HOME"), "/.", PRJ_NAME, "/log");
#endif

cgl::Settings::Settings()
{
    load();
}

void cgl::Settings::load(const std::string &filename)
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
    logToFile   = settingsTree.get<bool>          ("LogSettings.logToFile",     true);
    logToStdout = settingsTree.get<bool>          ("LogSettings.logToStdout",   false);
    logLast     = settingsTree.get<bool>          ("LogSettings.logLast",       false);
    logPath     = settingsTree.get<std::string>   ("LogSettings.logPath",       logPathDefalt);

    // Отображение
    smiles           = settingsTree.get<bool>     ("Graphic.smiles",            true);
    cellSize         = settingsTree.get<int>      ("Graphic.cellSize",          10);
    drawPeriod       = settingsTree.get<int>      ("Graphic.drawPeriod",        42);
    inhabitantColor  = settingsTree.get<uint32_t> ("Universe.inhabitantColor",  0xFFA030FF);
    backGroundColor  = settingsTree.get<uint32_t> ("Universe.backGroundColor",  0xFFFFFFFF);
    gridColor        = settingsTree.get<uint32_t> ("Universe.gridColor",        0x8080F0FF);

    // Вселенная
    universeHeight   = settingsTree.get<int>      ("Universe.height",           200);
    universeWidth    = settingsTree.get<int>      ("Universe.width",            200);
    generationPeriod = settingsTree.get<int>      ("Universe.generationPeriod", 100);
    historyDeep      = settingsTree.get<unsigned int> ("Graphic.historyDeep",   5);
    cycled           = settingsTree.get<bool>     ("Universe.cycled",           false);
}

void cgl::Settings::load()
{
    load(iniFileDefault);
}

void cgl::Settings::save(const std::string &filename)
{
    boost::property_tree::ptree settingsTree;

    // Журналирование
//    settingsTree.put("LogSettings.logLevel",      logLevel);
    settingsTree.put("LogSettings.logToFile",     logToFile        );
    settingsTree.put("LogSettings.logToStdout",   logToStdout      );
    settingsTree.put("LogSettings.logLast",       logLast          );
    settingsTree.put("LogSettings.logPath",       logPath          );

    // Отображение
    settingsTree.put("Graphic.smiles",            smiles           );
    settingsTree.put("Graphic.cellSize",          cellSize         );
    settingsTree.put("Graphic.drawPeriod",        drawPeriod       );
    settingsTree.put("Universe.inhabitantColor",  inhabitantColor  );
    settingsTree.put("Universe.backGroundColor",  backGroundColor  );
    settingsTree.put("Universe.gridColor",        gridColor        );

    // Вселенная
    settingsTree.put("Universe.height",           universeHeight   );
    settingsTree.put("Universe.width",            universeWidth    );
    settingsTree.put("Universe.generationPeriod", generationPeriod );
    settingsTree.put("Graphic.historyDeep",       historyDeep      );
    settingsTree.put("Universe.cycled",           cycled           );


    try {
        boost::property_tree::write_ini(filename, settingsTree);
    } catch (...) {

        std::cout << "Error: can not save log settings to file \""
                  << filename << "\"" << std::endl;
    }
}

void cgl::Settings::save()
{
    save(iniFileDefault);
}

cgl::Settings &cgl::Settings::get()
{
    static Settings settings;

    return settings;
}
