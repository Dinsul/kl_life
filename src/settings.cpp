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

//    logLevel    = settingsTree.get<LogLevel> ("LogSettings.logLevel",    LogLevel::info);
    logToFile   = settingsTree.get<bool>        ("LogSettings.logToFile",   true);
    logToStdout = settingsTree.get<bool>        ("LogSettings.logToStdout", false);
    logLast     = settingsTree.get<bool>        ("LogSettings.logLast",     false);
    logPath     = settingsTree.get<std::string> ("LogSettings.logPath",     "log");
}

void CGL::Settings::load()
{
    load(PRJ_NAME".ini");
}

void CGL::Settings::save(const std::string &filename)
{
    boost::property_tree::ptree settingsTree;

//    settingsTree.put("LogSettings.logLevel",    logLevel);
    settingsTree.put("LogSettings.logToFile",   logToFile);
    settingsTree.put("LogSettings.logToStdout", logToStdout);
    settingsTree.put("LogSettings.logLast",     logLast);
    settingsTree.put("LogSettings.logPath",     logPath);


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
