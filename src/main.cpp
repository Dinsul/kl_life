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
    auto &settings       = CGL::Settings::get();
    settings.logLevel    = CGL::Settings::LogLevel::debug;
    settings.logToStdout = true;

    CGL::Logger::info(CGL::makeStr(PRJ_NAME, "Version", PRJ_VERSION));

    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), PRJ_NAME);

    CGL::SimpleUniverse univ;

//    univ.addCell({34,21});
//    univ.addCell({34,22});
//    univ.addCell({34,23});

//    univ.addCell({34,23});
//    univ.addCell({35,23});
//    univ.addCell({36,23});
//    univ.addCell({37,23});
//    univ.addCell({38,23});

//    univ.addCell({39,22});
//    univ.addCell({39,20});
//    univ.addCell({37,19});
//    univ.addCell({35,20});

    Game game(mainWindow, univ);

    game.run();

    mainWindow.close();


//    while (MainWindow.isOpen())
//    {
//        sf::Event Event;
//        while (MainWindow.pollEvent(Event))
//        {
//            if (Event.type == sf::Event::Closed)
//                MainWindow.close();
//        }
//    }

    settings.save();
}
