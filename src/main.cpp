#include <iostream>
#include <SFML/Graphics.hpp>

#include "info.h"
#include "logger.h"
#include "settings.h"

#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
    auto &settings       = CGL::Settings::get();
    settings.logLevel    = CGL::Settings::LogLevel::trace;
    settings.logToStdout = true;

    CGL::Logger::info(CGL::makeStr(PRJ_NAME, "Version", PRJ_VERSION));

    sf::RenderWindow App(sf::VideoMode(800, 600), PRJ_NAME);

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }
        App.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        App.clear();
    }

    settings.save();
}
