#include <iostream>
#include <SFML/Graphics.hpp>

#include "info.h"
#include "logger.h"
#include "settings.h"
#include "game.h"

#include <thread>
#include <chrono>


#include "life_types.hpp"
#include "simpleuniverse.h"

int main(/*int argc, char* argv[]*/)
{
    auto &settings       = cgl::Settings::get();
    settings.logLevel    = cgl::Settings::LogLevel::info;
    settings.logToStdout = true;

    cgl::Logger::info(cgl::makeStr(PRJ_NAME, "Version", PRJ_VERSION));

    sf::RenderWindow mainWindow(sf::VideoMode(1000, 600), PRJ_NAME);

    cgl::SimpleUniverse univ(settings.cycled, settings.universeWidth, settings.universeHeight);

    Game game(mainWindow, univ);

    game.run();

    mainWindow.close();

    settings.save();
}
